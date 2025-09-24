#include "zadania4.h"
#include "ui_zadania4.h"
#include <QComboBox>
#include <QRadioButton>
#include "test1.h"
#include <QJsonArray>

zadania4::zadania4(QTcpSocket *sharedSocket, int currentUserId, QWidget *parent)
    : QDialog(parent), ui(new Ui::zadania4), socket(sharedSocket), userId(currentUserId)
{
    ui->setupUi(this);

    ui->pushButton_3->setVisible(false); // Вернуться к теории
    ui->pushButton_4->setVisible(false); // Пройти ещё раз

    // Изначально кнопка "Ответить" отключена
    ui->pushButton_6->setEnabled(false);

    // Подключаем сигналы изменения ComboBox
    connect(ui->change2, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &zadania4::updateSubmitButtonState);
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &zadania4::updateSubmitButtonState);

    // Подключаем сигналы RadioButton
    connect(ui->radioButton, &QRadioButton::toggled, this, &zadania4::updateSubmitButtonState);
    connect(ui->radioButton_2, &QRadioButton::toggled, this, &zadania4::updateSubmitButtonState);
    connect(ui->radioButton_3, &QRadioButton::toggled, this, &zadania4::updateSubmitButtonState);
    connect(ui->radioButton_4, &QRadioButton::toggled, this, &zadania4::updateSubmitButtonState);

    connect(ui->pushButton_3, &QPushButton::clicked, this, &zadania4::onBackClicked);

    QJsonObject req;
    req["type"] = "get_result";
    req["student_id"] = userId;
    req["test_id"] = 4;
    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}

void zadania4::lockAnswers() {
    ui->change2->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->radioButton->setEnabled(false);
    ui->radioButton_2->setEnabled(false);
    ui->radioButton_3->setEnabled(false);
    ui->radioButton_4->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
}

void zadania4::resetAnswers() {
    // Сбрасываем выбор к заглушке (например, индекс 0)
    ui->change2->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);

    // Снова включаем возможность выбора
    ui->change2->setEnabled(true);
    ui->comboBox_2->setEnabled(true);

    QList<QRadioButton*> radios = { ui->radioButton, ui->radioButton_2, ui->radioButton_3, ui->radioButton_4 };
    for (auto r : radios) {
        r->setAutoExclusive(false);
        r->setChecked(false);
        r->setStyleSheet("");
        r->setAutoExclusive(true);
        r->setEnabled(true);   // <-- тоже включаем
    }

    ui->change2->setStyleSheet("");
    ui->comboBox_2->setStyleSheet("");
    ui->pushButton_6->setEnabled(false);
}

void zadania4::sendSaveResult(int score) {
    QString answer1 = ui->change2->currentText();
    QString answer2 = ui->comboBox_2->currentText();
    QString answer3;
    if (ui->radioButton->isChecked()) answer3 = "A";
    if (ui->radioButton_2->isChecked()) answer3 = "B";
    if (ui->radioButton_3->isChecked()) answer3 = "C";
    if (ui->radioButton_4->isChecked()) answer3 = "D";

    QJsonArray answers;
    answers.append(answer1);
    answers.append(answer2);
    answers.append(answer3);

    QJsonObject req;
    req["type"] = "save_result";
    req["student_id"] = userId;
    req["test_id"] = 4;
    req["score"] = score;
    req["answers"] = answers;

    socket->write(QJsonDocument(req).toJson(QJsonDocument::Compact) + "\n");
    socket->flush();
}

void zadania4::restoreAnswersAndHighlight(const QString &a1, const QString &a2, const QString &a3) {
    int idx1 = ui->change2->findText(a1);
    if (idx1 != -1) ui->change2->setCurrentIndex(idx1);

    int idx2 = ui->comboBox_2->findText(a2);
    if (idx2 != -1) ui->comboBox_2->setCurrentIndex(idx2);

    if (a3 == "A") ui->radioButton->setChecked(true);
    else if (a3 == "B") ui->radioButton_2->setChecked(true);
    else if (a3 == "C") ui->radioButton_3->setChecked(true);
    else if (a3 == "D") ui->radioButton_4->setChecked(true);

    lockAnswers();
    updateButtonsVisibility();
}

