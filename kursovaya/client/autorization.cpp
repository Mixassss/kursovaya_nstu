#include "autorization.h"
#include "ui_autorization.h"
#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , socket(new QTcpSocket(this))
{
    ui->setupUi(this);

    setFixedSize(300, 250);
    setWindowTitle("Авторизация");

    connect(ui->loginButton, &QPushButton::clicked, this, &Dialog::on_loginButton_clicked);
    connect(ui->backButton, &QPushButton::clicked, this, &Dialog::on_backButton_clicked);

    ui->loginButton->setEnabled(false);

    connect(ui->Login, &QLineEdit::textChanged, this, &Dialog::on_inputChanged);
    connect(ui->Password, &QLineEdit::textChanged, this, &Dialog::on_inputChanged);

    connect(socket, &QTcpSocket::readyRead, this, &Dialog::onServerResponse);

    socket->connectToHost("127.0.0.1", 9878); // подключаемся к серверу
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::on_loginButton_clicked() {
    QString login = ui->Login->text().trimmed();
    QString password = ui->Password->text();

    QJsonObject request;
    request["type"] = "auth";      // соответствует серверу
    request["login"] = login;
    request["password"] = password;

    // Преобразуем JSON в компактный формат и добавляем '\n' для серверной буферизации
    QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact) + "\n";
    qDebug() << "[CLIENT] Sending JSON:" << data;

    socket->write(data);
    socket->flush();
}


void Dialog::onServerResponse() {
    QJsonDocument response = QJsonDocument::fromJson(socket->readAll());
    QJsonObject obj = response.object();

    if (obj["type"] == "auth") {
        if (obj["status"] == "ok") {
            this->userPosition = obj["position"].toString();
            this->userId = obj["id"].toInt();
            accept();
        } else {
            QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
            ui->Password->clear();
            ui->Password->setFocus();
        }
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
    ui->loginButton->setEnabled(isLoginValid && isPasswordValid);
}
