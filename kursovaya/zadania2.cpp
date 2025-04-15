#include "zadania2.h"
#include "ui_zadania2.h"

zadania2::zadania2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::zadania2)
{
    ui->setupUi(this);
}

zadania2::~zadania2()
{
    delete ui;
}
