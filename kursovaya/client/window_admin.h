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
    explicit window_admin(QTcpSocket *sharedSocket, const QString &role, QWidget *parent = nullptr);
    void on_exitButton_clicked();
    void on_backButton_clicked();
    void on_add_users_clicked();
    void on_delete_users_clicked();
    void on_check_results_clicked();
    ~window_admin();

private:
    Ui::window_admin *ui;
    QTcpSocket *socket;
    QString role;
};

#endif // WINDOW_ADMIN_H
