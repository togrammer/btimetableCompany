#ifndef LISTORDERS_H
#define LISTORDERS_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class listOrders;
}

class listOrders : public QDialog
{
    Q_OBJECT

public:
    explicit listOrders(QWidget *parent = nullptr);
    ~listOrders();

private:
    Ui::listOrders *ui;
    QStandardItemModel *model;
};

#endif // LISTORDERS_H
