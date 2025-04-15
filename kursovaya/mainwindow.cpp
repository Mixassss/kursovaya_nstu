#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "autorization.h"
#include "main_lection.h"
#include "dialog_window_exit.h" // Добавьте этот заголовочный файл
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Устанавливаем минимальный размер окна
    setMinimumSize(750, 580);

    // Создаем центральный виджет и устанавливаем его
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Создаем вертикальный макет
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignCenter); // Центрируем все элементы

    // Создаем фрейм для заголовка
    QFrame *headerFrame = new QFrame(this);
    QVBoxLayout *headerLayout = new QVBoxLayout(headerFrame);

    // Добавляем заголовок "Обучающая система"
    headerLayout->addWidget(ui->label, 0, Qt::AlignCenter);
    headerLayout->addSpacing(100);
    headerLayout->addWidget(ui->label_2, 0, Qt::AlignCenter);
    mainLayout->addWidget(headerFrame);

    // Создаем фрейм для кнопок
    QFrame *buttonFrame = new QFrame(this);
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonFrame);

    // Настраиваем кнопки
    ui->pushButton->setFixedSize(100, 40);
    ui->pushButton_2->setFixedSize(100, 40);

    // Добавляем кнопки в вертикальный макет
    buttonLayout->addWidget(ui->pushButton);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(ui->pushButton_2);
    buttonLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(buttonFrame);

    // Устанавливаем стиль и выравнивание
    centralWidget->setStyleSheet("background-color: rgb(36, 31, 49);");
    headerFrame->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    buttonFrame->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    // Подключаем сигнал clicked() кнопки "Войти" к слоту
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);

    // Подключаем сигнал clicked() кнопки "Выход" к слоту
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_exitButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_loginButton_clicked() {
    Dialog authDialog(this); // Создаем экземпляр диалогового окна авторизации
    if (authDialog.exec() == QDialog::Accepted) { // Используем exec() для модального окна
        main_lection lectionWindow(this); // Создаем экземпляр главного окна лекции
        lectionWindow.exec(); // Открываем main_lection как модальное окно
    }
}

// Новый слот для обработки выхода
void MainWindow::on_exitButton_clicked() {
    dialog_window_exit exitDialog(this); // Создаем экземпляр диалогового окна выхода
    if (exitDialog.exec() == QDialog::Accepted) {
        qApp->quit(); // Закрываем приложение, если нажата кнопка "Да"
    }
}
