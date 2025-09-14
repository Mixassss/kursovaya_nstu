#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUserId(int id) { userId = id; }   // сохраняем userId после авторизации

private slots:
    void on_loginButton_clicked(); // Слот для обработки нажатия кнопки
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    int userId;   // ID текущего пользователя
};

#endif // MAINWINDOW_H
