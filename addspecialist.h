#ifndef ADDSPECIALIST_H
#define ADDSPECIALIST_H

#include <QDialog>

namespace Ui {
class addSpecialist;
}

class addSpecialist : public QDialog
{
    Q_OBJECT

public:
    explicit addSpecialist(QWidget *parent = nullptr);
    ~addSpecialist();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addSpecialist *ui;
};

#endif // ADDSPECIALIST_H
