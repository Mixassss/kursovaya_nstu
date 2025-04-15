#ifndef ZADANIA3_H
#define ZADANIA3_H

#include <QDialog>

namespace Ui {
class zadania3;
}

class zadania3 : public QDialog
{
    Q_OBJECT

public:
    explicit zadania3(QWidget *parent = nullptr);
    ~zadania3();

private:
    Ui::zadania3 *ui;
};

#endif // ZADANIA3_H
