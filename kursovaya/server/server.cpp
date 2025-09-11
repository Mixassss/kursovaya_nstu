#include "server.h"
#include "handler.h"
#include <QThread>
#include <QDebug>

Server::Server(Database *db, QObject *parent)
    : QTcpServer(parent), m_db(db) {}

void Server::start(quint16 port) {
    if (!listen(QHostAddress::Any, port)) {
        qCritical() << "Не удалось запустить сервер!" << errorString();
        return;
    }
    qDebug() << "Сервер слушает порт" << port;
}

void Server::incomingConnection(qintptr socketDescriptor) {
    Handler *handler = new Handler(socketDescriptor, m_db);
    QThread *thread = new QThread;

    handler->moveToThread(thread);
    connect(thread, &QThread::started, handler, &Handler::process);
    connect(handler, &Handler::finished, thread, &QThread::quit);
    connect(handler, &Handler::finished, handler, &Handler::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}
