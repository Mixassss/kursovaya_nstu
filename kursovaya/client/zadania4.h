#ifndef ZADANIA4_H
#define ZADANIA4_H

#include <QDialog>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class zadania4;
}

class zadania4 : public QDialog {
    Q_OBJECT

public:
    explicit zadania4(QTcpSocket *sharedSocket, int currentUserId, QWidget *parent = nullptr);
    ~zadania4();

signals:
    void scoreUpdated(int score);

private slots:
    void updateSubmitButtonState();
    void on_pushButton_6_clicked();
    void updateButtonsVisibility();
    void on_backButton_clicked();
    void onBackClicked();
    void on_pushButton_4_clicked();
    void onServerResponse();

private:
    Ui::zadania4 *ui;
    QTcpSocket *socket;
    int userId;

    bool alreadyPassed = false;
    QString lastAnswer1, lastAnswer2, lastAnswer3;

    void lockAnswers();
    void resetAnswers();
    void sendSaveResult(int score);
    void restoreAnswersAndHighlight(const QString &a1, const QString &a2, const QString &a3);
};

#endif // ZADANIA4_H
