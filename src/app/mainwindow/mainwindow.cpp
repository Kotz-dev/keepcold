//
// Created by KoTz on 14/07/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow/mainwindow.h"
#include "ui_mainwindow.h"


mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainwindow) { ui->setupUi(this); }

mainwindow::~mainwindow() { delete ui; }
