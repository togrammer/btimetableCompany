#include "choosewindow.h"
#include "ui_choosewindow.h"
#include "registration.h"
#include "authorization.h"

chooseWindow::chooseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseWindow)
{
    ui->setupUi(this);
}

chooseWindow::~chooseWindow()
{
    delete ui;
}

void chooseWindow::on_registrationButton_clicked()
{
    registration regWindow;
    regWindow.setModal(true);
    regWindow.exec();
}

void chooseWindow::on_authorizationButton_clicked()
{
    authorization authWindow;
    authWindow.setModal(true);
    authWindow.exec();
}
