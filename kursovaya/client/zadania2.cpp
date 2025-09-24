#include "zadania2.h"
#include "ui_zadania2.h"
#include "test2.h"
#include <QJsonArray>

zadania2::zadania2(QTcpSocket *sharedSocket, int currentUserId, QWidget *parent)
    : QDialog(parent), ui(new Ui::zadania2), socket(sharedSocket), userId(currentUserId)
{
    ui->setupUi(this);

    alreadyPassed = false;

    // скрываем кнопки
    ui->pushButton_2->setVisible(false); // теория
    ui->pushButton_3->setVisible(false); // теория
    ui->pushButton_6->setEnabled(false); // "ответить"

    // подключаем радиокнопки
    QList<QRadioButton*> buttons = {
        ui->AnswerA, ui->AnswerB, ui->AnswerC, ui->AnswerD,
        ui->AnswerA_2, ui->AnswerB_2, ui->AnswerC_2, ui->AnswerD_2,
        ui->AnswerA_3, ui->AnswerB_3, ui->AnswerC_3, ui->AnswerD_3
    };
    for (auto btn : buttons)
        connect(btn, &QRadioButton::toggled, this, &zadania2::updateSubmitButtonState);

    // навигация
    connect(ui->pushButton_3, &QPushButton::clicked, this, &zadania2::onBackClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &zadania2::on_pushButton_2_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &zadania2::on_pushButton_6_clicked);

    connect(socket, &QTcpSocket::readyRead, this, &zadania2::onServerResponse);

    // запрос результата для test_id=2
    QJsonObject req;
    req["type"] = "get_result";
    req["student_id"] = userId;
    req["test_id"] = 2;
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}

zadania2::~zadania2() {
    delete ui;
}

// ===================== вспомогательные =====================

void zadania2::lockAnswers() {
    QList<QRadioButton*> buttons = {
        ui->AnswerA, ui->AnswerB, ui->AnswerC, ui->AnswerD,
        ui->AnswerA_2, ui->AnswerB_2, ui->AnswerC_2, ui->AnswerD_2,
        ui->AnswerA_3, ui->AnswerB_3, ui->AnswerC_3, ui->AnswerD_3
    };
    for (auto btn : buttons) btn->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
}

void zadania2::resetAnswers() {
    QList<QRadioButton*> buttons = {
        ui->AnswerA, ui->AnswerB, ui->AnswerC, ui->AnswerD,
        ui->AnswerA_2, ui->AnswerB_2, ui->AnswerC_2, ui->AnswerD_2,
        ui->AnswerA_3, ui->AnswerB_3, ui->AnswerC_3, ui->AnswerD_3
    };

    for (auto btn : buttons) {
        btn->setAutoExclusive(false);
        btn->setChecked(false);
        btn->setStyleSheet("");
        btn->setAutoExclusive(true);
        btn->setEnabled(true);
    }

    ui->pushButton_6->setEnabled(false);
}

void zadania2::sendSaveResult(int score) {
    QString answer1, answer2, answer3;

    if (ui->AnswerA->isChecked()) answer1 = "A";
    if (ui->AnswerB->isChecked()) answer1 = "B";
    if (ui->AnswerC->isChecked()) answer1 = "C";
    if (ui->AnswerD->isChecked()) answer1 = "D";

    if (ui->AnswerA_2->isChecked()) answer2 = "A";
    if (ui->AnswerB_2->isChecked()) answer2 = "B";
    if (ui->AnswerC_2->isChecked()) answer2 = "C";
    if (ui->AnswerD_2->isChecked()) answer2 = "D";

    if (ui->AnswerA_3->isChecked()) answer3 = "A";
    if (ui->AnswerB_3->isChecked()) answer3 = "B";
    if (ui->AnswerC_3->isChecked()) answer3 = "C";
    if (ui->AnswerD_3->isChecked()) answer3 = "D";

    QJsonArray answers;
    answers.append(answer1);
    answers.append(answer2);
    answers.append(answer3);

    QJsonObject req;
    req["type"] = "save_result";
    req["student_id"] = userId;
    req["test_id"] = 2;
    req["score"] = score;
    req["answers"] = answers;

    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}

void zadania2::restoreAnswersAndHighlight(const QString &a1, const QString &a2, const QString &a3) {
    if (a1 == "A") ui->AnswerA->setChecked(true);
    else if (a1 == "B") ui->AnswerB->setChecked(true);
    else if (a1 == "C") ui->AnswerC->setChecked(true);
    else if (a1 == "D") ui->AnswerD->setChecked(true);

    if (a2 == "A") ui->AnswerA_2->setChecked(true);
    else if (a2 == "B") ui->AnswerB_2->setChecked(true);
    else if (a2 == "C") ui->AnswerC_2->setChecked(true);
    else if (a2 == "D") ui->AnswerD_2->setChecked(true);

    if (a3 == "A") ui->AnswerA_3->setChecked(true);
    else if (a3 == "B") ui->AnswerB_3->setChecked(true);
    else if (a3 == "C") ui->AnswerC_3->setChecked(true);
    else if (a3 == "D") ui->AnswerD_3->setChecked(true);

    lockAnswers();
    updateButtonsVisibility();
}

