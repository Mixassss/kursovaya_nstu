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


main_lection::main_lection(QTcpSocket *sharedSocket, QWidget *parent)
    : QDialog(parent), ui(new Ui::main_lection), socket(sharedSocket)
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
}

main_lection::~main_lection() {
    delete ui;
}

void main_lection::on_easy_question_clicked() {
    zadania1 *zadaniaWindow = new zadania1(this);
    zadaniaWindow->exec(); // Открываем zadania1 как модальное окно
}

void main_lection::on_middle_question_clicked() {
    zadania2 *zadaniaWindow = new zadania2(this);
    zadaniaWindow->exec(); // Открываем zadania2 как модальное окно
}

void main_lection::on_hard_question_clicked() {
    zadania3 *zadaniaWindow = new zadania3(this);
    zadaniaWindow->exec(); // Открываем zadania3 как модальное окно
}

void main_lection::on_code_question_clicked() {
    zadania4 *zadaniaWindow = new zadania4(this);
    zadaniaWindow->exec(); // Открываем zadania4 как модальное окно
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
