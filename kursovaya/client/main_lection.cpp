#include "main_lection.h"
#include "ui_main_lection.h"
#include "zadania1.h" // Подключаем класс zadania1
#include "zadania2.h" // Подключаем класс zadania2
#include "zadania3.h" // Подключаем класс zadania3
#include "zadania4.h" // Подключаем класс zadania4
#include "test1.h" // Подключаем класс test1
#include "test2.h" // Подключаем класс test2
#include "test3.h" // Подключаем класс test3
#include "dialog_window_exit.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "finish_test.h"


main_lection::main_lection(QTcpSocket *sharedSocket, int currentUserId, QWidget *parent)
    : QDialog(parent), ui(new Ui::main_lection), socket(sharedSocket), userId(currentUserId)
{
    ui->setupUi(this);

    // Подключаем сигнал clicked() кнопки "Основы программирования. Вопросы легкой сложности"
    connect(ui->easy_question, &QCommandLinkButton::clicked, this, &main_lection::on_easy_question_clicked);

    // Подключаем сигнал clicked() кнопки "Основы программирования. Вопросы средней сложности"
    connect(ui->middle_question, &QCommandLinkButton::clicked, this, &main_lection::on_middle_question_clicked);

    // Подключаем сигнал clicked() кнопки "Основы программирования. Вопросы высокой сложности"
    connect(ui->hard_question, &QCommandLinkButton::clicked, this, &main_lection::on_hard_question_clicked);

    // Подключаем сигнал clicked() кнопки "Основы программирования. Работа с кодом"
    connect(ui->question_withcode, &QCommandLinkButton::clicked, this, &main_lection::on_code_question_clicked);

    // Подключаем сигнал clicked() кнопки "Основы программирования. Работа с кодом"
    connect(ui->Lection1, &QCommandLinkButton::clicked, this, &main_lection::on_lection1_clicked);

    // Подключаем сигнал clicked() кнопки "Основы программирования. Работа с кодом"
    connect(ui->Lection2, &QCommandLinkButton::clicked, this, &main_lection::on_lection2_clicked);

    // Подключаем сигнал clicked() кнопки "Основы программирования. Работа с кодом"
    connect(ui->Lection3, &QCommandLinkButton::clicked, this, &main_lection::on_lection3_clicked);

    connect(ui->back, &QPushButton::clicked, this, &main_lection::on_backButton_clicked);

    // Подключаем сигнал clicked() кнопки "Выход из системы" к слоту
    connect(ui->quit_system, &QPushButton::clicked, this, &main_lection::on_exitButton_clicked);

    connect(ui->itogovoe_testirovanie, &QCommandLinkButton::clicked, this, &main_lection::on_finish_test_clicked);


    connect(socket, &QTcpSocket::readyRead, this, &main_lection::onServerResponse);

    requestTestResults();
}

main_lection::~main_lection() {
    delete ui;
}

