#include "zadania3.h"
#include "ui_zadania3.h"
#include "test1.h"

zadania3::zadania3(QTcpSocket *sharedSocket, int currentUserId, QWidget *parent)
    : QDialog(parent), ui(new Ui::zadania3), socket(sharedSocket), userId(currentUserId)
{
    ui->setupUi(this);

    alreadyPassed = false;

    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_6->setEnabled(false);

    QList<QRadioButton*> buttons = {
        ui->AnswerA, ui->AnswerB, ui->AnswerC, ui->AnswerD,
        ui->AnswerA_2, ui->AnswerB_2, ui->AnswerC_2, ui->AnswerD_2,
        ui->AnswerA_3, ui->AnswerB_3, ui->AnswerC_3, ui->AnswerD_3
    };
    for (auto btn : buttons)
        connect(btn, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);

    connect(ui->pushButton,   &QPushButton::clicked, this, &zadania3::on_backButton_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &zadania3::onBackClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &zadania3::on_pushButton_2_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &zadania3::on_pushButton_6_clicked);

    connect(socket, &QTcpSocket::readyRead, this, &zadania3::onServerResponse);

    // запрос результата для test_id=3
    QJsonObject req;
    req["type"] = "get_result";
    req["student_id"] = userId;
    req["test_id"] = 3;
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}

zadania3::~zadania3() {
    delete ui;
}

// ===================== вспомогательные =====================

void zadania3::lockAnswers() {
    QList<QRadioButton*> buttons = {
        ui->AnswerA, ui->AnswerB, ui->AnswerC, ui->AnswerD,
        ui->AnswerA_2, ui->AnswerB_2, ui->AnswerC_2, ui->AnswerD_2,
        ui->AnswerA_3, ui->AnswerB_3, ui->AnswerC_3, ui->AnswerD_3
    };
    for (auto btn : buttons) btn->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
}

void zadania3::resetAnswers() {
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

void zadania3::sendSaveResult(int score) {
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

    QJsonObject req;
    req["type"] = "save_result";
    req["student_id"] = userId;
    req["test_id"] = 3;
    req["score"] = score;
    req["answer1"] = answer1;
    req["answer2"] = answer2;
    req["answer3"] = answer3;

    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}

void zadania3::restoreAnswersAndHighlight(const QString &a1, const QString &a2, const QString &a3) {
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

void zadania3::on_pushButton_6_clicked() {
    bool firstCorrect = ui->AnswerB->isChecked();
    bool secondCorrect = ui->AnswerC_2->isChecked();
    bool thirdCorrect = ui->AnswerD_3->isChecked();

    int score = 0;
    if (firstCorrect) score+= 2;
    if (secondCorrect) score+= 2;
    if (thirdCorrect) score += 2;
    if (score > 6) score = 6;

    lockAnswers();
    updateButtonsVisibility();

    if (!alreadyPassed) {
        sendSaveResult(score);
        alreadyPassed = true;
        emit scoreUpdated(score);
    }
}


// ===================== сервер =====================

void zadania3::onServerResponse() {
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    if (obj["type"] == "get_result") {
        if (obj["status"] == "ok") {
            int score = obj["score"].toInt();
            lastAnswer1 = obj["answer1"].toString();
            lastAnswer2 = obj["answer2"].toString();
            lastAnswer3 = obj["answer3"].toString();

            alreadyPassed = true;
            restoreAnswersAndHighlight(lastAnswer1, lastAnswer2, lastAnswer3);
            ui->pushButton_6->setVisible(false);
            emit scoreUpdated(score);
        } else if (obj["status"] == "empty") {
            alreadyPassed = false;
        }
    }
}

void zadania3::updateSubmitButtonState() {
    if (alreadyPassed) {
        ui->pushButton_6->setEnabled(false);
        return;
    }

    bool g1 = ui->AnswerA->isChecked() || ui->AnswerB->isChecked() || ui->AnswerC->isChecked() || ui->AnswerD->isChecked();
    bool g2 = ui->AnswerA_2->isChecked() || ui->AnswerB_2->isChecked() || ui->AnswerC_2->isChecked() || ui->AnswerD_2->isChecked();
    bool g3 = ui->AnswerA_3->isChecked() || ui->AnswerB_3->isChecked() || ui->AnswerC_3->isChecked() || ui->AnswerD_3->isChecked();

    ui->pushButton_6->setEnabled(g1 && g2 && g3);
}

void zadania3::updateButtonsVisibility() {
    bool firstCorrect = ui->AnswerB->isChecked();
    bool secondCorrect = ui->AnswerA_2->isChecked();
    bool thirdCorrect = ui->AnswerA_3->isChecked();

    // Подсветка
    if (ui->AnswerA->isChecked()) ui->AnswerA->setStyleSheet("background-color: red;");
    if (ui->AnswerB->isChecked()) ui->AnswerB->setStyleSheet("background-color: green;");
    if (ui->AnswerC->isChecked()) ui->AnswerC->setStyleSheet("background-color: red;");
    if (ui->AnswerD->isChecked()) ui->AnswerD->setStyleSheet("background-color: red;");

    if (ui->AnswerA_2->isChecked()) ui->AnswerA_2->setStyleSheet("background-color: red;");
    if (ui->AnswerB_2->isChecked()) ui->AnswerB_2->setStyleSheet("background-color: red;");
    if (ui->AnswerC_2->isChecked()) ui->AnswerC_2->setStyleSheet("background-color: green;");
    if (ui->AnswerD_2->isChecked()) ui->AnswerD_2->setStyleSheet("background-color: red;");

    if (ui->AnswerA_3->isChecked()) ui->AnswerA_3->setStyleSheet("background-color: red;");
    if (ui->AnswerB_3->isChecked()) ui->AnswerB_3->setStyleSheet("background-color: red;");
    if (ui->AnswerC_3->isChecked()) ui->AnswerC_3->setStyleSheet("background-color: red;");
    if (ui->AnswerD_3->isChecked()) ui->AnswerD_3->setStyleSheet("background-color: green;");

    // Логика кнопок
    if (firstCorrect && secondCorrect && thirdCorrect) {
        ui->pushButton->setVisible(true);
        ui->pushButton_5->setVisible(true);
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(false);
    } else if (firstCorrect || secondCorrect || thirdCorrect) {
        ui->pushButton->setVisible(true);
        ui->pushButton_5->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->pushButton_3->setVisible(false);
    } else {
        ui->pushButton->setVisible(true);
        ui->pushButton_5->setVisible(false);
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(true);
    }
}

// ===================== кнопки =====================

void zadania3::on_backButton_clicked() {
    if (alreadyPassed) {
        restoreAnswersAndHighlight(lastAnswer1, lastAnswer2, lastAnswer3);
    }
    reject();
}

void zadania3::onBackClicked() {
    if (alreadyPassed) {
        restoreAnswersAndHighlight(lastAnswer1, lastAnswer2, lastAnswer3);
    }
    test1 *lectionWindow = new test1();
    lectionWindow->setModal(true);
    this->close();
    lectionWindow->show();
}

void zadania3::on_pushButton_2_clicked() {
    alreadyPassed = false;
    resetAnswers();

    ui->pushButton_5->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_6->setVisible(true);
}
