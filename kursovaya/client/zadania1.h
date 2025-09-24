#ifndef ZADANIA1_H
#define ZADANIA1_H

#include <QDialog>
#include <QTcpSocket>
#include <QRadioButton>
#include <QJsonObject>

namespace Ui {
class zadania1;
}

class zadania1 : public QDialog
{
    Q_OBJECT

public:
    explicit zadania1(QTcpSocket *sharedSocket, int currentUserId, QWidget *parent = nullptr);
    ~zadania1();

signals:
    void scoreUpdated(int score); // сигнал для main_lection

private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void onBackClicked();
    void onServerResponse();
    void updateSubmitButtonState();

private:
    Ui::zadania1 *ui;
    QTcpSocket *socket;
    int userId;
    bool alreadyPassed;
    QString lastAnswer1, lastAnswer2;

    void lockAnswers();
    void resetAnswers();
    void sendSaveResult(int score);
    void restoreAnswersAndHighlight(const QString &answer1, const QString &answer2);
    void updateButtonsVisibility();
};

#endif // ZADANIA1_H