void zadania4::on_pushButton_6_clicked() {
    bool firstCorrect = ui->change2->currentText() == "*top = pv";
    bool secondCorrect = ui->comboBox_2->currentText() == "*p != 0";
    bool thirdCorrect = ui->radioButton_3->isChecked();

    int score = 0;
    if (firstCorrect) score += 2;
    if (secondCorrect) score += 2;
    if (thirdCorrect) score++;
    if (score > 5) score = 5;

    lockAnswers();
    updateButtonsVisibility();

    if (!alreadyPassed) {
        sendSaveResult(score);
        alreadyPassed = true;
        emit scoreUpdated(score);
    }

    // 🔹 Проверка на максимальный результат
    if (score == 5) {
        QMessageBox::information(this, "Поздравляем",
                                 "Поздравляем! Тест 4 пройден на 5 из 5.");
        this->close();
    }
}


void zadania4::updateSubmitButtonState() {
    // Проверяем, выбраны ли ответы из всех групп
    bool firstComboSelected = ui->change2->currentIndex() != -1;
    bool secondComboSelected = ui->comboBox_2->currentIndex() != -1;
    bool radioGroupSelected = ui->radioButton->isChecked() || ui->radioButton_2->isChecked() ||
                              ui->radioButton_3->isChecked() || ui->radioButton_4->isChecked();

    // Активируем кнопку "Ответить", если выбраны ответы из всех групп
    ui->pushButton_6->setEnabled(firstComboSelected && secondComboSelected && radioGroupSelected);
}

void zadania4::updateButtonsVisibility() {
    // Проверка правильных ответов
    bool firstComboCorrect = ui->change2->currentText() == "*top = pv";
    bool secondComboCorrect = ui->comboBox_2->currentText() == "*p != 0";
    bool radioCorrect = ui->radioButton_3->isChecked();

    // Изменяем цвет ComboBox в зависимости от выбора
    QString correctStyle = "QComboBox { background-color: green; color: white; }";
    QString incorrectStyle = "QComboBox { background-color: red; color: white; }";
    QString defaultStyle = "QComboBox { background-color: white; color: black; }";

    // Первый ComboBox
    if (firstComboCorrect) {
        ui->change2->setStyleSheet(correctStyle);
    } else {
        ui->change2->setStyleSheet(incorrectStyle);
    }

    // Второй ComboBox
    if (secondComboCorrect) {
        ui->comboBox_2->setStyleSheet(correctStyle);
    } else {
        ui->comboBox_2->setStyleSheet(incorrectStyle);
    }

    // Radio buttons
    if (ui->radioButton->isChecked()) {
        ui->radioButton->setStyleSheet("color: red; font-weight: bold;");
    }
    if (ui->radioButton_2->isChecked()) {
        ui->radioButton_2->setStyleSheet("color: red; font-weight: bold;");
    }
    if (ui->radioButton_3->isChecked()) {
        ui->radioButton_3->setStyleSheet("color: green; font-weight: bold;");
    }
    if (ui->radioButton_4->isChecked()) {
        ui->radioButton_4->setStyleSheet("color: red; font-weight: bold;");
    }

    // Подсчет правильных ответов
    int correctAnswersCount = 0;
    if (firstComboCorrect) correctAnswersCount++;
    if (secondComboCorrect) correctAnswersCount++;
    if (radioCorrect) correctAnswersCount++;

    if (correctAnswersCount == 3) {
        ui->pushButton_4->setVisible(false); // Скрыть кнопку "Пройти ещё раз"
        ui->pushButton_3->setVisible(false); // Скрыть кнопку "Вернуться к теории"
    } else if (correctAnswersCount == 2) {
        ui->pushButton_4->setVisible(true); // Показать кнопку "Пройти ещё раз"
        ui->pushButton_3->setVisible(true); // Скрыть кнопку "Вернуться к теории"
    } else if (correctAnswersCount == 1) {
        ui->pushButton_4->setVisible(true); // Показать кнопку "Пройти ещё раз"
        ui->pushButton_3->setVisible(true); // Показать кнопку "Вернуться к теории"
    } else {
        // Если ни один ответ не верный
        ui->pushButton_4->setVisible(true); // Скрыть кнопку "Пройти ещё раз"
        ui->pushButton_3->setVisible(true); // Показать кнопку "Вернуться к теории"
    }
}

void zadania4::onServerResponse() {
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

zadania4::~zadania4()
{
    delete ui;
}

void zadania4::on_pushButton_4_clicked() {
    alreadyPassed = false;
    resetAnswers();

    ui->pushButton_4->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_6->setVisible(true);
}

void zadania4::onBackClicked() {
    // Создаем новое окно test1
    test1 *lectionWindow = new test1();

    // Настраиваем новое окно
    lectionWindow->setModal(true); // Если нужно модальное окно

    // Закрываем текущее окно
    this->close();

    // Показываем новое окно
    lectionWindow->show();
}
