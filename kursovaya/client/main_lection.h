#ifndef MAIN_LECTION_H
#define MAIN_LECTION_H

#include <QDialog>
#include <QPointer>
#include <QTcpSocket>

namespace Ui {
class main_lection;
}

class main_lection : public QDialog
{
    Q_OBJECT

public:
    explicit main_lection(QTcpSocket *sharedSocket, QWidget *parent = nullptr);
    void on_easy_question_clicked();
    void on_middle_question_clicked();
    void on_hard_question_clicked();
    void on_code_question_clicked();
    void on_lection1_clicked();
    void on_lection2_clicked();
    void on_lection3_clicked();
    void on_backButton_clicked();
    void on_exitButton_clicked();
    ~main_lection();

private:
    Ui::main_lection *ui;
    QTcpSocket *socket;
};

#endif // MAIN_LECTION_H
