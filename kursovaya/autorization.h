#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_loginButton_clicked(); // Слот для обработки нажатия кнопки "Войти"
    void on_backButton_clicked();   // Слот для обработки нажатия кнопки "Назад"
    void on_inputChanged();         // Слот для обработки изменений в полях ввода

private:
    Ui::Dialog *ui;
};

#endif // AUTORIZATION_H
