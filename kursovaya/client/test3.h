#ifndef TEST3_H
#define TEST3_H

#include <QDialog>

namespace Ui {
class test3;
}

class test3 : public QDialog
{
    Q_OBJECT

public:
    explicit test3(QWidget *parent = nullptr);
    ~test3();

private slots:
    void on_backButton_clicked();   // Слот для обработки нажатия кнопки "Вернуться на главную"
    void all_lection3_clicked();
    void lec3_1_clicked();
    void lec3_2_clicked();
    void lec3_3_clicked();
    void lec3_4_clicked();

private:
    Ui::test3 *ui;
};

#endif // TEST3_H
