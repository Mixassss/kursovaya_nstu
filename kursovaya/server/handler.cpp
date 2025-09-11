#include "handler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

Handler::Handler(qintptr socketDescriptor, Database *db, QObject *parent)
    : QObject(parent), m_socketDescriptor(socketDescriptor), m_db(db)
{
    m_socket = new QTcpSocket(this);
}

void Handler::process()
{
    if (!m_socket->setSocketDescriptor(m_socketDescriptor)) {
        qWarning() << "Не удалось установить дескриптор сокета";
        emit finished();
        return;
    }

    connect(m_socket, &QTcpSocket::readyRead, this, &Handler::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &Handler::onDisconnected);
}

void Handler::onReadyRead()
{
    m_buffer.append(m_socket->readAll());

    int index;
    while ((index = m_buffer.indexOf('\n')) != -1) {
        QByteArray line = m_buffer.left(index);
        m_buffer.remove(0, index + 1);

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(line, &error);
        if (error.error != QJsonParseError::NoError) {
            qWarning() << "[SERVER] JSON parse error:" << error.errorString() << "Data:" << line;
            continue;
        }

        if (!doc.isObject()) {
            qWarning() << "[SERVER] Not a JSON object!";
            continue;
        }

        QJsonObject request = doc.object();
        handleRequest(request);
    }
}

void Handler::handleRequest(const QJsonObject &request)
{
    QJsonObject response;
    QString cmd = request.value("type").toString();

    if (cmd == "auth") {
        QString position;
        bool ok = m_db->authenticateUser(
            request.value("login").toString(),
            request.value("password").toString(),
            position
            );

        response["type"] = "auth";
        response["status"] = ok ? "ok" : "error";
        if (ok) response["position"] = position;
    }
    else if (cmd == "add_user") {
        bool ok = m_db->addUser(
            request.value("login").toString(),
            request.value("password").toString(),
            request.value("position").toString()
            );

        response["type"] = "add_user";
        response["status"] = ok ? "ok" : "error";
    }
    else if (cmd == "delete_user") {
        bool ok = m_db->deleteUser(request.value("id").toInt());

        response["type"] = "delete_user";
        response["status"] = ok ? "ok" : "error";
        if (!ok) {
            response["reason"] = "Не удалось удалить пользователя (возможно, админ или неверный id)";
        }
    }
    else if (cmd == "list_users") {
        QJsonArray usersArray;
        QList<QVariantMap> users = m_db->getAllUsers();

        for (const QVariantMap &u : users) {
            QJsonObject userObj;
            userObj["id"] = u["id"].toInt();
            userObj["login"] = u["login"].toString();
            userObj["position"] = u["position"].toString();
            usersArray.append(userObj);
        }

        response["type"] = "list_users";
        response["status"] = "ok";
        response["users"] = usersArray;
    }
    else {
        response["type"] = cmd.isEmpty() ? "unknown" : cmd;
        response["status"] = "error";
        response["reason"] = "Unknown command";
    }

    QByteArray respData = QJsonDocument(response).toJson(QJsonDocument::Compact) + "\n";
    m_socket->write(respData);
    m_socket->flush();
}


void Handler::onDisconnected()
{
    m_socket->deleteLater();
    emit finished();
}
