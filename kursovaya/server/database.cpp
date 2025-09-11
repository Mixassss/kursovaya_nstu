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

bool Database::authenticateUser(const QString &login, const QString &password, QString &position)
{
    QString hashedPassword = hashPassword(password);

    qDebug() << "[AUTH] Login attempt:";
    qDebug() << "  login:" << login;
    qDebug() << "  raw password:" << password;
    qDebug() << "  hashed password (client input):" << hashedPassword;

    QSqlQuery query(db);
    query.prepare("SELECT position, password FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        qWarning() << "[AUTH] Ошибка запроса:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString storedHash = query.value(1).toString();
        qDebug() << "  stored hash (from DB):" << storedHash;

        if (storedHash == hashedPassword) {
            position = query.value(0).toString();
            qDebug() << "[AUTH] Success, position =" << position;
            return true;
        } else {
            qWarning() << "[AUTH] Hash mismatch!";
        }
    } else {
        qWarning() << "[AUTH] Пользователь не найден:" << login;
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
