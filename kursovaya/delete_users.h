#ifndef DELETE_USERS_H
#define DELETE_USERS_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "database.h"

namespace Ui {
class delete_users;
}

class delete_users : public QDialog
{
    Q_OBJECT

public:
    explicit delete_users(QWidget *parent = nullptr);
    ~delete_users();
    void refreshUsersList();

private slots:
    void on_backButton_clicked();
    void onDeleteButtonClicked();

private:
    Ui::delete_users *ui;
    QVBoxLayout *usersLayout;
     Database *db;
};

#endif // DELETE_USERS_H
