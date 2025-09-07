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

    bool connectToDatabase();
    bool authenticateUser(const QString &login, const QString &password, QString &position);
    bool addUser(const QString &login, const QString &password, const QString &position);
    QSqlDatabase getDatabase() const { return db; }
    bool deleteUser(int userId);
    QSqlError lastError() const;
    QString hashPassword(const QString &password);
    QVector<QPair<int, QString>> getAvailableTests();
    QVector<QPair<int, QString>> getTestQuestions(int testId);
    QVector<QPair<int, QString>> getQuestionAnswers(int questionId);
    int getCorrectAnswerId(int questionId);
    bool saveTestResult(int studentId, int testId, int score);
    QByteArray encryptData(const QString &data);
    QString decryptData(const QByteArray &encryptedData);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
