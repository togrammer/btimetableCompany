#include "chooseaction.h"
#include "ui_chooseaction.h"
#include "addeventaction.h"
#include "addspecialist.h"
#include "deletespecialist.h"
#include "deleteorder.h"
#include "listorders.h"

chooseAction::chooseAction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseAction)
{
    ui->setupUi(this);
}

chooseAction::~chooseAction()
{
    delete ui;
}

void chooseAction::on_addEventButton_clicked()
{
    addEventAction addEvent;
    addEvent.setModal(true);
    addEvent.exec();
}


void chooseAction::on_addEmployeeButton_clicked()
{
    addSpecialist addSpec;
    addSpec.setModal(true);
    addSpec.exec();
}


void chooseAction::on_deleteEmployeeButton_clicked()
{
    deleteSpecialist delSpec;
    delSpec.setModal(true);
    delSpec.exec();
}


void chooseAction::on_deleteEventButton_clicked()
{
    deleteOrder delOrd;
    delOrd.setModal(true);
    delOrd.exec();
}


void chooseAction::on_pushButton_clicked()
{
    listOrders listOrd;
    listOrd.setModal(true);
    listOrd.exec();
}

