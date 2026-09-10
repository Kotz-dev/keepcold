//
// Created by KoTz on 18/08/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_windowconfig.h" resolved

#include "../../../../include/app/keepcold/windowConfig/windowconfig.h"

#include "io/FileManager.h"
#include "ui_windowconfig.h"

windowConfig::windowConfig(QWidget* parent)
    : QDialog(parent),
      ui(new Ui::windowConfig)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setStyleSheet(FileManager::loadStyleSheet("keepcold\\resources\\Styles\\windowConfig\\dark\\WindowConfig.qss",PATCH_TYPE_::FILE_styles));
    setAttribute(Qt::WA_TranslucentBackground);
}

void windowConfig::on_btn_fechar_clicked()
{
   close();
}

windowConfig::~windowConfig()
{
    delete ui;
}
