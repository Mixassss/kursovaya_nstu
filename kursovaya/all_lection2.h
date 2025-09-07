#ifndef ALL_LECTION2_H
#define ALL_LECTION2_H

#include <QDialog>

namespace Ui {
class all_lection2;
}

class all_lection2 : public QDialog
{
    Q_OBJECT

public:
    explicit all_lection2(QWidget *parent = nullptr);
    ~all_lection2();

private slots:
    void on_backButton_clicked();   // Слот для обработки нажатия кнопки "Вернуться к лекциям"

private:
    Ui::all_lection2 *ui;
};

#endif // ALL_LECTION2_H
