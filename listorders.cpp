#include "listorders.h"
#include "ui_listorders.h"
#include "CompanyAPI.h"
#include "Entities.h"
#include <string>
#include <QString>
#include <QMessageBox>

extern std::string companyId;

listOrders::listOrders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listOrders)
{
    ui->setupUi(this);
//    orders.append(QList<QString>({"Event", "Company", "Master", "Start", "Finish", "Status"}));
    try{
        std::vector<long long> orders = db::CompanyAPI::listAllOrdersOfCompany(companyId);
        model = new QStandardItemModel(orders.size(), 5, this);
        ui->orders->setModel(model);
        model->setHeaderData(0, Qt::Horizontal, "Event");
        model->setHeaderData(1, Qt::Horizontal, "Master");
        model->setHeaderData(2, Qt::Horizontal, "Start");
        model->setHeaderData(3, Qt::Horizontal, "Duration");
        model->setHeaderData(4, Qt::Horizontal, "Status");
        QModelIndex index;
        for(int row = 0; row < model->rowCount(); ++row){
            index = model->index(row, 0);
            try{
                db::Order currentOrder = db::CompanyAPI::getOrderById(companyId, orders[row]);
                QString title_ = QString::fromStdString(currentOrder.title);
                model->setData(index, title_);
                index = model->index(row, 1);
                QString master_ = QString::fromStdString(db::CompanyAPI::getEmployeeById(companyId, currentOrder.employeeId).fullName);
                model->setData(index, master_);
                index = model->index(row, 2);
                const time_t timeStart = currentOrder.timeStart;
                std::string time_ = asctime(gmtime(&timeStart));
                model->setData(index, QString::fromStdString(time_));
                index = model->index(row, 3);
                model->setData(index, QString::fromStdString(std::to_string(currentOrder.duration)));
                index = model->index(row, 4);
                if(currentOrder.status == 0){
                    model->setData(index, "vacant");
                } else if(currentOrder.status == 1){
                    model->setData(index, "booked");
                } else {
                    model->setData(index, "deleted");
                }
            } catch(db::bttFatalError &e){
                QMessageBox::warning(this, "", e.what());
                exit(1);
            } catch(db::bttError &e){
                QMessageBox::warning(this, "", e.what());
            }
        }
    } catch(db::bttError){
        QMessageBox::warning(this, "", "Ошибка");
    } catch(db::bttFatalError){
        QMessageBox::warning(this, "", "Ошибка");
        exit(1);
    }
}

listOrders::~listOrders()
{
    delete ui;
}
