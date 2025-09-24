#include "handler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

Handler::Handler(qintptr socketDescriptor, Database *db, QObject *parent)
    : QObject(parent), m_socketDescriptor(socketDescriptor), m_db(db)
{
    m_socket = new QTcpSocket(this);
}

void Handler::process()
{
    if (!m_socket->setSocketDescriptor(m_socketDescriptor)) {
        qWarning() << "Не удалось установить дескриптор сокета";
        emit finished();
        return;
    }

    connect(m_socket, &QTcpSocket::readyRead, this, &Handler::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &Handler::onDisconnected);
}

void Handler::onReadyRead()
{
    m_buffer.append(m_socket->readAll());

    int index;
    while ((index = m_buffer.indexOf('\n')) != -1) {
        QByteArray line = m_buffer.left(index);
        m_buffer.remove(0, index + 1);

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(line, &error);
        if (error.error != QJsonParseError::NoError) {
            qWarning() << "[SERVER] JSON parse error:" << error.errorString() << "Data:" << line;
            continue;
        }

        if (!doc.isObject()) {
            qWarning() << "[SERVER] Not a JSON object!";
            continue;
        }

        QJsonObject request = doc.object();
        handleRequest(request);
    }
}

void Handler::handleRequest(const QJsonObject &request)
{
    QJsonObject response;
    QString cmd = request.value("type").toString();

    if (cmd == "auth") {
        QString position;
        int userId;
        bool ok = m_db->authenticateUser(
            request.value("login").toString(),
            request.value("password").toString(),
            position,
            userId
            );

        response["type"] = "auth";
        response["status"] = ok ? "ok" : "error";
        if (ok) {
            response["position"] = position;
            response["id"] = userId;
        }
    }
    else if (cmd == "add_user") {
        bool ok = m_db->addUser(
            request.value("login").toString(),
            request.value("password").toString(),
            request.value("position").toString()
            );

        response["type"] = "add_user";
        response["status"] = ok ? "ok" : "error";
    }
    else if (cmd == "delete_user") {
        bool ok = m_db->deleteUser(request.value("id").toInt());

        response["type"] = "delete_user";
        response["status"] = ok ? "ok" : "error";
        if (!ok) {
            response["reason"] = "Не удалось удалить пользователя (возможно, админ или неверный id)";
        }
    }
    else if (cmd == "list_users") {
        QJsonArray usersArray;
        QList<QVariantMap> users = m_db->getAllUsers();

        for (const QVariantMap &u : users) {
            QJsonObject userObj;
            userObj["id"] = u["id"].toInt();
            userObj["login"] = u["login"].toString();
            userObj["position"] = u["position"].toString();
            usersArray.append(userObj);
        }

        response["type"] = "list_users";
        response["status"] = "ok";
        response["users"] = usersArray;
    }
    else if (cmd == "get_test") {
        int testId = request.value("test_id").toInt();
        QList<QVariantMap> questions = m_db->getQuestionsForTest(testId);

        QJsonArray arr;
        for (auto &q : questions) {
            QJsonObject obj;
            obj["question_id"] = q["question_id"].toInt();
            obj["question_text"] = q["question_text"].toString();
            obj["answer_id"] = q["answer_id"].toInt();
            obj["answer_text"] = q["answer_text"].toString();
            obj["correct_answer_id"] = q["correct_answer_id"].toInt();
            arr.append(obj);
        }

        response["type"] = "get_test";
        response["status"] = "ok";
        response["questions"] = arr;
    }
    else if (cmd == "save_result") {
        int studentId = request.value("student_id").toInt();
        int testId = request.value("test_id").toInt();
        int score = request.value("score").toInt();

        QVector<QString> answers;
        if (request.contains("answers") && request.value("answers").isArray()) {
            QJsonArray arr = request.value("answers").toArray();
            for (const QJsonValue &v : arr) {
                answers.append(v.toString());
            }
        }

        bool ok = m_db->saveStudentTestResult(studentId, testId, score, answers);

        response["type"] = "get_result";
        response["test_id"] = testId;
        if (ok) {
            response["status"] = "ok";
            response["score"] = score;
            response["passed_at"] = QDateTime::currentDateTime().toString(Qt::ISODate);

            QJsonArray arr;
            for (const QString &ans : answers) arr.append(ans);
            response["answers"] = arr;
        } else {
            response["status"] = "error";
        }
    }
    else if (cmd == "list_results") {
        QJsonArray resultsArray;
        QSqlQuery query(m_db->connection());

        query.prepare(R"(
        SELECT s.student_id, s.test_id, s.score, s.passed_at,
               s.answer1, s.answer2, s.answer3, s.answer4, s.answer5,
               s.answer6, s.answer7, s.answer8, s.answer9, s.answer10,
               u.login
        FROM student_tests s
        JOIN users u ON s.student_id = u.id
        ORDER BY s.passed_at DESC
    )");

        if (query.exec()) {
            while (query.next()) {
                QJsonObject resultObj;
                resultObj["login"] = query.value("login").toString();
                resultObj["test_id"] = query.value("test_id").toInt();
                resultObj["score"] = query.value("score").toInt();
                resultObj["passed_at"] = query.value("passed_at").toString();

                QJsonArray answers;
                for (int i = 1; i <= 10; ++i) {
                    QString ans = query.value(QString("answer%1").arg(i)).toString();
                    if (!ans.isEmpty()) {
                        answers.append(ans);
                    }
                }
                resultObj["answers"] = answers;

                resultsArray.append(resultObj);
            }

            response["type"] = "list_results";
            response["status"] = "ok";
            response["results"] = resultsArray;
        } else {
            response["status"] = "error";
            response["reason"] = "Failed to fetch results";
        }
    }
    else if (cmd == "get_result") {
        int studentId = request.value("student_id").toInt();
        int testId = request.value("test_id").toInt();

        // Берем максимум answer1..answer10 (универсально для всех тестов)
        QString sql = R"(
        SELECT score, passed_at,
               answer1, answer2, answer3, answer4, answer5,
               answer6, answer7, answer8, answer9, answer10
        FROM student_tests
        WHERE student_id = :sid AND test_id = :tid
        ORDER BY score DESC, passed_at DESC
        LIMIT 1
    )";

        QSqlQuery query(m_db->connection());
        query.prepare(sql);
        query.bindValue(":sid", studentId);
        query.bindValue(":tid", testId);

        response["type"] = "get_result";
        response["test_id"] = testId;

        if (query.exec() && query.next()) {
            response["status"] = "ok";
            response["score"] = query.value("score").toInt();
            response["passed_at"] = query.value("passed_at").toString();

            // Собираем ответы в массив
            QJsonArray answers;
            for (int i = 1; i <= 10; ++i) {
                QString ans = query.value(QString("answer%1").arg(i)).toString();
                if (!ans.isEmpty()) {   // добавляем только непустые
                    answers.append(ans);
                }
            }
            response["answers"] = answers;
        } else {
            response["status"] = "empty";
        }
    }
    else {
        response["type"] = cmd.isEmpty() ? "unknown" : cmd;
        response["status"] = "error";
        response["reason"] = "Unknown command";
    }

    QByteArray respData = QJsonDocument(response).toJson(QJsonDocument::Compact) + "\n";
    m_socket->write(respData);
    m_socket->flush();
}


void Handler::onDisconnected()
{
    m_socket->deleteLater();
    emit finished();
}
