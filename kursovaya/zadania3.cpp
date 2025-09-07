#include "zadania3.h"
#include "ui_zadania3.h"
#include "test1.h"

zadania3::zadania3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::zadania3)
{
    ui->setupUi(this);
    // Изначально кнопки скрыты
    ui->pushButton_2->setVisible(false); // Пройти ещё раз
    ui->pushButton_5->setVisible(false); // Следующий вопрос
    ui->pushButton_3->setVisible(false); // Вернуться к теории

    // Изначально кнопка "Ответить" отключена
    ui->pushButton_6->setEnabled(false);

    // Подключаем слоты для радиокнопок первой группы
    connect(ui->AnswerA, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);
    connect(ui->AnswerB, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);
    connect(ui->AnswerC, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);
    connect(ui->AnswerD, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);

    // Подключаем слоты для радиокнопок второй группы
    connect(ui->AnswerA_2, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);
    connect(ui->AnswerB_2, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);
    connect(ui->AnswerC_2, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);
    connect(ui->AnswerD_2, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);

    // Подключаем слоты для радиокнопок третьей группы
    connect(ui->AnswerA_3, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);
    connect(ui->AnswerB_3, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);
    connect(ui->AnswerC_3, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);
    connect(ui->AnswerD_3, &QRadioButton::toggled, this, &zadania3::updateSubmitButtonState);

    connect(ui->pushButton, &QPushButton::clicked, this, &zadania3::on_backButton_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &zadania3::onBackClicked);
}

void zadania3::on_pushButton_6_clicked() {
    // Блокируем радиокнопки
    ui->AnswerA->setEnabled(false);
    ui->AnswerB->setEnabled(false);
    ui->AnswerC->setEnabled(false);
    ui->AnswerD->setEnabled(false);
    ui->AnswerA_2->setEnabled(false);
    ui->AnswerB_2->setEnabled(false);
    ui->AnswerC_2->setEnabled(false);
    ui->AnswerD_2->setEnabled(false);
    ui->AnswerA_3->setEnabled(false);
    ui->AnswerB_3->setEnabled(false);
    ui->AnswerC_3->setEnabled(false);
    ui->AnswerD_3->setEnabled(false);

    // Обновляем видимость кнопок в зависимости от выбранных ответов
    updateButtonsVisibility();

    // Деактивируем кнопку "Ответить"
    ui->pushButton_6->setEnabled(false);
}

void zadania3::updateSubmitButtonState() {
    // Проверяем, выбраны ли ответы из всех групп
    bool firstGroupSelected = ui->AnswerA->isChecked() || ui->AnswerB->isChecked() || ui->AnswerC->isChecked() || ui->AnswerD->isChecked();
    bool secondGroupSelected = ui->AnswerA_2->isChecked() || ui->AnswerB_2->isChecked() || ui->AnswerC_2->isChecked() || ui->AnswerD_2->isChecked();
    bool thirdGroupSelected = ui->AnswerA_3->isChecked() || ui->AnswerB_3->isChecked() || ui->AnswerC_3->isChecked() || ui->AnswerD_3->isChecked();

    // Активируем кнопку "Ответить", если выбраны ответы из всех групп
    ui->pushButton_6->setEnabled(firstGroupSelected && secondGroupSelected && thirdGroupSelected);
}

zadania3::~zadania3()
{
    delete ui;
}

void zadania3::updateButtonsVisibility() {
    // Проверка правильных ответов
    bool firstGroupCorrect = ui->AnswerB->isChecked(); // AnswerB - правильный ответ первой группы
    bool secondGroupCorrect = ui->AnswerC_2->isChecked(); // AnswerC_2 - правильный ответ второй группы
    bool thirdGroupCorrect = ui->AnswerD_3->isChecked(); // AnswerD_3 - правильный ответ второй группы

    // Изменяем цвет кнопок в зависимости от выбораS
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

    if (ui->AnswerA_3->isChecked()) {
        ui->AnswerA_3->setStyleSheet("background-color: red;"); // Неправильный ответ
    }
    if (ui->AnswerB_3->isChecked()) {
        ui->AnswerB_3->setStyleSheet("background-color: red;"); // Неправильный ответ
    }
    if (ui->AnswerC_3->isChecked()) {
        ui->AnswerC_3->setStyleSheet("background-color: red;"); // Неправильный ответ
    }
    if (ui->AnswerD_3->isChecked()) {
        ui->AnswerD_3->setStyleSheet("background-color: green;"); // Правильный ответ
    }

    // Логика для видимости кнопок
    int correctAnswersCount = 0;
    if (firstGroupCorrect) correctAnswersCount++;
    if (secondGroupCorrect) correctAnswersCount++;
    if (thirdGroupCorrect) correctAnswersCount++;

    // Обновляем видимость кнопок в зависимости от количества правильных ответов
    if (correctAnswersCount == 3) {
        ui->pushButton_2->setVisible(false); // Скрыть кнопку "Пройти ещё раз"
        ui->pushButton_5->setVisible(true); // Показать кнопку "Следующий вопрос"
        ui->pushButton_3->setVisible(false); // Скрыть кнопку "Вернуться к теории"
    } else if (correctAnswersCount == 2) {
        ui->pushButton_2->setVisible(true); // Показать кнопку "Пройти ещё раз"
        ui->pushButton_5->setVisible(true); // Скрыть кнопку "Следующий вопрос"
        ui->pushButton_3->setVisible(false); // Скрыть кнопку "Вернуться к теории"
    } else if (correctAnswersCount == 1) {
        ui->pushButton_2->setVisible(false); // Показать кнопку "Пройти ещё раз"
        ui->pushButton_5->setVisible(false); // Скрыть кнопку "Следующий вопрос"
        ui->pushButton_3->setVisible(true); // Показать кнопку "Вернуться к теории"
    } else {
        // Если ни один ответ не верный
        ui->pushButton_2->setVisible(false); // Скрыть кнопку "Пройти ещё раз"
        ui->pushButton_5->setVisible(false); // Скрыть кнопку "Следующий вопрос"
        ui->pushButton_3->setVisible(true); // Показать кнопку "Вернуться к теории"
    }
}

void zadania3::on_backButton_clicked() { // Реализация слота для кнопки "Вернуться на главную"
    reject(); // Закрывает диалог с результатом "Rejected"
}

void zadania3::onBackClicked() {
    // Создаем новое окно test1
    test1 *lectionWindow = new test1();

    // Настраиваем новое окно
    lectionWindow->setModal(true); // Если нужно модальное окно

    // Закрываем текущее окно
    this->close();

    // Показываем новое окно
    lectionWindow->show();
}
