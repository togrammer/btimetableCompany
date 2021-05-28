#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QDialog>

namespace Ui {
class chooseWindow;
}

class chooseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit chooseWindow(QWidget *parent = nullptr);
    ~chooseWindow();

private slots:
    void on_registrationButton_clicked();

    void on_authorizationButton_clicked();

private:
    Ui::chooseWindow *ui;
};

#endif // CHOOSEWINDOW_H
