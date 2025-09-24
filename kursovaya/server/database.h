#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QCryptographicHash>
#include <QByteArray>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    QSqlDatabase& connection() { return db; }
    bool connectToDatabase();
    bool authenticateUser(const QString &login, const QString &password, QString &position, int &userId);
    bool addUser(const QString &login, const QString &password, const QString &position);
    QSqlDatabase getDatabase() const { return db; }
    bool deleteUser(int userId);
    QSqlError lastError() const;
    QString hashPassword(const QString &password);
    QList<QVariantMap> getAllUsers();
    bool saveStudentTestResult(int studentId, int testId, int score, const QVector<QString> &answers);
    QList<QVariantMap> getQuestionsForTest(int testId);
    QByteArray encryptData(const QString &data);
    QString decryptData(const QByteArray &encryptedData);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
