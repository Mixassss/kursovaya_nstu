#ifndef WINDOW_ADMIN_H
#define WINDOW_ADMIN_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class window_admin;
}

class window_admin : public QDialog
{
    Q_OBJECT

public:
    explicit window_admin(QTcpSocket *sharedSocket, QWidget *parent = nullptr);
    void on_exitButton_clicked();
    void on_backButton_clicked();
    void on_add_users_clicked();
    void on_delete_users_clicked();
    ~window_admin();

private:
    Ui::window_admin *ui;
    QTcpSocket *socket;
};

#endif // WINDOW_ADMIN_H
