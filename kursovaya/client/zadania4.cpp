#include "zadania4.h"
#include "ui_zadania4.h"
#include <QComboBox>
#include <QRadioButton>
#include "test1.h"

zadania4::zadania4(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::zadania4)
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

    connect(ui->pushButton, &QPushButton::clicked, this, &zadania4::on_backButton_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &zadania4::onBackClicked);
}

void zadania4::on_pushButton_6_clicked() {
    // Блокируем элементы выбора
    ui->change2->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->radioButton->setEnabled(false);
    ui->radioButton_2->setEnabled(false);
    ui->radioButton_3->setEnabled(false);
    ui->radioButton_4->setEnabled(false);

    // Обновляем видимость кнопок и цвет элементов
    updateButtonsVisibility();

    // Деактивируем кнопку "Ответить"
    ui->pushButton_6->setEnabled(false);
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
    bool firstComboCorrect = ui->change2->currentIndex() == 1; // *top = pv - правильный ответ
    bool secondComboCorrect = ui->comboBox_2->currentIndex() == 2; // *p != 0 - правильный ответ
    bool radioCorrect = ui->radioButton_3->isChecked(); // Ответ C - правильный

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
        ui->pushButton_3->setVisible(false); // Скрыть кнопку "Вернуться к теории"
    } else if (correctAnswersCount == 1) {
        ui->pushButton_4->setVisible(false); // Показать кнопку "Пройти ещё раз"
        ui->pushButton_3->setVisible(true); // Показать кнопку "Вернуться к теории"
    } else {
        // Если ни один ответ не верный
        ui->pushButton_4->setVisible(false); // Скрыть кнопку "Пройти ещё раз"
        ui->pushButton_3->setVisible(true); // Показать кнопку "Вернуться к теории"
    }
}

void zadania4::on_backButton_clicked() {
    reject();
}

zadania4::~zadania4()
{
    delete ui;
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
