#ifndef ZADANIA3_H
#define ZADANIA3_H

#include <QDialog>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRadioButton>

namespace Ui {
class zadania3;
}

class zadania3 : public QDialog {
    Q_OBJECT

public:
    explicit zadania3(QTcpSocket *sharedSocket, int currentUserId, QWidget *parent = nullptr);
    ~zadania3();

signals:
    void scoreUpdated(int score);

private slots:
    void updateSubmitButtonState();
    void on_pushButton_6_clicked();
    void updateButtonsVisibility();
    void on_backButton_clicked();
    void onBackClicked();
    void on_pushButton_2_clicked();
    void onServerResponse();

private:
    Ui::zadania3 *ui;
    QTcpSocket *socket;
    int userId;

    bool alreadyPassed = false;
    QString lastAnswer1, lastAnswer2, lastAnswer3;

    void lockAnswers();
    void resetAnswers();
    void sendSaveResult(int score);
    void restoreAnswersAndHighlight(const QString &a1, const QString &a2, const QString &a3);
};

#endif // ZADANIA3_H
