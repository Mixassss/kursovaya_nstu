#ifndef FINISH_TEST_H
#define FINISH_TEST_H

#include <QDialog>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class finish_test;
}

class finish_test : public QDialog
{
    Q_OBJECT

public:
    explicit finish_test(QTcpSocket *sharedSocket, int studentId, int testId, QWidget *parent = nullptr);
    ~finish_test();

signals:
    void scoreUpdated(int newScore);

private slots:
    void updateTimer();
    void showQuestion();
    void submitAnswer();
    void finishTest();
    void updateTimerLabel();

    // недостающие слоты
    void onServerResponse();

private:
    Ui::finish_test *ui;
    int studentId;
    int testId;
    int currentQuestion;
    int score;
    int remainingTime;
    QTimer *timer;
    QTcpSocket *socket;

    QVector<QString> allQuestions;
    QVector<QString> correctAnswers;
    QStringList givenAnswers;

    bool alreadyPassed = false;

    // вспомогательные функции
    void sendSaveResult();
    void restoreAnswers(const QJsonArray &answers);
    void requestPreviousResult();
};

#endif // FINISH_TEST_H
