#ifndef ZADANIA1_H
#define ZADANIA1_H

#include <QDialog>

namespace Ui {
class zadania1;
}

class zadania1 : public QDialog
{
    Q_OBJECT

public:
    explicit zadania1(QWidget *parent = nullptr);
    ~zadania1();

private:
    Ui::zadania1 *ui;
};

#endif // ZADANIA1_H
