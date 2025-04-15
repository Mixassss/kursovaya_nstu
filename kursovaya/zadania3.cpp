#include "zadania3.h"
#include "ui_zadania3.h"

zadania3::zadania3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::zadania3)
{
    ui->setupUi(this);
}

zadania3::~zadania3()
{
    delete ui;
}
