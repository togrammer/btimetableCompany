#include "deleteorder.h"
#include "ui_deleteorder.h"
#include "CompanyAPI.h"
#include <iostream>
#include <string>
#include <QMessageBox>
#include "Entities.h"

extern std::string companyId;

deleteOrder::deleteOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteOrder)
{
    ui->setupUi(this);
    try{
        std::vector<long long> orders = db::CompanyAPI::listVacantOrdersOfCompany(companyId);
        for(long long i = 0; i  < orders.size(); i++){
            try{
                db::Order currentOrder = db::CompanyAPI::getOrderById(companyId, orders[i]);
                ui->order->addItem(QString::fromStdString(currentOrder.title));
            } catch(db::bttFatalError &e){
                QMessageBox::warning(this, "", e.what());
                exit(1);
            } catch(db::bttError &e){
                QMessageBox::warning(this, "", e.what());
            }
        }
    } catch(db::bttFatalError &e){
        QMessageBox::warning(this, "", e.what());
        exit(1);
    } catch(db::bttError &e){
        QMessageBox::warning(this, "", e.what());
    }
}

deleteOrder::~deleteOrder()
{
    delete ui;
}

void deleteOrder::on_pushButton_clicked()
{
    int orderIndex = ui->order->currentIndex();
    try{
        std::vector<long long> orders = db::CompanyAPI::listVacantOrdersOfCompany(companyId);
        db::Order currentOrder = db::CompanyAPI::getOrderById(companyId, orders[orderIndex]);
        db::CompanyAPI::deleteOrder(companyId, currentOrder.id);
        QMessageBox::information(this, "", "Событие успешно удалено");
    } catch(db::bttFatalError &e){
        QMessageBox::warning(this, "", e.what());
        exit(1);
    } catch(db::bttError &e){
        QMessageBox::warning(this, "", e.what());
    }
}

