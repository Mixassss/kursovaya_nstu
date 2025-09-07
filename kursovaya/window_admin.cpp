#include "window_admin.h"
#include "ui_window_admin.h"
#include "dialog_window_exit.h"
#include "add_users.h"
#include "delete_users.h"

window_admin::window_admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::window_admin)
{
    ui->setupUi(this);

    // Подключаем сигнал clicked() кнопки "Выход из системы" к слоту
    connect(ui->pushButton, &QPushButton::clicked, this, &window_admin::on_exitButton_clicked);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &window_admin::on_backButton_clicked);

    connect(ui->add_users, &QPushButton::clicked, this, &window_admin::on_add_users_clicked);

    connect(ui->delete_users, &QPushButton::clicked, this, &window_admin::on_delete_users_clicked);
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
    add_users *usersWindow = new add_users(this);
    usersWindow->exec(); // Открываем add_users как модальное окно
}

void window_admin::on_delete_users_clicked() {
    delete_users *deleteWindow = new delete_users(this);
    deleteWindow->exec(); // Открываем окно удаления как модальное
    delete deleteWindow;
}
