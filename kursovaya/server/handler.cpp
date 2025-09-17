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
        QString answer1 = request.value("answer1").toString();
        QString answer2 = request.value("answer2").toString();
        QString answer3 = request.contains("answer3") ? request.value("answer3").toString() : "";

        bool ok = m_db->saveStudentTestResult(studentId, testId, score, answer1, answer2, answer3);

        response["type"] = "save_result";
        response["status"] = ok ? "ok" : "error";
        response["test_id"] = testId;
        response["score"] = score;
    }
    else if (cmd == "get_result") {
        int studentId = request.value("student_id").toInt();
        int testId = request.value("test_id").toInt();

        QString sql;
        if (testId == 1) {
            sql = "SELECT score, passed_at, answer1, answer2 "
                  "FROM student_tests WHERE student_id = :sid AND test_id = :tid "
                  "ORDER BY score DESC, passed_at DESC LIMIT 1";
        } else if (testId == 2 || testId == 3 || testId == 4) {
            sql = "SELECT score, passed_at, answer1, answer2, answer3 "
                  "FROM student_tests WHERE student_id = :sid AND test_id = :tid "
                  "ORDER BY score DESC, passed_at DESC LIMIT 1";
        }

        QSqlQuery query(m_db->connection());
        query.prepare(sql);
        query.bindValue(":sid", studentId);
        query.bindValue(":tid", testId);

        response["type"] = "get_result";
        response["test_id"] = testId;   // 🔥 теперь клиент понимает, откуда ответ

        if (query.exec() && query.next()) {
            response["status"] = "ok";
            response["score"] = query.value("score").toInt();
            response["passed_at"] = query.value("passed_at").toString();
            response["answer1"] = query.value("answer1").toString();
            response["answer2"] = query.value("answer2").toString();
            if (testId == 2 || testId == 3 || testId == 4) {
                response["answer3"] = query.value("answer3").toString();
            }
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
