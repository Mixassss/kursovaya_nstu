#include "all_lection.h"
#include "ui_all_lection.h"

all_lection::all_lection(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::all_lection)
{
    ui->setupUi(this);

    // Установка минимального размера окна
    setMinimumSize(969, 491);

    // Подключение кнопки к слоту
    connect(ui->pushButton, &QPushButton::clicked, this, &all_lection::on_backButton_clicked);

    // Установка полноэкранного режима
    connect(this, &QDialog::accepted, this, &all_lection::toggleFullScreen);
}

all_lection::~all_lection()
{
    delete ui;
}

void all_lection::on_backButton_clicked() {
    reject(); // Закрывает диалог с результатом "Rejected"
}

void all_lection::toggleFullScreen() {
    if (isFullScreen()) {
        showNormal(); // Возврат к нормальному режиму
    } else {
        showFullScreen(); // Переход в полноэкранный режим
    }
}
