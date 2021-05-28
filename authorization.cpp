#include "authorization.h"
#include "ui_authorization.h"
#include "chooseaction.h"
#include "CompanyAPI.h"
#include <iostream>
#include <QMessageBox>
#include <string>

authorization::authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
}

authorization::~authorization()
{
    delete ui;
}

std::string companyId;

std::string hash1(std::string s){
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

void authorization::on_pushButton_clicked()
{
    QString qCompanyPhone = ui->phoneNumber->text();
    QString qCompanyPassword = ui->password->text();
    std::string phone = qCompanyPhone.toStdString();
    std::string password = qCompanyPassword.toStdString();
    try{
        companyId = db::CompanyAPI::authorizeCompany(phone, /*password*/ hash1(password));
        chooseAction actionWindow;
        actionWindow.setModal(true);
        actionWindow.exec();
    } catch(db::bttFatalError &e){
        QMessageBox::warning(this, "", e.what());
        exit(1);
    } catch(db::bttError &e){
        QMessageBox::warning(this, "", e.what());
    }
}
