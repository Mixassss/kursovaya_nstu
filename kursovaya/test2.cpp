#include "test2.h"
#include "ui_test2.h"

test2::test2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::test2)
{
    ui->setupUi(this);
}

test2::~test2()
{
    delete ui;
}
