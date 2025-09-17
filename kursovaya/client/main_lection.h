#ifndef MAIN_LECTION_H
#define MAIN_LECTION_H

#include <QDialog>
#include <QPointer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QMap>
#include <qt6/QtCore/qmap.h>
#include <QByteArray>

namespace Ui {
class main_lection;
}

class main_lection : public QDialog
{
    Q_OBJECT

public:
    explicit main_lection(QTcpSocket *sharedSocket, int currentUserId, QWidget *parent = nullptr);
    ~main_lection();

private slots:
    void on_easy_question_clicked();
    void on_middle_question_clicked();
    void on_hard_question_clicked();
    void on_code_question_clicked();
    void on_lection1_clicked();
    void on_lection2_clicked();
    void on_lection3_clicked();
    void on_backButton_clicked();
    void on_exitButton_clicked();
    void onServerResponse();
    void requestTestResults();
    void updateTotalScore();  // обновляет сумму баллов и выводит в max_balls

private:
    Ui::main_lection *ui;
    QTcpSocket *socket;
    int userId;
    int waitingForTestId = 0;

    int totalScore = 0;
    QMap<int, int> testResults = {{1,-1},{2,-1},{3,-1},{4,-1}};

    QByteArray socketBuffer;
};

#endif // MAIN_LECTION_H
