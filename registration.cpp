#include "registration.h"
#include "ui_registration.h"
#include <QString>
#include <regex>
#include <QMessageBox>
#include <iostream>
#include "CompanyAPI.h"
#include "Entities.h"
#include <string>

registration::registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
}

registration::~registration()
{
    delete ui;
}

std::string hash(std::string s){
    s += "wrgwuhboweuifnowubhregu";
    const int p = 31;
    long long hash = 0, p_pow = 1;
    long long MOD = 1e9 + 7;
    for (size_t i=0; i<s.length(); ++i)
    {
        hash += ((s[i] - 'a' + 1) * p_pow) % MOD;
        p_pow = (p_pow * p) % MOD;
    }
    return std::to_string(hash);
}

void registration::on_pushButton_clicked()
{
    QString companyName_ = ui->companyName->text();
    QString telephoneNumber_ = ui->telephoneNumber->text();
    QString password1_ = ui->password1->text();
    QString password2_ = ui->password2->text();
    std::string companyName = companyName_.toStdString();
    std::string telephoneNumber = telephoneNumber_.toStdString();
    std::string password1 = password1_.toStdString();
    std::string password2 = password2_.toStdString();
    bool errorTelephoneNumber = 0;
    {
        std::regex inputPattern(R"(^\s{0,}\+7-[0-9]{3}-[0-9]{3}-[0-9]{2}-[0-9]{2}\s{0,})");
        if (std::regex_match(telephoneNumber, inputPattern) == 0) {
            errorTelephoneNumber = 1;
        }
    }
    bool errorPassword = 0;
    if(password1 != password2){
        errorPassword = 1;
    }
    if(errorPassword || errorTelephoneNumber){
        QString errors = "";
        if(errorPassword){
            errors += "Пароли не совпадают\n";
        }
        if(errorTelephoneNumber){
            errors += "Телефон введен некорректно\n";
        }
        QMessageBox::warning(this, "Ошибка", "Ошибка:\n" + errors);
    } else {
        try {
            db::CompanyAPI::createCompany(telephoneNumber, /*password1*/hash(password1), companyName);
            QMessageBox::information(this, "", "Регистрация прошла успешно");
        } catch(db::bttError){
            QMessageBox::warning(this, "", "Ошибка");
        } catch(db::bttFatalError){
            QMessageBox::warning(this, "", "Ошибка");
            exit(1);
        }
    }
}
