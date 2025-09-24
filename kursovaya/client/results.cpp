#include "results.h"
#include "ui_results.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QHeaderView>
#include <QStandardItemModel>

results::results(QTcpSocket *socket, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::results)
    , socket(socket)
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);

    // Кнопка "Назад" закрывает окно
    connect(ui->pushButton, &QPushButton::clicked, this, &QDialog::close);

    // Настроим размеры таблицы
    ui->tableView->setMinimumSize(611, 192);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // Прокрутка
    ui->tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    // Запрещаем редактирование
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Запрещаем изменение структуры
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setSectionsMovable(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    // Включаем сортировку
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);

    // Стили
    ui->tableView->setStyleSheet(
        "QTableView {"
        "   background-color: #1e3a5f;"
        "   color: white;"
        "   gridline-color: #c0c0c0;"
        "   font-size: 14px;"
        "   selection-background-color: #0078d7;"
        "   selection-color: white;"
        "   border: 1px solid #a0a0a0;"
        "}"
        "QHeaderView::section {"
        "   background-color: #27496d;"
        "   color: white;"
        "   padding: 4px;"
        "   border: 1px solid #a0a0a0;"
        "   font-weight: bold;"
        "}"
        );

    // Заголовки колонок
    model->setHorizontalHeaderLabels({"Логин", "Тест ID", "Оценка", "Ответы"});
    ui->tableView->setModel(model);

    loadResults();
}

results::~results()
{
    delete ui;
}

void results::loadResults()
{
    // Отправляем запрос серверу
    QJsonObject req;
    req["type"] = "list_results";
    QByteArray data = QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n";
    qDebug() << "Sending request to server:" << QString(QJsonDocument(req).toJson(QJsonDocument::Compact)); // Логирование отправки запроса
    socket->write(data);
    socket->flush();

    // Ждём ответа
    if (!socket->waitForReadyRead(3000)) {
        qWarning() << "Нет ответа от сервера";
        return;
    }

    QByteArray respData = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(respData);
    if (!doc.isObject()) {
        qWarning() << "Ответ не является JSON объектом!";
        return;
    }

    // Логирование полученного ответа
    qDebug() << "Received response from server:" << doc.toJson(QJsonDocument::Indented);

    QJsonObject obj = doc.object();
    if (obj["type"] == "list_results" && obj["status"] == "ok") {
        QJsonArray arr = obj["results"].toArray();

        for (auto r : arr) {
            QJsonObject row = r.toObject();

            QString login = row["login"].toString();
            int testId = row["test_id"].toInt();
            int score = row["score"].toInt();

            QStringList answers;
            if (row.contains("answers") && row["answers"].isArray()) {
                QJsonArray arr = row["answers"].toArray();
                for (const QJsonValue &val : arr) {
                    if (val.isString())
                        answers << val.toString();
                }
            }

            // Логирование обработки каждого результата
            qDebug() << "Processing result for Login:" << login
                     << "Test ID:" << testId
                     << "Score:" << score
                     << "Answers:" << (answers.isEmpty() ? "No answers" : answers.join(", "));

            // Логирование пустых ответов
            if (answers.isEmpty()) {
                qDebug() << "No answers for Login:" << login << "Test ID:" << testId;
            }

            QList<QStandardItem*> items;
            items << new QStandardItem(login)
                  << new QStandardItem(QString::number(testId))
                  << new QStandardItem(QString::number(score))
                  << new QStandardItem(answers.isEmpty() ? "Нет ответов" : answers.join(", "));

            // Логирование перед добавлением в модель
            qDebug() << "Adding row to model:" << login << testId << score << (answers.isEmpty() ? "Нет ответов" : answers.join(", "));
            model->appendRow(items);
        }
    }
}


