#include "autorization.h"
#include "ui_autorization.h"
#include "main_lection.h" // Импортируем класс main_lection
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog) {
    ui->setupUi(this);

    // Ограничение длины логина и пароля до 20 символов
    ui->Login->setMaxLength(20);
    ui->Password->setMaxLength(20);

    // Устанавливаем фиксированный размер окна
    setFixedSize(300, 250);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &Dialog::on_backButton_clicked);

    // Изначально кнопка "Войти" отключена
    ui->pushButton->setEnabled(false);

    // Подключаем слоты для отслеживания изменений в полях ввода
    connect(ui->Login, &QLineEdit::textChanged, this, &Dialog::on_inputChanged);
    connect(ui->Password, &QLineEdit::textChanged, this, &Dialog::on_inputChanged);

    // Подключаем кнопку "Войти" к слоту
    connect(ui->pushButton, &QPushButton::clicked, this, &Dialog::on_loginButton_clicked);
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::on_loginButton_clicked() { // Реализация слота
    // Проверка логина и пароля
    const QString correctLogin = "user";
    const QString correctPassword = "1234";

    if (ui->Login->text() == correctLogin && ui->Password->text() == correctPassword) {
        main_lection *lectionWindow = new main_lection(this); // Создаем и открываем окно main_lection
        lectionWindow->show(); // Показываем новое окно
        accept(); // Закрываем диалог с результатом "Accepted"
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
        // Очищаем поля логина и пароля
        ui->Login->clear();
        ui->Password->clear();
    }
}

void Dialog::on_backButton_clicked() { // Реализация слота для кнопки "Назад"
    reject(); // Закрывает диалог с результатом "Rejected"
}

void Dialog::on_inputChanged(){ // Проверка длины вводимых символов
    // Проверяем, что оба поля содержат хотя бы 4 символов
    bool isLoginValid = ui->Login->text().length() >= 4;
    bool isPasswordValid = ui->Password->text().length() >= 4;

    // Активируем кнопку "Войти", если оба поля заполнены правильно
    ui->pushButton->setEnabled(isLoginValid && isPasswordValid);
}
