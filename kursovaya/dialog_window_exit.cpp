#include "dialog_window_exit.h"
#include "ui_dialog_window_exit.h"

dialog_window_exit::dialog_window_exit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dialog_window_exit)
{
    ui->setupUi(this);
    // Устанавливаем фиксированный размер окна
    setFixedSize(370, 100);

    // Подключаем сигналы кнопок "Да" и "Нет" к соответствующим слотам
    connect(ui->Yes, &QPushButton::clicked, this, &dialog_window_exit::accept); // Нажатие "Да" закрывает диалог с принятием
    connect(ui->No, &QPushButton::clicked, this, &dialog_window_exit::reject); // Нажатие "Нет" закрывает диалог без принятия
}

dialog_window_exit::~dialog_window_exit() {
    delete ui;
}
