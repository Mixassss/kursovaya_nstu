#include "delete_users.h"
#include "ui_delete_users.h"
#include <QMessageBox>
#include <QScrollArea>
#include <QJsonArray>
#include <QJsonValue>

delete_users::delete_users(QTcpSocket *sharedSocket, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::delete_users)
    , socket(sharedSocket)
{
    ui->setupUi(this);

    this->setStyleSheet(
        "QLabel {"
        "    font-size: 12px;"
        "    padding: 5px;"
        "}"
        "QPushButton {"
        "    padding: 5px 10px;"
        "    border-radius: 4px;"
        "}"
        "QPushButton#pushButton { /* Кнопка Назад */"
        "    background-color: #6c757d;"
        "    color: white;"
        "}"
        "QPushButton#pushButton:hover {"
        "    background-color: #5a6268;"
        "}"
        );

    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *scrollWidget = new QWidget();
    usersLayout = new QVBoxLayout(scrollWidget);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(ui->pushButton);

    setLayout(mainLayout);

    connect(ui->pushButton, &QPushButton::clicked, this, &delete_users::on_backButton_clicked);
    connect(socket, &QTcpSocket::readyRead, this, &delete_users::onServerResponse);

    requestUsersList();
}

delete_users::~delete_users() {
    delete ui;
}

void delete_users::requestUsersList() {
    QJsonObject request;
    request["type"] = "list_users";
    QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact) + "\n";
    socket->write(data);
    socket->flush();
}

void delete_users::onServerResponse() {
    QJsonDocument response = QJsonDocument::fromJson(socket->readAll());
    QJsonObject obj = response.object();

    if (obj["type"] == "list_users") {
        QLayoutItem *item;
        while ((item = usersLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }

        QJsonArray users = obj["users"].toArray();
        for (auto u : users) {
            QJsonObject userObj = u.toObject();
            int id = userObj["id"].toInt();
            QString login = userObj["login"].toString();
            QString position = userObj["position"].toString();

            QWidget *userWidget = new QWidget();
            QHBoxLayout *userLayout = new QHBoxLayout(userWidget);

            QLabel *userInfo = new QLabel(QString("%1 (%2)").arg(login).arg(position));
            userLayout->addWidget(userInfo);

            if (position != "admin") {
                QPushButton *deleteButton = new QPushButton("Удалить");
                deleteButton->setProperty("userId", id);
                deleteButton->setProperty("userLogin", login);

                deleteButton->setStyleSheet(
                    "QPushButton {"
                    "    background-color: #dc3545;"
                    "    color: white;"
                    "    border-radius: 4px;"
                    "    padding: 5px 10px;"
                    "}"
                    "QPushButton:hover {"
                    "    background-color: #c82333;"
                    "}"
                    );

                connect(deleteButton, &QPushButton::clicked, this, &delete_users::onDeleteButtonClicked);
                userLayout->addWidget(deleteButton);
            } else {
                userLayout->addStretch();
            }

            usersLayout->addWidget(userWidget);
        }
        usersLayout->addStretch();
    }
    else if (obj["type"] == "delete_user") {
        if (obj["status"] == "ok") {
            QMessageBox::information(this, "Успех", "Пользователь удален");
            requestUsersList();
        } else {
            QMessageBox::critical(this, "Ошибка", obj["reason"].toString());
        }
    }
}

void delete_users::onDeleteButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int userId = button->property("userId").toInt();
    QString userLogin = button->property("userLogin").toString();

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Подтверждение удаления");
    msgBox.setText(QString("Удалить пользователя '%1'?").arg(userLogin));
    msgBox.setIcon(QMessageBox::Question);
    QPushButton *yesButton = msgBox.addButton("Да", QMessageBox::YesRole);
    msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.exec();

    if (msgBox.clickedButton() == yesButton) {
        QJsonObject request;
        request["type"] = "delete_user";
        request["id"] = userId;

        QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact) + "\n";
        socket->write(data);
        socket->flush();
    }
}

void delete_users::on_backButton_clicked() {
    reject();
}
