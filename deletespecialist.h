#ifndef DELETESPECIALIST_H
#define DELETESPECIALIST_H

#include <QDialog>

namespace Ui {
class deleteSpecialist;
}

class deleteSpecialist : public QDialog
{
    Q_OBJECT

public:
    explicit deleteSpecialist(QWidget *parent = nullptr);
    ~deleteSpecialist();

private slots:
    void on_pushButton_clicked();

private:
    Ui::deleteSpecialist *ui;
};

#endif // DELETESPECIALIST_H
