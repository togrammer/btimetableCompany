#include "addeventaction.h"
#include "ui_addeventaction.h"
#include <vector>
#include "Entities.h"
#include "CompanyAPI.h"
#include <iostream>
#include <regex>
#include <QMessageBox>
#include <string>
#include <sstream>
#include "time.h"

extern std::string companyId;

addEventAction::addEventAction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addEventAction)
{
    ui->setupUi(this);
    std::vector<long long> employees;
    try{
        employees = db::CompanyAPI::listEmployeesOfCompany(companyId);
    } catch(db::bttFatalError &e){
        QMessageBox::warning(this, "", e.what());
        exit(1);
    } catch(db::bttError &e){
        QMessageBox::warning(this, "", e.what());
    }
    for(long long i = 0; i  < employees.size(); i++){
        try{
            db::Employee currentEmployee = db::CompanyAPI::getEmployeeById(companyId, employees[i]);
            ui->specialist->addItem(QString::fromStdString(currentEmployee.fullName));
        } catch(db::bttFatalError &e){
            QMessageBox::warning(this, "", e.what());
            exit(1);
        } catch(db::bttError &e){
            QMessageBox::warning(this, "", e.what());
        }
    }
}

addEventAction::~addEventAction()
{
    delete ui;
}

void addEventAction::on_pushButton_clicked()
{
    int specialistIndex = ui->specialist->currentIndex();
    std::vector<long long> employees;
    try{
        employees = db::CompanyAPI::listEmployeesOfCompany(companyId);
    } catch(db::bttError){
        QMessageBox::warning(this, "", "Ошибка");
    } catch(db::bttFatalError){
        QMessageBox::warning(this, "", "Ошибка");
        exit(1);
    }
    try{
        db::Employee currentEmployee = db::CompanyAPI::getEmployeeById(companyId, employees[specialistIndex]);
        QString beginDate_ =  ui->beginDate->text();
        QString beginTime_ = ui->beginTime->text();
        QString duration_ = ui->duration->text();
        QString title_ = ui->title->text();
        std::string beginDate = beginDate_.toStdString();
        std::string beginTime = beginTime_.toStdString();
        std::string duration__ = duration_.toStdString();
        std::string title = title_.toStdString();
        bool errorSpecialist = 0;
        bool errorDate = 0;
        bool errorTime = 0;
        bool errorDuration = 0;
        int day, month, year;
        {
        std::regex inputPattern(R"(^\s{0,}[0-9]{2,2}[.][0-9]{2,2}[.][0-9]{4,4}\s{0,})");
            if (std::regex_match(beginDate, inputPattern) == 0) {
                errorDate = 1;
            } else {
                std::stringstream inputStream1(beginDate);
                char c;
                inputStream1 >> day >> c >> month >> c >> year;
                if (!(day >= 1 && day <= 31 && month >= 1 && month <= 12))
                    errorDate = 1;
            }
        }
        int beginHour, beginMinute;
        {
        std::regex inputPattern(R"(^\s{0,}[0-9]{2,2}[.][0-9]{2,2}\s{0,})");
            if (std::regex_match(beginTime, inputPattern) == 0) {
                errorTime = 1;
            } else {
                char c;
                std::stringstream inputStream1(beginTime);
                inputStream1 >> beginHour >> c >> beginMinute;
                if (!(beginHour >= 0 && beginHour <= 23 && beginMinute >= 0 &&
                    beginMinute <= 59))
                    errorTime = 1;
            }
        }
        int duration;
        {
        std::regex inputPattern(R"(^\s{0,}[0-9]{1,}\s{0,})");
            if (std::regex_match(duration__, inputPattern) == 0) {
                errorDuration = 1;
            } else  {
                std::stringstream inputStream1(duration__);
                inputStream1 >> duration;
            }
        }
        if(errorDate || errorDuration || errorSpecialist || errorTime){
            QString errors = "";
            if(errorSpecialist)
                errors += "Имя специалиста\n";
            if(errorDate)
                errors += "Дата начала\n";
            if(errorTime)
                errors += "Время начала\n";
            if(errorDuration)
                errors += "Длительность";
            QMessageBox::warning(this, "Ошибка", "Следующие поля введены некорректно:\n" + errors);
        } else {
            QMessageBox::information(this, "", "Событие успешно добавлено");
            time_t currentTime;
            time(&currentTime);
           struct tm *Time = localtime(&currentTime);
           Time->tm_mon = month - 1;
           Time->tm_year = year - 1900;
           Time->tm_mday = day;
           Time->tm_hour = beginHour + 3;
           Time->tm_min = beginMinute;
           Time->tm_sec = 0;
           time_t time_ = mktime(Time);
    //       std::cout << (char*) asctime(Time) << std::endl;
           try{
                db::CompanyAPI::createOrder(companyId, title, time_, duration, currentEmployee.id);
           } catch(db::bttError){
               QMessageBox::warning(this, "", "Ошибка");
           } catch(db::bttFatalError){
               QMessageBox::warning(this, "", "Ошибка");
               exit(1);
           }
        }
    } catch(db::bttError){
        QMessageBox::warning(this, "", "Ошибка");
    } catch(db::bttFatalError){
        QMessageBox::warning(this, "", "Ошибка");
        exit(1);
    }
}
