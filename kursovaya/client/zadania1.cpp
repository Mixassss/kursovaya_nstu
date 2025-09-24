#include "zadania1.h"
#include "ui_zadania1.h"
#include "test1.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>

zadania1::zadania1(QTcpSocket *sharedSocket, int currentUserId, QWidget *parent)
    : QDialog(parent), ui(new Ui::zadania1), socket(sharedSocket), userId(currentUserId)
{
    ui->setupUi(this);

    alreadyPassed = false;

    // Скрываем навигационные кнопки
    ui->pushButton_5->setVisible(false);
    ui->pushButton_3->setVisible(false);

    ui->pushButton_4->setEnabled(false);

    QList<QRadioButton*> buttons = {
        ui->AnswerA, ui->AnswerB, ui->AnswerC, ui->AnswerD,
        ui->AnswerA_2, ui->AnswerB_2, ui->AnswerC_2, ui->AnswerD_2
    };

    // Сразу включаем кнопки, если пользователь впервые
    for (auto btn : buttons) btn->setEnabled(true);

    // Подключаем слоты для радиокнопок
    for (auto btn : buttons)
        connect(btn, &QRadioButton::toggled, this, &zadania1::updateSubmitButtonState);

    // Кнопки
    connect(ui->pushButton_3, &QPushButton::clicked, this, &zadania1::onBackClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &zadania1::on_pushButton_5_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &zadania1::on_pushButton_4_clicked);
    connect(socket, &QTcpSocket::readyRead, this, &zadania1::onServerResponse);

    // Запросим последний результат
    QJsonObject req;
    req["type"] = "get_result";
    req["student_id"] = userId;
    req["test_id"] = 1;
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}

zadania1::~zadania1() {
    delete ui;
}

// ===================== вспомогательные =====================

void zadania1::lockAnswers() {
    QList<QRadioButton*> buttons = {
        ui->AnswerA, ui->AnswerB, ui->AnswerC, ui->AnswerD,
        ui->AnswerA_2, ui->AnswerB_2, ui->AnswerC_2, ui->AnswerD_2
    };
    for (auto btn : buttons) btn->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
}

void zadania1::resetAnswers() {
    QList<QRadioButton*> buttons = {
        ui->AnswerA, ui->AnswerB, ui->AnswerC, ui->AnswerD,
        ui->AnswerA_2, ui->AnswerB_2, ui->AnswerC_2, ui->AnswerD_2
    };
    for (auto btn : buttons) {
        btn->setAutoExclusive(false);
        btn->setChecked(false);
        btn->setStyleSheet("");
        btn->setAutoExclusive(true);
        btn->setEnabled(true);
    }
    ui->pushButton_4->setEnabled(false);
}

void zadania1::sendSaveResult(int score) {
    QString answer1, answer2;
    if (ui->AnswerA->isChecked()) answer1 = "A";
    if (ui->AnswerB->isChecked()) answer1 = "B";
    if (ui->AnswerC->isChecked()) answer1 = "C";
    if (ui->AnswerD->isChecked()) answer1 = "D";

    if (ui->AnswerA_2->isChecked()) answer2 = "A";
    if (ui->AnswerB_2->isChecked()) answer2 = "B";
    if (ui->AnswerC_2->isChecked()) answer2 = "C";
    if (ui->AnswerD_2->isChecked()) answer2 = "D";

    QJsonArray answers;
    answers.append(answer1);
    answers.append(answer2);

    QJsonObject req;
    req["type"] = "save_result";
    req["student_id"] = userId;
    req["test_id"] = 1;
    req["score"] = score;
    req["answers"] = answers;

    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}


// ===================== логика теста =====================

void zadania1::on_pushButton_4_clicked() {
    bool firstGroupAnswered = ui->AnswerA->isChecked() || ui->AnswerB->isChecked()
    || ui->AnswerC->isChecked() || ui->AnswerD->isChecked();
    bool secondGroupAnswered = ui->AnswerA_2->isChecked() || ui->AnswerB_2->isChecked()
                               || ui->AnswerC_2->isChecked() || ui->AnswerD_2->isChecked();

    if (!firstGroupAnswered || !secondGroupAnswered) {
        QMessageBox::warning(this, "Ошибка", "Вы должны выбрать ответ в обеих группах!");
        return;
    }

    int score = 0;
    if (ui->AnswerB->isChecked()) score++;
    if (ui->AnswerC_2->isChecked()) score++;

    lockAnswers();
    updateButtonsVisibility();

    sendSaveResult(score);
    alreadyPassed = true;
    emit scoreUpdated(score);

    if (score == 2) {
        QMessageBox::information(this, "Поздравляем",
                                 "Поздравляем! Тест пройден на 2 из 2.");
        this->close(); // Закрываем текущее окно zadania1
    }
}

