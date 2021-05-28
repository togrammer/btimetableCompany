#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

authorizationWindow::authorizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorizationWindow)
{
    ui->setupUi(this);
}

authorizationWindow::~authorizationWindow()
{
    delete ui;
}
