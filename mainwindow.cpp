#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <regex>
#include <QMessageBox>
#include <string>
#include <sstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

extern std::string companyId;

