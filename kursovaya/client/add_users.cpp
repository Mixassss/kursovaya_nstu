#include "add_users.h"
#include "ui_add_users.h"
#include <QMessageBox>

add_users::add_users(QTcpSocket *sharedSocket, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_users)
    , socket(sharedSocket)
{
    ui->setupUi(this);

    this->setStyleSheet(
        "QLabel {"
        "    color: white; /* Белый цвет для всех надписей */"
        "    font-size: 12px;"
        "    font-weight: bold;"
        "}"
        "QLineEdit {"
        "    background-color: white;"
        "    border: 2px solid #dcdcdc;"
        "    color: #333333; /* Темный цвет текста для ввода */"
        "}"
        "QLineEdit:focus {"
        "    border-color: #4CAF50;"
        "}"
        "QLineEdit[echoMode='2'] { /* Стиль для поля пароля */"
        "    color: #333333; /* Темный цвет для текста пароля */"
        "}"
        "QGroupBox {"
        "    background-color: #5e5c64;"
        "    border: 2px solid #4a4850;"
        "    border-radius: 8px;"
        "    margin-top: 10px;"
        "    padding-top: 15px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    subcontrol-position: top center;"
        "    padding: 0 5px;"
        "    color: white;"
        "    font-weight: bold;"
        "}"
        "QRadioButton {"
        "    color: white;"
        "    font-size: 12px;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}"
        "QRadioButton::indicator {"
        "    width: 16px;"
        "    height: 16px;"
        "    border-radius: 8px;"
        "    border: 2px solid #cccccc;"
        "    background-color: white;"
        "}"
        "QRadioButton::indicator:checked {"
        "    background-color: #4CAF50;"
        "    border-color: #45a049;"
        "}"
        "QPushButton {"
        "    border: none;"
        "    border-radius: 6px;"
        "    padding: 8px 16px;"
        "    font-size: 12px;"
        "    font-weight: bold;"
        "    min-width: 80px;"
        "    color: white; /* Белый текст на кнопках */"
        "}"
        "QPushButton#pushButton { /* Кнопка Назад */"
        "    background-color: #6c757d;"
        "}"
        "QPushButton#pushButton:hover {"
        "    background-color: #5a6268;"
        "}"
        "QPushButton#pushButton:pressed {"
        "    background-color: #4e555b;"
        "}"
        "QPushButton#pushButton_2 { /* Кнопка Добавить */"
        "    background-color: #28a745;"
        "}"
        "QPushButton#pushButton_2:hover {"
        "    background-color: #218838;"
        "}"
        "QPushButton#pushButton_2:pressed {"
        "    background-color: #1e7e34;"
        "}"
        "QPushButton#pushButton_2:disabled {"
        "    background-color: #cccccc;"
        "    color: #666666;"
        "}"
        );

    connect(ui->pushButton, &QPushButton::clicked, this, &add_users::on_backButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &add_users::on_addButton_clicked);

    connect(ui->Login, &QLineEdit::textChanged, this, &add_users::on_inputChanged);
    connect(ui->Password, &QLineEdit::textChanged, this, &add_users::on_inputChanged);
    connect(ui->student, &QRadioButton::toggled, this, &add_users::on_inputChanged);
    connect(ui->teacher, &QRadioButton::toggled, this, &add_users::on_inputChanged);

    connect(socket, &QTcpSocket::readyRead, this, &add_users::onServerResponse);

    ui->pushButton_2->setEnabled(false);
}

add_users::~add_users() {
    delete ui;
}

void add_users::on_backButton_clicked() {
    reject();
}

void add_users::on_addButton_clicked() {
    QString login = ui->Login->text().trimmed();
    QString password = ui->Password->text();
    QString position;

    if (ui->student->isChecked()) position = "student";
    else if (ui->teacher->isChecked()) position = "teacher";

    QJsonObject request;
    request["type"] = "add_user";
    request["login"] = login;
    request["password"] = password;
    request["position"] = position;

    // ✅ Отправляем компактный JSON + \n
    QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact) + "\n";
    socket->write(data);
    socket->flush();
}

void add_users::onServerResponse() {
    QJsonDocument response = QJsonDocument::fromJson(socket->readAll());
    QJsonObject obj = response.object();

    if (obj["type"] == "add_user") {
        if (obj["status"] == "ok") {
            QMessageBox::information(this, "Успех", "Пользователь добавлен!");
            ui->Login->clear();
            ui->Password->clear();
            ui->student->setChecked(false);
            ui->teacher->setChecked(false);
            on_inputChanged();
        } else {
            QMessageBox::critical(this, "Ошибка", obj["reason"].toString());
        }
    }
}

void add_users::on_inputChanged() {
    QString login = ui->Login->text().trimmed();
    QString password = ui->Password->text();
    bool roleSelected = ui->student->isChecked() || ui->teacher->isChecked();

    bool isLoginValid = login.length() >= 3;
    bool isPasswordValid = password.length() >= 4;
    ui->pushButton_2->setEnabled(isLoginValid && isPasswordValid && roleSelected);
}
