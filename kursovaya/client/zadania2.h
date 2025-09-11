#ifndef ZADANIA2_H
#define ZADANIA2_H

#include <QDialog>

namespace Ui {
class zadania2;
}

class zadania2 : public QDialog {
    Q_OBJECT

public:
    explicit zadania2(QWidget *parent = nullptr);
    ~zadania2();

private slots:
    void updateSubmitButtonState();
    void on_pushButton_6_clicked();
    void updateButtonsVisibility();
    void on_backButton_clicked();
    void onBackClicked();

private:
    Ui::zadania2 *ui;
};

#endif // ZADANIA2_H
