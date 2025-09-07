#ifndef ADD_USERS_H
#define ADD_USERS_H

#include <QDialog>
#include "database.h"

namespace Ui {
class add_users;
}

class add_users : public QDialog
{
    Q_OBJECT

public:
    explicit add_users(QWidget *parent = nullptr);
    ~add_users();

private slots:
    void on_backButton_clicked();
    void on_addButton_clicked();
    void on_inputChanged();

private:
    Ui::add_users *ui;
    Database *db;
};

#endif // ADD_USERS_H
