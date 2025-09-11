#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "database.h"

class Handler;

class Server : public QTcpServer {
    Q_OBJECT

public:
    explicit Server(Database *db, QObject *parent = nullptr);
    void start(quint16 port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    Database *m_db;
};

#endif //SERVER_H
