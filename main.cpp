#pragma comment(lib, "ws2_32.lib")
#include "mainwindow.h"
#include <QApplication>
#include "choosewindow.h"
#include "addeventaction.h"
#include "CompanyAPI.h"
#include "Entities.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    chooseWindow w;
    w.show();
    return a.exec();
}
