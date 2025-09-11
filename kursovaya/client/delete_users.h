#ifndef DELETE_USERS_H
#define DELETE_USERS_H

#include <QDialog>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class delete_users;
}

class delete_users : public QDialog
{
    Q_OBJECT

public:
    explicit delete_users(QTcpSocket *sharedSocket, QWidget *parent = nullptr);
    ~delete_users();
    void requestUsersList();

private slots:
    void on_backButton_clicked();
    void onServerResponse();
    void onDeleteButtonClicked();

private:
    Ui::delete_users *ui;
    QTcpSocket *socket;
    QVBoxLayout *usersLayout;
};

#endif // DELETE_USERS_H
