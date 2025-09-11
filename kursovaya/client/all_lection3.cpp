#include "all_lection3.h"
#include "ui_all_lection3.h"

all_lection3::all_lection3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::all_lection3)
{
    ui->setupUi(this);
    // Подключение кнопки к слоту
    connect(ui->pushButton, &QPushButton::clicked, this, &all_lection3::on_backButton_clicked);
}

all_lection3::~all_lection3() {
    delete ui;
}

void all_lection3::on_backButton_clicked() {
    reject(); // Закрывает диалог с результатом "Rejected"
}
