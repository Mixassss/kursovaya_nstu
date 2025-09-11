#ifndef ALL_LECTION3_H
#define ALL_LECTION3_H

#include <QDialog>

namespace Ui {
class all_lection3;
}

class all_lection3 : public QDialog
{
    Q_OBJECT

public:
    explicit all_lection3(QWidget *parent = nullptr);
    ~all_lection3();

private slots:
    void on_backButton_clicked();   // Слот для обработки нажатия кнопки "Вернуться к лекциям"

private:
    Ui::all_lection3 *ui;
};

#endif // ALL_LECTION3_H
