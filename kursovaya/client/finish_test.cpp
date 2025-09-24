#include "finish_test.h"
#include "ui_finish_test.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>
#include <QLabel>
#include <QRadioButton>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>

finish_test::finish_test(QTcpSocket *sharedSocket, int studentId, int testId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finish_test),
    socket(sharedSocket),
    studentId(studentId),
    testId(testId)
{
    ui->setupUi(this);

    currentQuestion = 0;
    score = 0;

    // список вопросов
    allQuestions = {"q1","q2","q3","q4","q5","q6","q7","q8","q9","q10"};
    std::shuffle(allQuestions.begin(), allQuestions.end(), *QRandomGenerator::global());

    // правильные ответы
    correctAnswers = {
        "A", "C", "C", "C", "C",
        "A", "A", "C", "B", "B"
    };

    givenAnswers.resize(allQuestions.size());
    for (int i = 0; i < givenAnswers.size(); ++i) givenAnswers[i] = "";

    // скрыть все вопросы и варианты
    for (int i = 1; i <= 10; i++) {
        if (auto *lbl = ui->groupBox->findChild<QLabel*>(QString("q%1").arg(i)))
            lbl->hide();
        for (auto c : {"A","B","C","D"}) {
            QString btnName = QString("%1_q%2").arg(c).arg(i);
            if (auto *rb = ui->groupBox->findChild<QRadioButton*>(btnName))
                rb->hide();
        }
    }

    ui->pushButton->hide();

    // таймер
    remainingTime = 5 * 60;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &finish_test::updateTimer);
    timer->start(1000);
    updateTimerLabel();

    // кнопка ответа
    ui->otvet->setEnabled(false);
    connect(ui->otvet, &QPushButton::clicked, this, &finish_test::submitAnswer);

    // 🔹 запрос к серверу, если уже есть результаты
    requestPreviousResult();

    // показываем первый вопрос
    showQuestion();
}

finish_test::~finish_test() {
    delete ui;
}

void finish_test::updateTimerLabel() {
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;
    QString timeStr = QString("%1:%2")
                          .arg(minutes, 2, 10, QChar('0'))
                          .arg(seconds, 2, 10, QChar('0'));
    if (ui->timeLabel)
        ui->timeLabel->setText(timeStr);
}

void finish_test::updateTimer() {
    if (remainingTime <= 0) {
        if (timer && timer->isActive()) timer->stop();
        finishTest();
        return;
    }
    updateTimerLabel();
    remainingTime--;
}

void finish_test::showQuestion() {
    if (currentQuestion >= allQuestions.size()) {
        finishTest();
        return;
    }

    QString qName = allQuestions[currentQuestion];
    if (auto *lbl = ui->groupBox->findChild<QLabel*>(qName))
        lbl->show();

    for (auto c : {"A","B","C","D"}) {
        QString btnName = QString("%1_%2").arg(c).arg(qName);
        if (auto *rb = ui->groupBox->findChild<QRadioButton*>(btnName)) {
            rb->show();
            rb->setEnabled(true);
            rb->disconnect(this);
            connect(rb, &QRadioButton::toggled, this, [=](bool checked){
                if (checked) ui->otvet->setEnabled(true);
            });
        }
    }
}

void finish_test::submitAnswer() {
    QString qName = allQuestions[currentQuestion];
    QString selected;

    for (auto c : {"A","B","C","D"}) {
        QString btnName = QString("%1_%2").arg(c).arg(qName);
        if (auto *rb = ui->groupBox->findChild<QRadioButton*>(btnName)) {
            if (rb->isChecked())
                selected = QString(c);

            rb->hide();
            rb->setEnabled(false);
            rb->setAutoExclusive(false);
            rb->setChecked(false);
            rb->setAutoExclusive(true);
        }
    }
    if (auto *lbl = ui->groupBox->findChild<QLabel*>(qName)) {
        lbl->hide();
        lbl->setEnabled(false);
    }

    givenAnswers[currentQuestion] = selected;

    int questionIndex = qName.mid(1).toInt() - 1;
    if (!selected.isEmpty() && questionIndex >= 0 && questionIndex < correctAnswers.size()) {
        if (selected == correctAnswers[questionIndex]) {
            if (questionIndex < 5) score += 1;
            else score += 2;
        }
    }

    currentQuestion++;
    if (currentQuestion >= allQuestions.size()) {
        finishTest();
    } else {
        ui->otvet->setEnabled(false);
        showQuestion();
    }
}

void finish_test::finishTest() {
    if (timer && timer->isActive())
        timer->stop();

    if (!alreadyPassed) {
        sendSaveResult();
        alreadyPassed = true;
        emit scoreUpdated(score);
    }

    if (socket) {
        QJsonObject obj;
        obj["type"] = "get_result";
        obj["student_id"] = studentId;
        obj["test_id"] = testId;
        socket->write(QJsonDocument(obj).toJson(QJsonDocument::Compact) + "\n");
        socket->flush();
    }

    ui->otvet->hide();
    ui->pushButton->show();
    connect(ui->pushButton, &QPushButton::clicked,
            this, &finish_test::accept, Qt::UniqueConnection);
}

void finish_test::sendSaveResult() {
    QJsonObject req;
    req["type"] = "save_result";
    req["student_id"] = studentId;
    req["test_id"] = testId;
    req["score"] = score;

    QJsonArray arr;
    for (const QString &ans : givenAnswers) {
        arr.append(ans);
    }
    req["answers"] = arr;

    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}

void finish_test::requestPreviousResult() {
    QJsonObject req;
    req["type"] = "get_result";
    req["student_id"] = studentId;
    req["test_id"] = testId;
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}

void finish_test::restoreAnswers(const QJsonArray &answers) {
    for (int i = 0; i < answers.size() && i < givenAnswers.size(); ++i) {
        givenAnswers[i] = answers[i].toString();
    }
}

void finish_test::onServerResponse() {
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();

    if (type == "get_result") {
        if (obj["status"] == "ok") {
            score = obj["score"].toInt();
            QJsonArray arr = obj["answers"].toArray();
            restoreAnswers(arr);
            alreadyPassed = true;
            emit scoreUpdated(score);
            ui->otvet->setVisible(false);
        } else if (obj["status"] == "empty") {
            alreadyPassed = false;
        }
    } else if (type == "save_result") {
        if (obj["status"] == "ok") {
            qDebug() << "Результат успешно сохранён";
        } else {
            qWarning() << "Ошибка сохранения:" << obj["message"].toString();
        }
    }
}
