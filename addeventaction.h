#ifndef ADDEVENTACTION_H
#define ADDEVENTACTION_H

#include <QDialog>

namespace Ui {
class addEventAction;
}

class addEventAction : public QDialog
{
    Q_OBJECT

public:
    explicit addEventAction(QWidget *parent = nullptr);
    ~addEventAction();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addEventAction *ui;
};

#endif // ADDEVENTACTION_H
