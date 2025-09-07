#include "all_lection2.h"
#include "ui_all_lection2.h"

all_lection2::all_lection2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::all_lection2)
{
    ui->setupUi(this);

    // Подключение кнопки к слоту
    connect(ui->pushButton, &QPushButton::clicked, this, &all_lection2::on_backButton_clicked);
}

all_lection2::~all_lection2() {
    delete ui;
}

void all_lection2::on_backButton_clicked() {
    reject(); // Закрывает диалог с результатом "Rejected"
}
