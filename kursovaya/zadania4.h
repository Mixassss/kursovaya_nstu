#ifndef ZADANIA4_H
#define ZADANIA4_H

#include <QDialog>

namespace Ui {
class zadania4;
}

class zadania4 : public QDialog
{
    Q_OBJECT

public:
    explicit zadania4(QWidget *parent = nullptr);
    ~zadania4();

private slots:
    void on_pushButton_6_clicked();
    void updateSubmitButtonState();
    void updateButtonsVisibility();
    void on_backButton_clicked();
    void onBackClicked();

private:
    Ui::zadania4 *ui;
};

#endif // ZADANIA4_H
