#include "autorization.h"
#include "ui_autorization.h"
#include "database.h"
#include <QMessageBox>
#include "window_admin.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , db(new Database(this))
{
    ui->setupUi(this);

    // Попытка подключения к базе данных
    if (!db->connectToDatabase()) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось подключиться к базе данных:\n" + db->lastError().text() +
                                  "\n\nУбедитесь, что:\n"
                                  "1. PostgreSQL запущен\n"
                                  "2. База данных 'education_db' существует\n"
                                  "3. Пользователь 'postgres' имеет доступ");
    } else {
        qDebug() << "Database connection established";
    }

    // Ограничение длины логина и пароля
    ui->Login->setMaxLength(50);
    ui->Password->setMaxLength(255);
    ui->Password->setEchoMode(QLineEdit::Password);

    // Устанавливаем фиксированный размер окна
    setFixedSize(300, 250);
    setWindowTitle("Авторизация");

    // Подключаем кнопки
    connect(ui->pushButton, &QPushButton::clicked, this, &Dialog::on_loginButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Dialog::on_backButton_clicked);

    // Изначально кнопка "Войти" отключена
    ui->pushButton->setEnabled(false);

    // Подключаем слоты для отслеживания изменений в полях ввода
    connect(ui->Login, &QLineEdit::textChanged, this, &Dialog::on_inputChanged);
    connect(ui->Password, &QLineEdit::textChanged, this, &Dialog::on_inputChanged);
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::on_loginButton_clicked() {
    QString login = ui->Login->text().trimmed();
    QString password = ui->Password->text();
    QString position;

    if (db->authenticateUser(login, password, position)) {
        // Сохраняем позицию для использования в MainWindow
        this->userPosition = position;

        // Закрываем окно авторизации с результатом Accepted
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
        ui->Password->clear();
        ui->Password->setFocus();
    }
}

QString Dialog::getUserPosition() const {
    return userPosition;
}

void Dialog::on_backButton_clicked() {
    reject();
}

void Dialog::on_inputChanged() {
    bool isLoginValid = ui->Login->text().length() >= 3;
    bool isPasswordValid = ui->Password->text().length() >= 4;
    ui->pushButton->setEnabled(isLoginValid && isPasswordValid);
}
