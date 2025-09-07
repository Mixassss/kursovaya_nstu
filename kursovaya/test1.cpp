#include "test1.h"
#include "ui_test1.h"
#include "all_lection.h"
#include "lec1_test1.h"
#include "lec1_test2.h"
#include "lec1_test3.h"
#include "lec1_test4.h"

test1::test1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::test1)
{
    ui->setupUi(this);

    connect(ui->pushButton_5, &QPushButton::clicked, this, &test1::on_backButton_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &test1::all_lection_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &test1::lec1_1_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &test1::lec1_2_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &test1::lec1_3_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &test1::lec1_4_clicked);
}

test1::~test1()
{
    delete ui;
}

void test1::on_backButton_clicked() { // Реализация слота для кнопки "Вернуться на главную"
    reject(); // Закрывает диалог с результатом "Rejected"
}

void test1::all_lection_clicked() {
    all_lection *all_lectionWindow = new all_lection(this);
    all_lectionWindow->exec(); // Открываем test1 как модальное окно
}

void test1::lec1_1_clicked() {
    lec1_test1 *lec1_1_test1Window = new lec1_test1(this);
    lec1_1_test1Window->exec(); // Открываем test1 как модальное окно
}

void test1::lec1_2_clicked() {
    lec1_test2 *lec1_2_test1Window = new lec1_test2(this);
    lec1_2_test1Window->exec(); // Открываем test1 как модальное окно
}

void test1::lec1_3_clicked() {
    lec1_test3 *lec1_3_test1Window = new lec1_test3(this);
    lec1_3_test1Window->exec(); // Открываем test1 как модальное окно
}

void test1::lec1_4_clicked() {
    lec1_test4 *lec1_4_test1Window = new lec1_test4(this);
    lec1_4_test1Window->exec(); // Открываем test1 как модальное окно
}
