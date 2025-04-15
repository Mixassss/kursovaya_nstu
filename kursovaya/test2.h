#ifndef TEST2_H
#define TEST2_H

#include <QDialog>

namespace Ui {
class test2;
}

class test2 : public QDialog
{
    Q_OBJECT

public:
    explicit test2(QWidget *parent = nullptr);
    ~test2();

private:
    Ui::test2 *ui;
};

#endif // TEST2_H
