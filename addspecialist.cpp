#include "addspecialist.h"
#include "ui_addspecialist.h"
#include <string>
#include <QString>
#include "CompanyAPI.h"
#include "QMessageBox"

addSpecialist::addSpecialist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSpecialist)
{
    ui->setupUi(this);
}

addSpecialist::~addSpecialist()
{
    delete ui;
}

extern std::string companyId;

void addSpecialist::on_pushButton_clicked()
{
    QString specialistName_ = ui->specialistName->text();
    std::string specialistName = specialistName_.toStdString();
    try{
        db::CompanyAPI::createEmployee(companyId, specialistName);
    } catch(db::bttFatalError &e){
        QMessageBox::warning(this, "", e.what());
        exit(1);
    } catch(db::bttError &e){
        QMessageBox::warning(this, "", e.what());
    }
    QMessageBox::information(this, "", "Работник успешно добавлен");
}

