#include "zadania1.h"
#include "test1.h"
#include "ui_zadania1.h"

zadania1::zadania1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::zadania1) {
    ui->setupUi(this);

    // Изначально кнопки скрыты
    ui->pushButton_5->setVisible(false); // Пройти ещё раз
    ui->pushButton_2->setVisible(false); // Следующий вопрос
    ui->pushButton_3->setVisible(false); // Вернуться к теории

    // Изначально кнопка "Ответить" отключена
    ui->pushButton_4->setEnabled(false);

    // Подключаем слоты для радиокнопок первой группы
    connect(ui->AnswerA, &QRadioButton::toggled, this, &zadania1::updateSubmitButtonState);
    connect(ui->AnswerB, &QRadioButton::toggled, this, &zadania1::updateSubmitButtonState);
    connect(ui->AnswerC, &QRadioButton::toggled, this, &zadania1::updateSubmitButtonState);
    connect(ui->AnswerD, &QRadioButton::toggled, this, &zadania1::updateSubmitButtonState);

    // Подключаем слоты для радиокнопок второй группы
    connect(ui->AnswerA_2, &QRadioButton::toggled, this, &zadania1::updateSubmitButtonState);
    connect(ui->AnswerB_2, &QRadioButton::toggled, this, &zadania1::updateSubmitButtonState);
    connect(ui->AnswerC_2, &QRadioButton::toggled, this, &zadania1::updateSubmitButtonState);
    connect(ui->AnswerD_2, &QRadioButton::toggled, this, &zadania1::updateSubmitButtonState);

    connect(ui->pushButton, &QPushButton::clicked, this, &zadania1::on_backButton_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &zadania1::onBackClicked);
}

zadania1::~zadania1() {
    delete ui;
}

void zadania1::on_pushButton_4_clicked() {
    // Блокируем радиокнопки
    ui->AnswerA->setEnabled(false);
    ui->AnswerB->setEnabled(false);
    ui->AnswerC->setEnabled(false);
    ui->AnswerD->setEnabled(false);
    ui->AnswerA_2->setEnabled(false);
    ui->AnswerB_2->setEnabled(false);
    ui->AnswerC_2->setEnabled(false);
    ui->AnswerD_2->setEnabled(false);

    // Обновляем видимость кнопок в зависимости от выбранных ответов
    updateButtonsVisibility();

    // Деактивируем кнопку "Ответить"
    ui->pushButton_4->setEnabled(false);
}

void zadania1::updateSubmitButtonState() {
    // Проверяем, выбраны ли ответы из обеих групп
    bool firstGroupSelected = ui->AnswerA->isChecked() || ui->AnswerB->isChecked() || ui->AnswerC->isChecked() || ui->AnswerD->isChecked();
    bool secondGroupSelected = ui->AnswerA_2->isChecked() || ui->AnswerB_2->isChecked() || ui->AnswerC_2->isChecked() || ui->AnswerD_2->isChecked();

    // Активируем кнопку "Ответить", если выбрано 2 ответа (по одному из каждой группы)
    ui->pushButton_4->setEnabled(firstGroupSelected && secondGroupSelected);
}

void zadania1::updateButtonsVisibility() {
    // Проверка правильных ответов
    bool firstGroupCorrect = ui->AnswerB->isChecked(); // AnswerB - правильный ответ первой группы
    bool secondGroupCorrect = ui->AnswerC_2->isChecked(); // AnswerC_2 - правильный ответ второй группы

    // Изменяем цвет кнопок в зависимости от выбора
    if (ui->AnswerA->isChecked()) {
        ui->AnswerA->setStyleSheet("background-color: red;"); // Неправильный ответ
    }
    if (ui->AnswerB->isChecked()) {
        ui->AnswerB->setStyleSheet("background-color: green;"); // Правильный ответ
    }
    if (ui->AnswerC->isChecked()) {
        ui->AnswerC->setStyleSheet("background-color: red;"); // Неправильный ответ
    }
    if (ui->AnswerD->isChecked()) {
        ui->AnswerD->setStyleSheet("background-color: red;"); // Неправильный ответ
    }

    if (ui->AnswerA_2->isChecked()) {
        ui->AnswerA_2->setStyleSheet("background-color: red;"); // Неправильный ответ
    }
    if (ui->AnswerB_2->isChecked()) {
        ui->AnswerB_2->setStyleSheet("background-color: red;"); // Неправильный ответ
    }
    if (ui->AnswerC_2->isChecked()) {
        ui->AnswerC_2->setStyleSheet("background-color: green;"); // Правильный ответ
    }
    if (ui->AnswerD_2->isChecked()) {
        ui->AnswerD_2->setStyleSheet("background-color: red;"); // Неправильный ответ
    }

    // Логика для видимости кнопок
    if (firstGroupCorrect && secondGroupCorrect) {
        // Если оба ответа верные
        ui->pushButton_5->setVisible(false); // Показать кнопку "Пройти ещё раз"
        ui->pushButton_2->setVisible(true); // Показать кнопку "Следующий вопрос"
        ui->pushButton_3->setVisible(false); // Скрыть кнопку "Вернуться к теории"
    } else if (firstGroupCorrect || secondGroupCorrect) {
        // Если один ответ верный
        ui->pushButton_5->setVisible(true); // Показать кнопку "Пройти ещё раз"
        ui->pushButton_2->setVisible(true); // Скрыть кнопку "Следующий вопрос"
        ui->pushButton_3->setVisible(false); // Скрыть кнопку "Вернуться к теории"
    } else {
        // Если ни один ответ не верный
        ui->pushButton_5->setVisible(false); // Скрыть кнопку "Пройти ещё раз"
        ui->pushButton_2->setVisible(false); // Скрыть кнопку "Следующий вопрос"
        ui->pushButton_3->setVisible(true); // Показать кнопку "Вернуться к теории"
    }
}

void zadania1::on_backButton_clicked() { // Реализация слота для кнопки "Вернуться на главную"
    reject(); // Закрывает диалог с результатом "Rejected"
}

void zadania1::onBackClicked() {
    // Создаем новое окно test1
    test1 *lectionWindow = new test1();

    // Настраиваем новое окно
    lectionWindow->setModal(true); // Если нужно модальное окно

    // Закрываем текущее окно
    this->close();

    // Показываем новое окно
    lectionWindow->show();
}
