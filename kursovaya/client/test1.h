#ifndef TEST1_H
#define TEST1_H

#include <QDialog>

namespace Ui {
class test1;
}

class test1 : public QDialog
{
    Q_OBJECT

public:
    explicit test1(QWidget *parent = nullptr);
    ~test1();

private slots:
    void on_backButton_clicked();   // Слот для обработки нажатия кнопки "Вернуться на главную"
    void all_lection_clicked();
    void lec1_1_clicked();
    void lec1_2_clicked();
    void lec1_3_clicked();
    void lec1_4_clicked();

private:
    Ui::test1 *ui;
};

#endif // TEST1_H
