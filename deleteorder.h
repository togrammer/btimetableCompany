#ifndef DELETEORDER_H
#define DELETEORDER_H

#include <QDialog>

namespace Ui {
class deleteOrder;
}

class deleteOrder : public QDialog
{
    Q_OBJECT

public:
    explicit deleteOrder(QWidget *parent = nullptr);
    ~deleteOrder();

private slots:
    void on_pushButton_clicked();

private:
    Ui::deleteOrder *ui;
};

#endif // DELETEORDER_H
