#ifndef TEST3_H
#define TEST3_H

#include <QDialog>

namespace Ui {
class test3;
}

class test3 : public QDialog
{
    Q_OBJECT

public:
    explicit test3(QWidget *parent = nullptr);
    ~test3();

private:
    Ui::test3 *ui;
};

#endif // TEST3_H
