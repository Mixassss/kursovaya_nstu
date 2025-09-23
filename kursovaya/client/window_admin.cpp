#include "window_admin.h"
#include "ui_window_admin.h"
#include "dialog_window_exit.h"
#include "add_users.h"
#include "delete_users.h"
#include "results.h"

window_admin::window_admin(QTcpSocket *sharedSocket, const QString &role, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::window_admin)
    , socket(sharedSocket)
    , role(role)
{
    ui->setupUi(this);

    if (role == "teacher") {
        ui->add_users->setEnabled(false);
        ui->delete_users->setEnabled(false);
    }

    connect(ui->pushButton, &QPushButton::clicked, this, &window_admin::on_exitButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &window_admin::on_backButton_clicked);
    connect(ui->add_users, &QPushButton::clicked, this, &window_admin::on_add_users_clicked);
    connect(ui->delete_users, &QPushButton::clicked, this, &window_admin::on_delete_users_clicked);
    connect(ui->check_results, &QPushButton::clicked, this, &window_admin::on_check_results_clicked);
}

window_admin::~window_admin()
{
    delete ui;
}

void window_admin::on_exitButton_clicked() {
    dialog_window_exit exitDialog(this); // Создаем экземпляр диалогового окна выхода
    if (exitDialog.exec() == QDialog::Accepted) {
        qApp->quit(); // Закрываем приложение, если нажата кнопка "Да"
    }
}

void window_admin::on_backButton_clicked() { // Реализация слота для кнопки "Назад"
    reject(); // Закрывает диалог с результатом "Rejected"
}

void window_admin::on_add_users_clicked() {
    add_users *usersWindow = new add_users(socket, this);
    usersWindow->exec();
    delete usersWindow;
}

void window_admin::on_delete_users_clicked() {
    delete_users *deleteWindow = new delete_users(socket, this);
    deleteWindow->exec();
    delete deleteWindow;
}

void window_admin::on_check_results_clicked() {
    results *resWindow = new results(socket, this);
    resWindow->exec();
    delete resWindow;
}
