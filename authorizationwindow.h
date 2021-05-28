#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>

namespace Ui {
class authorizationWindow;
}

class authorizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit authorizationWindow(QWidget *parent = nullptr);
    ~authorizationWindow();

private:
    Ui::authorizationWindow *ui;
};

#endif // AUTHORIZATIONWINDOW_H
