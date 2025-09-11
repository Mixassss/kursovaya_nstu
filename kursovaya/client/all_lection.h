#ifndef ALL_LECTION_H
#define ALL_LECTION_H

#include <QDialog>

namespace Ui {
class all_lection;
}

class all_lection : public QDialog
{
    Q_OBJECT

public:
    explicit all_lection(QWidget *parent = nullptr);
    ~all_lection();

private slots:
    void on_backButton_clicked();   // Слот для обработки нажатия кнопки "Вернуться к лекциям"
    void toggleFullScreen();


private:
    Ui::all_lection *ui;
};

#endif // ALL_LECTION_H
