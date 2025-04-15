#ifndef DIALOG_WINDOW_EXIT_H
#define DIALOG_WINDOW_EXIT_H

#include <QDialog>

namespace Ui {
class dialog_window_exit;
}

class dialog_window_exit : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_window_exit(QWidget *parent = nullptr);
    ~dialog_window_exit();

private:
    Ui::dialog_window_exit *ui;
};

#endif // DIALOG_WINDOW_EXIT_H
