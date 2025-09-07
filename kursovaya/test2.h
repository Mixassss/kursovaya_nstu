#ifndef TEST2_H
#define TEST2_H

#include <QDialog>

namespace Ui {
class test2;
}

class test2 : public QDialog
{
    Q_OBJECT

public:
    explicit test2(QWidget *parent = nullptr);
    ~test2();

private slots:
    void on_backButton_clicked();   // Слот для обработки нажатия кнопки "Вернуться на главную"
    void all_lection2_clicked();
    void lec2_1_clicked();
    void lec2_2_clicked();
    void lec2_3_clicked();
    void lec2_4_clicked();

private:
    Ui::test2 *ui;
};

#endif // TEST2_H