void main_lection::onServerResponse() {
    socketBuffer.append(socket->readAll());

    int index;
    while ((index = socketBuffer.indexOf('\n')) != -1) {
        QByteArray line = socketBuffer.left(index);
        socketBuffer.remove(0, index + 1);

        if (line.trimmed().isEmpty()) continue;

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(line, &error);
        if (error.error != QJsonParseError::NoError) {
            qWarning() << "[CLIENT] JSON parse error:" << error.errorString() << "Data:" << line;
            continue;
        }

        if (!doc.isObject()) {
            qWarning() << "[CLIENT] Not a JSON object! Data:" << line;
            continue;
        }

        QJsonObject obj = doc.object();
        qDebug() << "[CLIENT] Получен ответ от сервера:" << obj;

        if (obj["type"] == "get_result" || obj["type"] == "save_result") {
            QString status = obj["status"].toString();
            int score = obj["score"].toInt();
            int testId = obj["test_id"].toInt();

            qDebug() << "[CLIENT] waitingForTestId =" << waitingForTestId
                     << " testId =" << testId
                     << " status =" << status
                     << " score =" << score;

            bool isEmpty = false;

            if (status == "ok") {
                if (testId >= 1 && testId <= 4) {   // 🔹 только 1–4 тесты влияют на max_balls
                    if (testResults[testId] != score) {
                        testResults[testId] = score;
                        updateTotalScore();
                    }
                }
            } else if (status == "empty") {
                if (testId >= 1 && testId <= 4) {
                    if (testResults[testId] != -1) {
                        testResults[testId] = -1;
                        updateTotalScore();
                    }
                }
                isEmpty = true;
            }

            // --- Если ждём этот тест, открываем окно ---
            if (waitingForTestId == testId) {
                waitingForTestId = 0;

                if (testId == 5) {
                    if (status == "ok") {
                        QMessageBox::information(this, "Финальный тест",
                                                 "Вы уже проходили финальный тест.\nВаш результат: "
                                                     + QString::number(score) + " из 15.");
                    } else if (status == "empty") {
                        finish_test *finTest = new finish_test(socket, userId, 5, this);
                        connect(finTest, &finish_test::scoreUpdated, this, [=](int finalScore){
                            QMessageBox::information(this, "Финальный тест",
                                                     "Финальный тест завершён!\n"
                                                     "Ваш результат: " + QString::number(finalScore) + " из 15.");
                        });
                        finTest->exec();
                    }
                }

                if (testId == 1) {
                    zadania1 *zadaniaWindow = new zadania1(socket, userId, this);
                    connect(zadaniaWindow, &zadania1::scoreUpdated, this, [=](int newScore){
                        if (newScore > testResults[1]) {
                            testResults[1] = newScore;
                            updateTotalScore();
                        }
                    });

                    if (isEmpty) {
                        zadaniaWindow->exec();
                    } else if (score == 2) {
                        QMessageBox::information(this, "Тест пройден", "Тест 1 пройден на максимальный балл!");
                        zadaniaWindow->deleteLater();
                    } else {
                        QMessageBox msgBox(this);
                        msgBox.setWindowTitle("Тест пройден");
                        msgBox.setText("Ваш результат: " + QString::number(score) + " балла.\nЖелаете перепройти тест?");
                        QPushButton *yesButton = msgBox.addButton("✅ Да", QMessageBox::YesRole);
                        QPushButton *noButton  = msgBox.addButton("❌ Нет", QMessageBox::NoRole);
                        msgBox.exec();

                        if (msgBox.clickedButton() == yesButton) {
                            zadaniaWindow->exec();
                        } else {
                            zadaniaWindow->deleteLater();
                        }
                    }
                }

                else if (testId == 2) {
                    zadania2 *zadaniaWindow = new zadania2(socket, userId, this);
                    connect(zadaniaWindow, &zadania2::scoreUpdated, this, [=](int newScore){
                        if (newScore > testResults[2]) {
                            testResults[2] = newScore;
                            updateTotalScore();
                        }
                    });

                    if (isEmpty) {
                        zadaniaWindow->exec();
                    } else if (score == 4) {
                        QMessageBox::information(this, "Тест пройден", "Тест 2 пройден на максимальный балл!");
                        zadaniaWindow->deleteLater();
                    } else {
                        QMessageBox msgBox(this);
                        msgBox.setWindowTitle("Тест пройден");
                        msgBox.setText("Ваш результат: " + QString::number(score) + " балла.\nЖелаете перепройти тест?");
                        QPushButton *yesButton = msgBox.addButton("✅ Да", QMessageBox::YesRole);
                        QPushButton *noButton  = msgBox.addButton("❌ Нет", QMessageBox::NoRole);
                        msgBox.exec();

                        if (msgBox.clickedButton() == yesButton) {
                            zadaniaWindow->exec();
                        } else {
                            zadaniaWindow->deleteLater();
                        }
                    }
                }

                else if (testId == 3) {
                    zadania3 *zadaniaWindow = new zadania3(socket, userId, this);
                    connect(zadaniaWindow, &zadania3::scoreUpdated, this, [=](int newScore){
                        if (newScore > testResults[3]) {
                            testResults[3] = newScore;
                            updateTotalScore();
                        }
                    });

                    if (isEmpty) {
                        zadaniaWindow->exec();
                    } else if (score == 6) {
                        QMessageBox::information(this, "Тест пройден", "Тест 3 пройден на максимальный балл!");
                        zadaniaWindow->deleteLater();
                    } else {
                        QMessageBox msgBox(this);
                        msgBox.setWindowTitle("Тест пройден");
                        msgBox.setText("Ваш результат: " + QString::number(score) + " баллов.\nЖелаете перепройти тест?");
                        QPushButton *yesButton = msgBox.addButton("✅ Да", QMessageBox::YesRole);
                        QPushButton *noButton  = msgBox.addButton("❌ Нет", QMessageBox::NoRole);
                        msgBox.exec();

                        if (msgBox.clickedButton() == yesButton) {
                            zadaniaWindow->exec();
                        } else {
                            zadaniaWindow->deleteLater();
                        }
                    }
                }

                else if (testId == 4) {
                    zadania4 *zadaniaWindow = new zadania4(socket, userId, this);
                    connect(zadaniaWindow, &zadania4::scoreUpdated, this, [=](int newScore){
                        if (newScore > testResults[4]) {
                            testResults[4] = newScore;
                            updateTotalScore();
                        }
                    });

                    if (isEmpty) {
                        zadaniaWindow->exec();
                    } else if (score == 5) {
                        QMessageBox::information(this, "Тест пройден", "Тест 4 пройден на максимальный балл!");
                        zadaniaWindow->deleteLater();
                    } else {
                        QMessageBox msgBox(this);
                        msgBox.setWindowTitle("Тест пройден");
                        msgBox.setText("Ваш результат: " + QString::number(score) + " баллов.\nЖелаете перепройти тест?");
                        QPushButton *yesButton = msgBox.addButton("✅ Да", QMessageBox::YesRole);
                        QPushButton *noButton  = msgBox.addButton("❌ Нет", QMessageBox::NoRole);
                        msgBox.exec();

                        if (msgBox.clickedButton() == yesButton) {
                            zadaniaWindow->exec();
                        } else {
                            zadaniaWindow->deleteLater();
                        }
                    }
                }
            }
        }
    }
}

