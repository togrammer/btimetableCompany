#ifndef CHOOSEACTION_H
#define CHOOSEACTION_H

#include <QDialog>

namespace Ui {
class chooseAction;
}

class chooseAction : public QDialog
{
    Q_OBJECT

public:
    explicit chooseAction(QWidget *parent = nullptr);
    ~chooseAction();

private slots:
    void on_addEventButton_clicked();

    void on_addEmployeeButton_clicked();

    void on_deleteEmployeeButton_clicked();

    void on_deleteEventButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::chooseAction *ui;
};

#endif // CHOOSEACTION_H
