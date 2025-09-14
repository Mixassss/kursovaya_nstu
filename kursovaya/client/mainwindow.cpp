#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "autorization.h"
#include "main_lection.h"
#include "window_admin.h"
#include "dialog_window_exit.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , socket(new QTcpSocket(this))   // создаем сокет
{
    ui->setupUi(this);

    socket->connectToHost("127.0.0.1", 9850);

    connect(socket, &QTcpSocket::connected, this, [](){
        qDebug() << "Connected to server";
    });
    connect(socket, &QTcpSocket::errorOccurred, this, [](QAbstractSocket::SocketError err){
        qWarning() << "Socket error" << err;
    });

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
    Dialog authDialog(this);
    if (authDialog.exec() == QDialog::Accepted) {

        int uid = authDialog.getUserId();
        qDebug() << "Авторизованный пользователь ID:" << uid;

        if (uid == 0) {
            QMessageBox::critical(this, "Ошибка", "Не удалось получить ID пользователя!");
            return;
        }

        QString position = authDialog.getUserPosition();

        if (position == "admin") {
            window_admin *adminWindow = new window_admin(socket, nullptr); // nullptr как родитель
            adminWindow->setAttribute(Qt::WA_DeleteOnClose);
            adminWindow->show(); // show() вместо exec(), чтобы не блокировать MainWindow
        } else {
            main_lection *lectionWindow = new main_lection(socket, authDialog.getUserId(), nullptr);
            lectionWindow->setAttribute(Qt::WA_DeleteOnClose);
            lectionWindow->show();
        }
    }
}

// Новый слот для обработки выхода
void MainWindow::on_exitButton_clicked() {
    dialog_window_exit exitDialog(this); // Создаем экземпляр диалогового окна выхода
    if (exitDialog.exec() == QDialog::Accepted) {
        qApp->quit(); // Закрываем приложение, если нажата кнопка "Да"
    }
}
