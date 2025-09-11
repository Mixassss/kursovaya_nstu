#include "test3.h"
#include "ui_test3.h"
#include "all_lection3.h"
#include "lec3_test1.h"
#include "lec3_test2.h"
#include "lec3_test3.h"
#include "lec3_test4.h"

test3::test3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::test3)
{
    ui->setupUi(this);

    connect(ui->pushButton_5, &QPushButton::clicked, this, &test3::on_backButton_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &test3::all_lection3_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &test3::lec3_1_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &test3::lec3_2_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &test3::lec3_3_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &test3::lec3_4_clicked);
}

test3::~test3()
{
    delete ui;
}

void test3::on_backButton_clicked() { // Реализация слота для кнопки "Вернуться на главную"
    reject(); // Закрывает диалог с результатом "Rejected"
}

void test3::all_lection3_clicked() {
    all_lection3 *all_lection3Window = new all_lection3(this);
    all_lection3Window->exec(); // Открываем как модальное окно
}

void test3::lec3_1_clicked() {
    lec3_test1 *lec3_1_test1Window = new lec3_test1(this);
    lec3_1_test1Window->exec(); // Открываем как модальное окно
}

void test3::lec3_2_clicked() {
    lec3_test2 *lec3_2_test1Window = new lec3_test2(this);
    lec3_2_test1Window->exec(); // Открываем как модальное окно
}

void test3::lec3_3_clicked() {
    lec3_test3 *lec3_3_test1Window = new lec3_test3(this);
    lec3_3_test1Window->exec(); // Открываем как модальное окно
}

void test3::lec3_4_clicked() {
    lec3_test4 *lec3_4_test1Window = new lec3_test4(this);
    lec3_4_test1Window->exec(); // Открываем как модальное окно
}
