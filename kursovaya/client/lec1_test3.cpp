#include "lec1_test3.h"
#include "lec1_test4.h"
#include "ui_lec1_test3.h"
#include <QRandomGenerator>
#include <QRadioButton>
#include <QMessageBox>

lec1_test3::lec1_test3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::lec1_test3)
    , currentPair1(-1)
    , currentPair2(-1)
{
    ui->setupUi(this);

    QString groupBoxStyle =
        "QGroupBox {"
        "   border: 1px solid #BDBDBD;"
        "   border-radius: 6px;"
        "   margin-top: 10px;"
        "   padding-top: 15px;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   left: 10px;"
        "   padding: 0 5px;"
        "   color: #616161;"
        "}";

    ui->group_first->setStyleSheet(groupBoxStyle);
    ui->group_second->setStyleSheet(groupBoxStyle);

    ui->retry->setStyleSheet(
        "QCheckBox {"
        "   font-size: 14px;"
        "   color: #616161;"
        "}"
        "QCheckBox::indicator {"
        "   width: 16px;"
        "   height: 16px;"
        "}"
        );

    // Настройка стилей
    ui->pushButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   border: none;"
        "   padding: 5px 10px;"
        "   border-radius: 4px;"
        "}"
        "QPushButton:disabled {"
        "   background-color: #CCCCCC;"
        "   color: gray;"
        "}"
        );

    ui->pushButton_2->setStyleSheet(
        "QPushButton {"
        "   background-color: #2196F3;"
        "   color: white;"
        "   border: none;"
        "   padding: 5px 10px;"
        "   border-radius: 4px;"
        "}"
        );

    ui->scrollArea->setStyleSheet(
        "QScrollArea {"
        "   border: none;"
        "}"
        "QScrollBar:vertical {"
        "   width: 10px;"
        "   background: #f1f1f1;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #888;"
        "   min-height: 20px;"
        "}"
        );

    ui->retry->setText("Пройти ещё раз");
    ui->retry->hide();

    // Инициализация пар вопросов
    initQuestionPairs();

    // Изначально скрываем всё
    resetTest();

    // Подключаем сигналы
    connect(ui->agree, &QCheckBox::stateChanged, this, &lec1_test3::onAgreeClicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &lec1_test3::onAnswerClicked);
    connect(ui->retry, &QCheckBox::stateChanged, this, &lec1_test3::onRetryClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &lec1_test3::onNextLectureClicked);
}

void lec1_test3::onRetryClicked(int state) {
    if (state == Qt::Checked) {
        resetTest();
    }
}

void lec1_test3::resetTest() {
    // Сбрасываем все элементы интерфейса в начальное состояние
    ui->scrollArea->show();
    ui->agree->show();
    ui->agree->setEnabled(true);
    ui->agree->setChecked(false);

    ui->group_first->hide();
    ui->group_second->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->retry->hide();
    ui->retry->setChecked(false);

    // Сбрасываем стили и состояния элементов
    resetRadioButtons(ui->group_first);
    resetRadioButtons(ui->group_second);

    // Скрываем все кнопки пояснения
    for (const auto& pair : group1Pairs) {
        pair.explanation->hide();
        pair.explanation->setEnabled(false);
    }
    for (const auto& pair : group2Pairs) {
        pair.explanation->hide();
        pair.explanation->setEnabled(false);
    }

    // Скрываем все элементы в группах
    hideAllGroupElements(ui->group_first);
    hideAllGroupElements(ui->group_second);
}

void lec1_test3::resetRadioButtons(QGroupBox* group) {
    foreach(QObject* child, group->children()) {
        if (auto radio = qobject_cast<QRadioButton*>(child)) {
            radio->setStyleSheet(""); // Сбрасываем стиль
            radio->setAutoExclusive(false);
            radio->setChecked(false);
            radio->setEnabled(true);
            radio->setAutoExclusive(true);
        }
    }
}

void lec1_test3::initQuestionPairs() {
    // Группа 1 пары (вопрос-ответ-пояснение-правильный ответ)
    group1Pairs = {
        {ui->first_q, ui->first_ans, ui->first_poyas, ui->Answer_B},
        {ui->third_q, ui->third_ans, ui->third_poyas, ui->Answer_D},
        {ui->fifth_q, ui->fifth_ans, ui->five_poyas, ui->Answer_A},
        {ui->seven_q, ui->seven_ans, ui->seven_poyas, ui->Answer_B},
        {ui->ninth_q, ui->ninth_ans, ui->ninth_poyas, ui->Answer_B}
    };

    // Группа 2 пары
    group2Pairs = {
        {ui->second_q, ui->second_ans, ui->sec_poyas, ui->Answer_A_2},
        {ui->fourth_q, ui->fourth_ans, ui->fourth_poyas, ui->Answer_C_2},
        {ui->six_q, ui->six_ans, ui->six_poyas, ui->Answer_C_2},
        {ui->eighth_q, ui->eighth_ans, ui->eight_poyas, ui->Answer_A_2}
    };
}

void lec1_test3::hideAllGroupElements(QGroupBox* group) {
    foreach(QObject* child, group->children()) {
        if (auto widget = qobject_cast<QWidget*>(child)) {
            if (!qobject_cast<QRadioButton*>(widget) && widget != group) {
                widget->hide();
            }
        }
    }
}

