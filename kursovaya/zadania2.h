#ifndef ZADANIA2_H
#define ZADANIA2_H

#include <QDialog>

namespace Ui {
class zadania2;
}

class zadania2 : public QDialog
{
    Q_OBJECT

public:
    explicit zadania2(QWidget *parent = nullptr);
    ~zadania2();

private:
    Ui::zadania2 *ui;
};

#endif // ZADANIA2_H
