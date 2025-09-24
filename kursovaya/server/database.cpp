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
                                     const QVector<QString> &answers)
{
    if (!db.isOpen()) {
        qWarning() << "База данных не открыта!";
        return false;
    }

    // Максимум 10 ответов (answer1..answer10)
    QStringList cols = {"student_id", "test_id", "score", "passed_at"};
    QStringList placeholders = {":student_id", ":test_id", ":score", "NOW()"};

    for (int i = 0; i < 10; ++i) {
        cols << QString("answer%1").arg(i + 1);
        if (i < answers.size())
            placeholders << QString(":answer%1").arg(i + 1);
        else
            placeholders << "NULL";
    }

    QString sql = QString(R"(
        INSERT INTO student_tests (%1)
        VALUES (%2)
        ON CONFLICT (student_id, test_id)
        DO UPDATE SET score = EXCLUDED.score,
                      passed_at = EXCLUDED.passed_at,
                      %3
    )")
                      .arg(cols.join(", "))
                      .arg(placeholders.join(", "))
                      .arg(QStringList({
                                           "answer1 = EXCLUDED.answer1",
                                           "answer2 = EXCLUDED.answer2",
                                           "answer3 = EXCLUDED.answer3",
                                           "answer4 = EXCLUDED.answer4",
                                           "answer5 = EXCLUDED.answer5",
                                           "answer6 = EXCLUDED.answer6",
                                           "answer7 = EXCLUDED.answer7",
                                           "answer8 = EXCLUDED.answer8",
                                           "answer9 = EXCLUDED.answer9",
                                           "answer10 = EXCLUDED.answer10"
                                       }).join(", "));

    QSqlQuery query(db);
    query.prepare(sql);

    query.bindValue(":student_id", studentId);
    query.bindValue(":test_id", testId);
    query.bindValue(":score", score);

    for (int i = 0; i < answers.size() && i < 10; ++i) {
        query.bindValue(QString(":answer%1").arg(i + 1), answers[i]);
    }

    if (!query.exec()) {
        qWarning() << "Ошибка сохранения результата:" << query.lastError().text();
        return false;
    }

    return true;
}
