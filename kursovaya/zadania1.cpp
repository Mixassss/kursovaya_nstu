#include "zadania1.h"
#include "ui_zadania1.h"

zadania1::zadania1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::zadania1)
{
    ui->setupUi(this);
}

zadania1::~zadania1() {
    delete ui;
}