void main_lection::on_easy_question_clicked() {
    QJsonObject req;
    req["type"] = "get_result";
    req["student_id"] = userId;
    req["test_id"] = 1;
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();

    waitingForTestId = 1;
}

void main_lection::on_middle_question_clicked() {
    QJsonObject req;
    req["type"] = "get_result";
    req["student_id"] = userId;
    req["test_id"] = 2;
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();

    waitingForTestId = 2;
}

void main_lection::on_hard_question_clicked() {
    QJsonObject req;
    req["type"] = "get_result";
    req["student_id"] = userId;
    req["test_id"] = 3;
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();

    waitingForTestId = 3;
}

void main_lection::on_code_question_clicked() {
    QJsonObject req;
    req["type"] = "get_result";
    req["student_id"] = userId;
    req["test_id"] = 4;
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();

    waitingForTestId = 4;
}

void main_lection::on_finish_test_clicked() {
    if (totalScore < 10) {
        QMessageBox::warning(this, "Недостаточно баллов",
                             "Чтобы пройти финальный тест, нужно набрать минимум 10 баллов "
                             "за предыдущие тесты.");
        return;
    }

    QJsonObject req;
    req["type"] = "get_result";
    req["student_id"] = userId;
    req["test_id"] = 5;
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();

    waitingForTestId = 5;
}

void main_lection::on_lection1_clicked() {
    test1 *zadaniaWindow = new test1(this);
    zadaniaWindow->exec(); // Открываем test1 как модальное окно
}

void main_lection::on_lection2_clicked() {
    test2 *zadaniaWindow = new test2(this);
    zadaniaWindow->exec(); // Открываем test2 как модальное окно
}

void main_lection::on_lection3_clicked() {
    test3 *zadaniaWindow = new test3(this);
    zadaniaWindow->exec(); // Открываем test3 как модальное окно
}

void main_lection::on_backButton_clicked() { // Реализация слота для кнопки "Назад"
    reject(); // Закрывает диалог с результатом "Rejected"
}

// Новый слот для обработки выхода
void main_lection::on_exitButton_clicked() {
    dialog_window_exit exitDialog(this); // Создаем экземпляр диалогового окна выхода
    if (exitDialog.exec() == QDialog::Accepted) {
        qApp->quit(); // Закрываем приложение, если нажата кнопка "Да"
    }
}

void main_lection::requestTestResults() {
    // Запрашиваем результаты сразу для всех тестов
    for (int testId = 1; testId <= 4; ++testId) {
        QJsonObject req;
        req["type"] = "get_result";
        req["student_id"] = userId;
        req["test_id"] = testId;
        socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    }
    socket->flush();
}

void main_lection::updateTotalScore() {
    totalScore = 0;
    for (auto score : testResults) {
        if (score >= 0) {
            totalScore += score;
        }
    }
    ui->max_balls->setText(QString::number(totalScore));
}
