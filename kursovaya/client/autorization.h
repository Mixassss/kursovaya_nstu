#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QDialog>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    QString getUserPosition() const;
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_loginButton_clicked();
    void on_backButton_clicked();
    void on_inputChanged();
    void onServerResponse();

private:
    QString userPosition;
    Ui::Dialog *ui;
    QTcpSocket *socket;
};

#endif // AUTORIZATION_H
