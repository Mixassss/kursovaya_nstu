#include "delete_users.h"
#include "ui_delete_users.h"
#include "database.h"
#include <QMessageBox>
#include <QScrollArea>
#include <QWidget>

delete_users::delete_users(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::delete_users)
    , db(new Database(this))
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

    // Подключение к базе данных
    if (!db->connectToDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных");
    }

    // Создаем scroll area для списка пользователей
    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *scrollWidget = new QWidget();
    usersLayout = new QVBoxLayout(scrollWidget);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    // Добавляем scroll area в основной layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(ui->pushButton); // Кнопка "Назад"

    // Устанавливаем layout
    setLayout(mainLayout);

    // Подключаем кнопку "Назад"
    connect(ui->pushButton, &QPushButton::clicked, this, &delete_users::on_backButton_clicked);

    // Загружаем список пользователей
    refreshUsersList();
}

delete_users::~delete_users()
{
    delete ui;
}

void delete_users::refreshUsersList()
{
    // Очищаем текущий список
    QLayoutItem *item;
    while ((item = usersLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    if (!db->connectToDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Нет подключения к базе данных");
        return;
    }

    QSqlQuery query(db->getDatabase());
    query.prepare("SELECT id, login, position FROM users ORDER BY position, login");

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить список пользователей");
        return;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString login = query.value(1).toString();
        QString position = query.value(2).toString();

        // Создаем виджет для каждого пользователя
        QWidget *userWidget = new QWidget();
        QHBoxLayout *userLayout = new QHBoxLayout(userWidget);

        QLabel *userInfo = new QLabel(
            QString("%1 (%2)").arg(login).arg(
                position == "admin" ? "Администратор" :
                    position == "teacher" ? "Преподаватель" : "Ученик")
            );

        userLayout->addWidget(userInfo);

        // Добавляем кнопку удаления только для teacher и student
        if (position != "admin") {
            QPushButton *deleteButton = new QPushButton("Удалить");

            deleteButton->setStyleSheet(
                "QPushButton {"
                "    background-color: #ff4444;"
                "    color: white;"
                "    border: 1px solid #cc0000;"
                "    border-radius: 4px;"
                "    padding: 5px 10px;"
                "}"
                "QPushButton:hover {"
                "    background-color: #ff6666;"
                "}"
                "QPushButton:pressed {"
                "    background-color: #cc0000;"
                "}"
                );
            deleteButton->setProperty("userId", id);
            deleteButton->setProperty("userLogin", login);
            connect(deleteButton, &QPushButton::clicked, this, &delete_users::onDeleteButtonClicked);
            userLayout->addWidget(deleteButton);
        } else {
            // Для администраторов добавляем заглушку для выравнивания
            userLayout->addStretch();
        }

        usersLayout->addWidget(userWidget);
    }

    // Добавляем растяжку в конец
    usersLayout->addStretch();
}

void delete_users::on_backButton_clicked()
{
    reject();
}

void delete_users::onDeleteButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int userId = button->property("userId").toInt();
    QString userLogin = button->property("userLogin").toString();

    // Создаем кастомное сообщение с русскими кнопками
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Подтверждение удаления");
    msgBox.setText(QString("Вы уверены, что хотите удалить пользователя '%1'?").arg(userLogin));
    msgBox.setIcon(QMessageBox::Question);

    // Добавляем кнопки на русском
    QPushButton *yesButton = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *noButton = msgBox.addButton("Нет", QMessageBox::NoRole);

    msgBox.setDefaultButton(noButton);
    msgBox.exec();

    if (msgBox.clickedButton() == yesButton) {
        if (!db->connectToDatabase()) {
            QMessageBox::critical(this, "Ошибка", "Нет подключения к базе данных");
            return;
        }

        QSqlQuery query(db->getDatabase());
        query.prepare("DELETE FROM users WHERE id = :id");
        query.bindValue(":id", userId);

        if (query.exec()) {
            QMessageBox::information(this, "Успех", "Пользователь успешно удален");
            refreshUsersList(); // Обновляем список
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить пользователя");
        }
    }
}
