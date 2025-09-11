#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonArray>
#include "database.h"

class Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler(qintptr socketDescriptor, Database *db, QObject *parent = nullptr);

signals:
    void finished();

public slots:
    void process();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *m_socket;
    qintptr m_socketDescriptor;
    Database *m_db;
    QByteArray m_buffer;

    void handleRequest(const QJsonObject &request);
};

#endif // HANDLER_H
