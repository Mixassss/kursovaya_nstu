#ifndef RESULTS_H
#define RESULTS_H

#include <QDialog>
#include <QTcpSocket>
#include <QStandardItemModel>

namespace Ui {
class results;
}

class results : public QDialog
{
    Q_OBJECT

public:
    explicit results(QTcpSocket *socket, QWidget *parent = nullptr);
    ~results();

    void loadResults(); // метод для загрузки данных

private:
    Ui::results *ui;
    QTcpSocket *socket;
    QStandardItemModel *model; // модель для таблицы
};

#endif // RESULTS_H
