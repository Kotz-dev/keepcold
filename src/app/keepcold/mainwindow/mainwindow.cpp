//
// Created by KoTz on 14/07/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "app/keepcold/mainwindow/mainwindow.h"
#include <widgets/PasswordLineEdit.h>
#include <io/FileManger.h>
#include <styles/UIStyle.h>
#include "ui_mainwindow.h"
#include <app/Animation/ProgressBar.h>
#include "zxcvbn.h"


void mainwindow::Page(StackPage page) {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(page));
}

void mainwindow::navigateTo(StackPage page, QWidget *frameToAnimate,
                             const std::function<void()> &onShow) {
    Page(page);
    animateIn(frameToAnimate);

    if (onShow) {
        onShow();
    }
}


void mainwindow::on_btn_create_cofre_clicked() {
    navigateTo(StackPage::CreateVault, ui->frame_8, [this]() {
        UIStyle::Page::PasswordField::show(ui->line_password_mestra, this, "page_create_new_cofre.qss");
    });
}

void mainwindow::on_btn_back_clicked() {
    navigateTo(StackPage::Welcome, ui->frame_3, [this]() {
        UIStyle::Page::Welcome::show(ui, this);
    });
}

void mainwindow::on_btn_open_cofre_clicked() {
    navigateTo(StackPage::OpenVault, ui->frame_10, [this]() {
        UIStyle::Page::PasswordField::show(ui->line_passowrd_open_cofre, this, "page_open_exist_cofre.qss");
    });
}

void mainwindow::on_back_open_cofre_clicked() {
    navigateTo(StackPage::Welcome, ui->frame_8, [this]() {
        setStyleSheet(FileManger::loadStyleSheet(
            "keepcold\\resources\\Styles\\dark\\page_welcome.qss",
            PATCH_TYPE_::FILE_styles
        ));
    });
}

int teste(int value,QString & text);

int teste (int value,QString & text) {
    text = "";
    if (value < 20) {text = "Muito fraca"; return 1;} // muito fraca
    if (value < 36) {text = "Fraca"; return 2;} // fraca/regular
    if (value < 60) {text = "Boa"; return 3;} // boa
    if (value < 80) {text = "Forte"; return 4;} // forte
     text = "Excelente";
    return 5;
}

void mainwindow::on_line_password_mestra_textEdited(const QString &arg1) {
    ui->frame_14->show();
    ui->progressBar->show();

    auto value = ZxcvbnMatch(arg1.toStdString().c_str(), nullptr, nullptr);
    QString text;
    strengthBar->setSegments(5);
    strengthBar->setRange(0, 5);
    strengthBar->setTextVisible(false);
    strengthBar->setValue(teste(value,text));
    strengthBar->setFixedHeight(7);


    ui->label_forca_senha->setText(text);


    QLayout *existingLayout = ui->progressBar->layout();
    if (existingLayout == nullptr) {
        existingLayout = new QVBoxLayout(ui->progressBar);
        existingLayout->setContentsMargins(0, 0, 0, 0);
    }
    existingLayout->addWidget(strengthBar);
    if (arg1.isEmpty()) {
        strengthBar->setValue(0);
        ui->frame_14->hide();
        ui->label_forca_senha->clear();
        ui->progressBar->hide();
    }



}

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
     UIStyle::Page::Welcome::show(ui,this);
    ui->frame_14->hide();
}

mainwindow::~mainwindow() { delete ui; }
