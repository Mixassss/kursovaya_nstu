#include "database.h"
#include <QDebug>
#include <QSqlQuery>

Database::Database(QObject *parent) : QObject(parent)
{
    if (QSqlDatabase::isDriverAvailable("QPSQL")) {
        qDebug() << "PostgreSQL driver is available";

        // Создаем только одно соединение с именем
        db = QSqlDatabase::addDatabase("QPSQL", "education_connection");
        db.setHostName("localhost");
        db.setPort(5432);
        db.setDatabaseName("education_db");
        db.setUserName("postgres");
        db.setPassword("Password123");
        db.setConnectOptions("connect_timeout=5");

        qDebug() << "Database configured:";
        qDebug() << "  Host:" << db.hostName();
        qDebug() << "  Database:" << db.databaseName();
        qDebug() << "  User:" << db.userName();
        qDebug() << "  Port:" << db.port();
    } else {
        qWarning() << "PostgreSQL driver NOT available";
    }
}

Database::~Database()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool Database::connectToDatabase()
{
    if (!db.open()) {
        qWarning() << "Database error:" << db.lastError().text();
        return false;
    }
    return true;
}

bool Database::authenticateUser(const QString &login, const QString &password, QString &position, int &userId) {
    if (!db.isOpen()) {
        qWarning() << "База данных не открыта!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, position, password FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        qWarning() << "Ошибка запроса аутентификации:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString storedHash = query.value("password").toString();
        QString hash = hashPassword(password); // твоя функция хэширования

        if (storedHash == hash) {
            position = query.value("position").toString();
            userId = query.value("id").toInt();
            return true;
        }
    }

    return false;
}


QSqlError Database::lastError() const
{
    return db.lastError();
}

bool Database::addUser(const QString &login, const QString &password, const QString &position)
{
    if (!db.isOpen()) {
        qWarning() << "База данных не открыта!";
        return false;
    }

    // Проверка на существование пользователя
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM users WHERE login = :login");
    checkQuery.bindValue(":login", login);

    if (!checkQuery.exec() || !checkQuery.next()) {
        qWarning() << "Проверьте ошибку запроса:" << checkQuery.lastError().text();
        return false;
    }

    if (checkQuery.value(0).toInt() > 0) {
        qWarning() << "Пользователь с логином" << login << "уже существует";
        return false;
    }

    // Хеширование пароля
    QString hashedPassword = hashPassword(password);

    // Добавление пользователя
    QSqlQuery insertQuery(db);
    insertQuery.prepare("INSERT INTO users (login, password, position) VALUES (:login, :password, :position)");
    insertQuery.bindValue(":login", login);
    insertQuery.bindValue(":password", hashedPassword);
    insertQuery.bindValue(":position", position);

    if (!insertQuery.exec()) {
        qWarning() << "Insert error:" << insertQuery.lastError().text();
        return false;
    }

    return true;
}

bool Database::deleteUser(int userId)
{
    if (!db.isOpen()) {
        qWarning() << "База данных не открыта!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM users WHERE id = :id AND position != 'admin'");
    query.bindValue(":id", userId);

    if (!query.exec()) {
        qWarning() << "Delete error:" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

QString Database::hashPassword(const QString &password)
{
    QByteArray passwordData = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

QList<QVariantMap> Database::getAllUsers()
{
    QList<QVariantMap> list;

    if (!db.isOpen()) {
        qWarning() << "База данных не открыта!";
        return list;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT id, login, position FROM users ORDER BY id ASC")) {
        qWarning() << "Ошибка выборки пользователей:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        QVariantMap user;
        user["id"] = query.value(0);
        user["login"] = query.value(1);
        user["position"] = query.value(2);
        list.append(user);
    }

    return list;
}

// Получить вопросы и ответы для теста
QList<QVariantMap> Database::getQuestionsForTest(int testId) {
    QList<QVariantMap> list;
    QSqlQuery query(db);
    query.prepare(R"(
        SELECT q.id, q.question_text, a.id AS answer_id, a.answer_text, q.correct_answer_id
        FROM questions q
        JOIN answers a ON q.id = a.question_id
        WHERE q.test_id = :test_id
        ORDER BY q.id, a.id
    )");
    query.bindValue(":test_id", testId);

    if (!query.exec()) {
        qWarning() << "Ошибка выборки вопросов:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        QVariantMap row;
        row["question_id"] = query.value("id");
        row["question_text"] = query.value("question_text");
        row["answer_id"] = query.value("answer_id");
        row["answer_text"] = query.value("answer_text");
        row["correct_answer_id"] = query.value("correct_answer_id");
        list.append(row);
    }
    return list;
}

// Сохранить результат теста студента
bool Database::saveStudentTestResult(int studentId, int testId, int score,
                                     const QString &answer1, const QString &answer2,
                                     const QString &answer3)
{
    QSqlQuery query(db);

    if (testId == 1) {
        query.prepare(R"(
            UPDATE student_tests
            SET score = :score,
                passed_at = NOW(),
                answer1 = :answer1,
                answer2 = :answer2
            WHERE student_id = :student_id AND test_id = :test_id
        )");
        query.bindValue(":answer1", answer1);
        query.bindValue(":answer2", answer2);
    } else if (testId == 2 || testId == 3 || testId == 4) {
        query.prepare(R"(
            UPDATE student_tests
            SET score = :score,
                passed_at = NOW(),
                answer1 = :answer1,
                answer2 = :answer2,
                answer3 = :answer3
            WHERE student_id = :student_id AND test_id = :test_id
        )");
        query.bindValue(":answer1", answer1);
        query.bindValue(":answer2", answer2);
        query.bindValue(":answer3", answer3);
    }

    query.bindValue(":score", score);
    query.bindValue(":student_id", studentId);
    query.bindValue(":test_id", testId);

    if (!query.exec()) {
        qWarning() << "Ошибка обновления результата:" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        if (testId == 1) {
            query.prepare(R"(
                INSERT INTO student_tests (student_id, test_id, score, passed_at, answer1, answer2)
                VALUES (:student_id, :test_id, :score, NOW(), :answer1, :answer2)
            )");
            query.bindValue(":answer1", answer1);
            query.bindValue(":answer2", answer2);
        } else if (testId == 2 || testId == 3 || testId == 4) {
            query.prepare(R"(
                INSERT INTO student_tests (student_id, test_id, score, passed_at, answer1, answer2, answer3)
                VALUES (:student_id, :test_id, :score, NOW(), :answer1, :answer2, :answer3)
            )");
            query.bindValue(":answer1", answer1);
            query.bindValue(":answer2", answer2);
            query.bindValue(":answer3", answer3);
        }

        query.bindValue(":student_id", studentId);
        query.bindValue(":test_id", testId);
        query.bindValue(":score", score);

        if (!query.exec()) {
            qWarning() << "Ошибка вставки результата:" << query.lastError().text();
            return false;
        }
    }

    return true;
}