void lec1_test3::onAgreeClicked(int state) {
    if (state == Qt::Checked) {
        startNewTest();
    }
}

void lec1_test3::startNewTest() {
    ui->scrollArea->hide();
    ui->agree->setEnabled(false);

    // Показываем группы вопросов
    ui->group_first->show();
    ui->group_second->show();

    // Выбираем случайные вопросы
    showRandomQuestionPair(ui->group_first, group1Pairs);
    showRandomQuestionPair(ui->group_second, group2Pairs);

    // Показываем кнопку "Ответить"
    ui->pushButton->show();
    ui->pushButton->setEnabled(false);
}

void lec1_test3::showRandomQuestionPair(QGroupBox* group, const QVector<QuestionPair>& pairs) {
    if (pairs.empty()) return;

    // Выбираем случайный вопрос
    int randomIndex = QRandomGenerator::global()->bounded(pairs.size());

    if (group == ui->group_first) {
        currentPair1 = randomIndex;
    } else {
        currentPair2 = randomIndex;
    }

    // Скрываем все элементы в группе
    hideAllGroupElements(group);

    // Показываем выбранные элементы
    pairs[randomIndex].question->show();
    pairs[randomIndex].answer->show();

    // Разблокируем RadioButton
    foreach(QObject* child, pairs[randomIndex].answer->children()) {
        if (auto radio = qobject_cast<QRadioButton*>(child)) {
            radio->show();
            radio->setEnabled(true);
            radio->setStyleSheet("");
            radio->setAutoExclusive(false);
            radio->setChecked(false);
            radio->setAutoExclusive(true);
        }
    }

    // Скрываем кнопку пояснения
    pairs[randomIndex].explanation->hide();
    pairs[randomIndex].explanation->setEnabled(false);

    connectRadioButtons(group);
}

void lec1_test3::connectRadioButtons(QGroupBox* group) {
    foreach(QObject* child, group->children()) {
        if (auto radio = qobject_cast<QRadioButton*>(child)) {
            connect(radio, &QRadioButton::toggled, this, &lec1_test3::checkAnswers, Qt::UniqueConnection);
        }
    }
}

void lec1_test3::checkAnswers() {
    bool group1Answered = isGroupAnswered(ui->group_first);
    bool group2Answered = isGroupAnswered(ui->group_second);

    ui->pushButton->setEnabled(group1Answered && group2Answered);
}

bool lec1_test3::isGroupAnswered(QGroupBox* group) {
    foreach(QObject* child, group->children()) {
        if (auto radio = qobject_cast<QRadioButton*>(child)) {
            if (radio->isChecked()) {
                return true;
            }
        }
    }
    return false;
}

void lec1_test3::onAnswerClicked() {
    // Проверяем ответы
    bool group1Correct = checkGroupAnswer(ui->group_first, group1Pairs, currentPair1);
    bool group2Correct = checkGroupAnswer(ui->group_second, group2Pairs, currentPair2);

    // Блокируем кнопку "Ответить"
    ui->pushButton->setEnabled(false);

    // Блокируем RadioButton
    setRadioButtonsEnabled(ui->group_first, false);
    setRadioButtonsEnabled(ui->group_second, false);

    // Показываем пояснения для неправильных ответов
    if (!group1Correct && currentPair1 >= 0 && currentPair1 < group1Pairs.size()) {
        group1Pairs[currentPair1].explanation->show();
        group1Pairs[currentPair1].explanation->setEnabled(true);
    }

    if (!group2Correct && currentPair2 >= 0 && currentPair2 < group2Pairs.size()) {
        group2Pairs[currentPair2].explanation->show();
        group2Pairs[currentPair2].explanation->setEnabled(true);
    }

    // Показываем кнопку "Следующая лекция" в любом случае
    ui->pushButton_2->show();

    // Показываем кнопку "Пройти ещё раз"
    ui->agree->hide();
    ui->retry->show();
    ui->retry->setEnabled(true);
}

bool lec1_test3::checkGroupAnswer(QGroupBox* group, const QVector<QuestionPair>& pairs, int pairIndex) {
    if (pairIndex < 0 || pairIndex >= pairs.size()) return false;

    QRadioButton* correctAnswer = pairs[pairIndex].correctAnswer;
    bool allCorrect = true;

    // Проверяем ответы и подсвечиваем их
    foreach(QObject* child, group->children()) {
        if (auto radio = qobject_cast<QRadioButton*>(child)) {
            if (radio->isChecked()) {
                if (radio == correctAnswer) {
                    radio->setStyleSheet("background-color: #A5D6A7;"); // Зеленый
                } else {
                    radio->setStyleSheet("background-color: #EF9A9A;"); // Красный
                    allCorrect = false;
                }
            }
        }
    }

    return allCorrect;
}

void lec1_test3::setRadioButtonsEnabled(QGroupBox* group, bool enabled) {
    foreach(QObject* child, group->children()) {
        if (auto radio = qobject_cast<QRadioButton*>(child)) {
            radio->setEnabled(enabled);
        }
    }
}

void lec1_test3::onNextLectureClicked() {
    // Создаем новое окно lec1_test2
    lec1_test4 *test4Window = new lec1_test4();

    // Настраиваем новое окно
    test4Window->setModal(true); // Если нужно модальное окно

    // Закрываем текущее окно
    this->close();

    // Показываем новое окно
    test4Window->show();
}

lec1_test3::~lec1_test3() {
    delete ui;
}
