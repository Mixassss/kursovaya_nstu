#include "test3.h"
#include "ui_test3.h"

test3::test3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::test3)
{
    ui->setupUi(this);
}

test3::~test3()
{
    delete ui;
}