void zadania1::updateSubmitButtonState() {
    bool firstGroupSelected = ui->AnswerA->isChecked() || ui->AnswerB->isChecked()
    || ui->AnswerC->isChecked() || ui->AnswerD->isChecked();
    bool secondGroupSelected = ui->AnswerA_2->isChecked() || ui->AnswerB_2->isChecked()
                               || ui->AnswerC_2->isChecked() || ui->AnswerD_2->isChecked();

    ui->pushButton_4->setEnabled(firstGroupSelected && secondGroupSelected);
}

void zadania1::updateButtonsVisibility() {
    bool firstGroupCorrect = ui->AnswerB->isChecked();
    bool secondGroupCorrect = ui->AnswerC_2->isChecked();

    // Подсветка
    if (ui->AnswerA->isChecked()) ui->AnswerA->setStyleSheet("background-color: red;");
    if (ui->AnswerB->isChecked()) ui->AnswerB->setStyleSheet("background-color: green;");
    if (ui->AnswerC->isChecked()) ui->AnswerC->setStyleSheet("background-color: red;");
    if (ui->AnswerD->isChecked()) ui->AnswerD->setStyleSheet("background-color: red;");

    if (ui->AnswerA_2->isChecked()) ui->AnswerA_2->setStyleSheet("background-color: red;");
    if (ui->AnswerB_2->isChecked()) ui->AnswerB_2->setStyleSheet("background-color: red;");
    if (ui->AnswerC_2->isChecked()) ui->AnswerC_2->setStyleSheet("background-color: green;");
    if (ui->AnswerD_2->isChecked()) ui->AnswerD_2->setStyleSheet("background-color: red;");

    // Логика кнопок
    if (firstGroupCorrect && secondGroupCorrect) {
        ui->pushButton_5->setVisible(false); // перепройти нельзя
        ui->pushButton_3->setVisible(false);
    } else {
        ui->pushButton_5->setVisible(true); // можно перепройти
        ui->pushButton_3->setVisible(true);
    }
}

// ===================== ответы от сервера =====================

void zadania1::onServerResponse() {
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    if (obj["type"] == "get_result") {
        if (obj["status"] == "ok") {
            int score = obj["score"].toInt();
            QJsonArray arr = obj["answers"].toArray();
            if (arr.size() >= 2) {
                lastAnswer1 = arr.at(0).toString();
                lastAnswer2 = arr.at(1).toString();
                alreadyPassed = true;
                restoreAnswersAndHighlight(lastAnswer1, lastAnswer2);
            }

            ui->pushButton_4->setVisible(false);
            emit scoreUpdated(score);
        } else if (obj["status"] == "empty") {
            QList<QRadioButton*> buttons = {
                ui->AnswerA, ui->AnswerB, ui->AnswerC, ui->AnswerD,
                ui->AnswerA_2, ui->AnswerB_2, ui->AnswerC_2, ui->AnswerD_2
            };
            for (auto btn : buttons) btn->setEnabled(true);
            alreadyPassed = false;
        }
    }
}

// ===================== кнопки =====================

void zadania1::on_pushButton_5_clicked() {
    alreadyPassed = false;   // сбрасываем статус
    resetAnswers();          // сбрасываем ответы
    ui->pushButton_5->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(true);
}

void zadania1::onBackClicked() {
    test1 *lectionWindow = new test1();
    lectionWindow->setModal(true);
    this->close();
    lectionWindow->show();
}

void zadania1::restoreAnswersAndHighlight(const QString &answer1, const QString &answer2) {
    if (answer1 == "A") ui->AnswerA->setChecked(true);
    else if (answer1 == "B") ui->AnswerB->setChecked(true);
    else if (answer1 == "C") ui->AnswerC->setChecked(true);
    else if (answer1 == "D") ui->AnswerD->setChecked(true);

    if (answer2 == "A") ui->AnswerA_2->setChecked(true);
    else if (answer2 == "B") ui->AnswerB_2->setChecked(true);
    else if (answer2 == "C") ui->AnswerC_2->setChecked(true);
    else if (answer2 == "D") ui->AnswerD_2->setChecked(true);

    lockAnswers();
    updateButtonsVisibility();
}
