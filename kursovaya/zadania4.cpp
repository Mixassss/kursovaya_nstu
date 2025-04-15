#include "zadania4.h"
#include "ui_zadania4.h"

zadania4::zadania4(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::zadania4)
{
    ui->setupUi(this);
}

zadania4::~zadania4()
{
    delete ui;
}
