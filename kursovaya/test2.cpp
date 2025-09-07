#include "test2.h"
#include "ui_test2.h"
#include "all_lection2.h"
#include "lec2_test1.h"
#include "lec2_test2.h"
#include "lec2_test3.h"
#include "lec2_test4.h"

test2::test2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::test2)
{
    ui->setupUi(this);

    connect(ui->pushButton_5, &QPushButton::clicked, this, &test2::on_backButton_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &test2::all_lection2_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &test2::lec2_1_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &test2::lec2_2_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &test2::lec2_3_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &test2::lec2_4_clicked);
}

test2::~test2()
{
    delete ui;
}

void test2::on_backButton_clicked() { // Реализация слота для кнопки "Вернуться на главную"
    reject(); // Закрывает диалог с результатом "Rejected"
}

void test2::all_lection2_clicked() {
    all_lection2 *all_lection2Window = new all_lection2(this);
    all_lection2Window->exec(); // Открываем как модальное окно
}

void test2::lec2_1_clicked() {
    lec2_test1 *lec2_1_test1Window = new lec2_test1(this);
    lec2_1_test1Window->exec(); // Открываем как модальное окно
}

void test2::lec2_2_clicked() {
    lec2_test2 *lec2_2_test1Window = new lec2_test2(this);
    lec2_2_test1Window->exec(); // Открываем как модальное окно
}

void test2::lec2_3_clicked() {
    lec2_test3 *lec2_3_test1Window = new lec2_test3(this);
    lec2_3_test1Window->exec(); // Открываем как модальное окно
}

void test2::lec2_4_clicked() {
    lec2_test4 *lec2_4_test1Window = new lec2_test4(this);
    lec2_4_test1Window->exec(); // Открываем как модальное окно
}
