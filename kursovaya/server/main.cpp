#include <QCoreApplication>
#include "server.h"
#include "database.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Database db;
    if (!db.connectToDatabase()) {
        qWarning() << "Не удалось подключиться к базе!";
        return -1;
    }

    Server server(&db);
    server.start(9878);

    return app.exec();  // запускаем цикл обработки событий
}
