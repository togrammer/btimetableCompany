#include "deletespecialist.h"
#include "ui_deletespecialist.h"
#include "CompanyAPI.h"
#include "Entities.h"
#include <string>
#include <QMessageBox>

extern std::string companyId;

deleteSpecialist::deleteSpecialist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteSpecialist)
{
    ui->setupUi(this);
    try{
        std::vector<long long> employees = db::CompanyAPI::listEmployeesOfCompany(companyId);
        for(long long i = 0; i  < employees.size(); i++){
            db::Employee currentEmployee = db::CompanyAPI::getEmployeeById(companyId, employees[i]);
            ui->specialist->addItem(QString::fromStdString(currentEmployee.fullName));
        }
    } catch(db::bttFatalError &e){
        QMessageBox::warning(this, "", e.what());
        exit(1);
    } catch(db::bttError &e){
        QMessageBox::warning(this, "", e.what());
    }
}

deleteSpecialist::~deleteSpecialist()
{
    delete ui;
}

void deleteSpecialist::on_pushButton_clicked()
{
    int specialistIndex = ui->specialist->currentIndex();
    try{
        std::vector<long long> employees = db::CompanyAPI::listEmployeesOfCompany(companyId);
        db::Employee currentEmployee = db::CompanyAPI::getEmployeeById(companyId, employees[specialistIndex]);
        db::CompanyAPI::deleteEmployee(companyId, currentEmployee.id);
        QMessageBox::information(this, "", "Работник успешно удален");
    } catch(db::bttFatalError &e){
        QMessageBox::warning(this, "", e.what());
        exit(1);
    } catch(db::bttError &e){
        QMessageBox::warning(this, "", e.what());
    }
}

