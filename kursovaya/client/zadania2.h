#ifndef ZADANIA2_H
#define ZADANIA2_H

#include <QDialog>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QRadioButton>

namespace Ui {
class zadania2;
}

class zadania2 : public QDialog {
    Q_OBJECT

public:
    explicit zadania2(QTcpSocket *sharedSocket, int currentUserId, QWidget *parent = nullptr);
    ~zadania2();

signals:
    void scoreUpdated(int score);

private slots:
    void updateSubmitButtonState();
    void on_backButton_clicked();
    void onBackClicked();
    void on_pushButton_2_clicked();   // «Пройти ещё раз»
    void on_pushButton_6_clicked();   // «Ответить»
    void onServerResponse();

private:
    Ui::zadania2 *ui;
    QTcpSocket *socket;
    int userId;

    bool alreadyPassed = false;

    QString lastAnswer1, lastAnswer2, lastAnswer3;

    // методы
    void lockAnswers();
    void resetAnswers();
    void sendSaveResult(int score);
    void restoreAnswersAndHighlight(const QString &a1, const QString &a2, const QString &a3);
    void updateButtonsVisibility();
};

#endif // ZADANIA2_H