// ===================== логика =====================

void zadania2::on_pushButton_6_clicked() {
    bool firstCorrect = ui->AnswerB->isChecked();
    bool secondCorrect = ui->AnswerA_2->isChecked();
    bool thirdCorrect = ui->AnswerA_3->isChecked();

    int score = 0;
    if (firstCorrect) score++;
    if (secondCorrect) score++;
    if (thirdCorrect) score += 2;
    if (score > 4) score = 4;

    lockAnswers();
    updateButtonsVisibility();

    if (!alreadyPassed) {
        sendSaveResult(score);
        alreadyPassed = true;
        emit scoreUpdated(score);
    }

    // 🔹 Проверка на максимальный результат
    if (score == 4) {
        QMessageBox::information(this, "Поздравляем",
                                 "Поздравляем! Тест 2 пройден на 4 из 4.");
        this->close();
    }
}

void zadania2::updateSubmitButtonState() {
    if (alreadyPassed) {
        ui->pushButton_6->setEnabled(false);
        return;
    }

    bool g1 = ui->AnswerA->isChecked() || ui->AnswerB->isChecked() || ui->AnswerC->isChecked() || ui->AnswerD->isChecked();
    bool g2 = ui->AnswerA_2->isChecked() || ui->AnswerB_2->isChecked() || ui->AnswerC_2->isChecked() || ui->AnswerD_2->isChecked();
    bool g3 = ui->AnswerA_3->isChecked() || ui->AnswerB_3->isChecked() || ui->AnswerC_3->isChecked() || ui->AnswerD_3->isChecked();

    ui->pushButton_6->setEnabled(g1 && g2 && g3);
}

void zadania2::updateButtonsVisibility() {
    bool firstCorrect = ui->AnswerB->isChecked();
    bool secondCorrect = ui->AnswerA_2->isChecked();
    bool thirdCorrect = ui->AnswerA_3->isChecked();

    // Подсветка
    if (ui->AnswerA->isChecked()) ui->AnswerA->setStyleSheet("background-color: red;");
    if (ui->AnswerB->isChecked()) ui->AnswerB->setStyleSheet("background-color: green;");
    if (ui->AnswerC->isChecked()) ui->AnswerC->setStyleSheet("background-color: red;");
    if (ui->AnswerD->isChecked()) ui->AnswerD->setStyleSheet("background-color: red;");

    if (ui->AnswerA_2->isChecked()) ui->AnswerA_2->setStyleSheet("background-color: green;");
    if (ui->AnswerB_2->isChecked()) ui->AnswerB_2->setStyleSheet("background-color: red;");
    if (ui->AnswerC_2->isChecked()) ui->AnswerC_2->setStyleSheet("background-color: red;");
    if (ui->AnswerD_2->isChecked()) ui->AnswerD_2->setStyleSheet("background-color: red;");

    if (ui->AnswerA_3->isChecked()) ui->AnswerA_3->setStyleSheet("background-color: green;");
    if (ui->AnswerB_3->isChecked()) ui->AnswerB_3->setStyleSheet("background-color: red;");
    if (ui->AnswerC_3->isChecked()) ui->AnswerC_3->setStyleSheet("background-color: red;");
    if (ui->AnswerD_3->isChecked()) ui->AnswerD_3->setStyleSheet("background-color: red;");

    // Логика кнопок
    if (firstCorrect && secondCorrect && thirdCorrect) {
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(false);
    } else if (firstCorrect || secondCorrect || thirdCorrect) {
        ui->pushButton_2->setVisible(true);
        ui->pushButton_3->setVisible(true);
    } else {
        ui->pushButton_2->setVisible(true);
        ui->pushButton_3->setVisible(true);
    }
}


// ===================== сервер =====================

void zadania2::onServerResponse() {
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    if (obj["type"] == "get_result") {
        if (obj["status"] == "ok") {
            int score = obj["score"].toInt();
            QJsonArray arr = obj["answers"].toArray();
            if (arr.size() >= 3) {
                lastAnswer1 = arr.at(0).toString();
                lastAnswer2 = arr.at(1).toString();
                lastAnswer3 = arr.at(2).toString();
                alreadyPassed = true;
                restoreAnswersAndHighlight(lastAnswer1, lastAnswer2, lastAnswer3);
            }
            ui->pushButton_6->setVisible(false);
            emit scoreUpdated(score);
        } else if (obj["status"] == "empty") {
            alreadyPassed = false;
        }
    }
}

// ===================== кнопки навигации =====================

void zadania2::onBackClicked() {
    if (alreadyPassed) {
        restoreAnswersAndHighlight(lastAnswer1, lastAnswer2, lastAnswer3);
    }
    test2 *lectionWindow = new test2();
    lectionWindow->setModal(true);
    this->close();
    lectionWindow->show();
}

void zadania2::on_pushButton_2_clicked() {
    alreadyPassed = false;
    resetAnswers();

    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_6->setVisible(true);
}
