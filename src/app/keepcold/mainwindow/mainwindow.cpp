//
// Created by KoTz on 14/07/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "app/keepcold/mainwindow/mainwindow.h"

#include <QFileDialog>

#include "app/keepcold/windowConfig/windowconfig.h"
#include "app/keepcold/windowItem/windowitem.h"
#include "io/FileManager.h"
#include "item/logins.h"
#include "src/item/itens.h"
#include "widgets/ItemCard.h"
#include "ui_mainwindow.h"

#include <QtWidgetStoolkit/QtWidgetStoolkit.h>
#include <core/PasswordStrength.h>
#include <ui_windowconfig.h>

void mainwindow::on_Welcome_btn_criar_cofre_clicked() {
    ClearStrengthBar(ui->CreateVault_progressBar);
    ui->pageCreateVault->setAttribute(Qt::WA_TranslucentBackground);
    WindowPage::NavigetPage(StackPage::CreateVault);
}

void mainwindow::on_CreateVault_btn_voltar_clicked() {
    ClearStrengthBar(ui->CreateVault_progressBar);
    WindowPage::NavigetPage(StackPage::Welcome);
}


void mainwindow::on_Welcome_btn_abrir_cofre_clicked() {

    const QString path = FileManager::OpenFileURL(this);
    QFileInfo info(path);
    QDateTime now = info.lastModified();

    if (info.exists() == false && now.isValid() == false) return;

    FileManager::Local_usado = path;
    ui->OpenVault_label_info_modificado->setText(info.fileName() + " · " + now.toString("dd/MM/yyyy HH:mm"));
    WindowPage::NavigetPage(StackPage::OpenVault);
}

void mainwindow::on_OpenVault_btn_voltar_clicked() {
    WindowPage::NavigetPage(StackPage::Welcome);

}

void mainwindow::on_OpenVault_btn_desbloquear_clicked()
{
    WindowPage::NavigetPage(StackPage::VaultMain              );
}

void mainwindow::on_OpenVault_btn_trocar_arquivo_clicked()
{
    WindowPage::NavigetPage(StackPage::Welcome);
}

void mainwindow::on_CreateVault_btn_criar_clicked()
{
    if (ui->CreateVault_line_nome_arquivo->text().isEmpty() == false)
    {
        auto getURL = QFileDialog::getSaveFileUrl(
            this,
            "Salvar os Arquivos",
            QUrl::fromLocalFile(ui->CreateVault_line_nome_arquivo->text()),
            "Vault files (*.vault)");


        if (FileManager::CreateVaultFile(getURL))
        {
            FileManager::Local_usado = getURL.toLocalFile();
            WindowPage::NavigetPage(StackPage::VaultMain);
        }
    }
}

void mainwindow::showUI() {
    ui->CreateVault_frame_forca_senha->show();
    ui->CreateVault_progressBar->show();
}

void mainwindow::ClearStrengthBar(QProgressBar *widget) {
    if (widget != nullptr) {
        widget->setValue(0);
        widget->hide();
        ui->CreateVault_progressBar->hide();
        ui->CreateVault_frame_forca_senha->hide();
        ui->CreateVault_label_forca_senha_valor->clear();
        return;
    }
}

void mainwindow::on_btn_max_window_clicked() {
    QtToolkit::Window::Maximizer::toggle(this);
}
void mainwindow::on_btn_min_window_clicked() {
    showMinimized();
}
void mainwindow::on_btn_close_window_clicked() {
    close();
}


void mainwindow::on_VaultMain_btn_documento_clicked() {
   ui->VaultMain_stack_item_paginas->setCurrentIndex(3);
}


// Desgin QProcesdar
void mainwindow::setupStrengthBar(int value)
{
    if (ui->CreateVault_line_senha_mestra->text().isEmpty())
    {
        ClearStrengthBar(ui->CreateVault_progressBar);
    }
    QtToolkit::ProgessBar::SegmentedProgressBar::applyProgressBar(value, ui->CreateVault_progressBar);
}

void mainwindow::on_VaultMain_btn_configuracao_clicked()
{
    windowConfig *janela = new windowConfig(this);
    auto blur =  QtToolkit::Blur::applyBlur(this,4);
    janela->move(this->geometry().center() - QPoint(janela->width() / 2, janela->height() / 2));
    janela->exec();
    if (blur != nullptr && janela->isVisible() == false)
    {
        delete janela;
        delete blur;
    }
}

void mainwindow::on_CreateVault_line_confirmar_senha_textEdited(const QString& arg1)
{
    if (arg1.isEmpty() == true)
    {
        ui->CreateVault_label_erro_senha->hide();
        ui->CreateVault_line_confirmar_senha->setStyleSheet("border: 1px solid #3a4368");
        return;
    }
    if (!PasswordStrength::PassowrdIguais(arg1))
    {
        ui->CreateVault_label_erro_senha->setStyleSheet("color: rgb(239, 107, 107);");
        ui->CreateVault_line_confirmar_senha->setStyleSheet("border: 1px solid #ef6b6b;");
        ui->CreateVault_label_erro_senha->show();
    }
    else
    {
        ui->CreateVault_label_erro_senha->hide();
    }
}
// Line Passowrd
void mainwindow::on_CreateVault_line_senha_mestra_textEdited(const QString& arg1)
{
    showUI();
    QString text = arg1;
    setupStrengthBar(PasswordStrength::evaluate(text));
    ui->CreateVault_label_forca_senha_valor->setText(text);
}

void mainwindow::on_VaultMain_btn_add_item_clicked()
{
    windowItem *WindowItem = new windowItem(this);
    auto blur =  QtToolkit::Blur::applyBlur(this,4);
    WindowItem->move(QtToolkit::geometry::centeredPosition(this,WindowItem));
    WindowItem->exec();
    atualizarLista();
    if (blur != nullptr && WindowItem->isVisible() == false)
    {
        delete WindowItem;
        delete blur;
    }

}

void mainwindow::atualizarLista()
{
    ui->VaultMain_listView->clear();

    for (const auto &item : itens::todos)
    {
        auto *linha = new QListWidgetItem(ui->VaultMain_listView);
        auto *card  = new ItemCard(*item);



        linha->setSizeHint(card->sizeHint());
        linha->setData(Qt::UserRole, item->getId());
        card->setStyleSheet("background: #2c3760; border: 1px solid transparent;border-radius: 10px;");
        ui->VaultMain_listView->setSpacing(2);
        card->setFixedSize(280,55);
        ui->VaultMain_listView->setItemWidget(linha, card);
    }
}

void mainwindow::itemClicado(QListWidgetItem *linha)
{
    const QString id = linha->data(Qt::UserRole).toString();

    for (const auto &item : itens::todos)
    {
        if (item->getId() == id)
        {
            qDebug() << "itemClicado" << id;
           /// ui->VaultMain_stack_item_paginas->setCurrentIndex(0);
            return;
        }
    }
}
mainwindow::mainwindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    WindowPage::__init__(ui, this);
   // ui->VaultMain_stack_item_paginas->setCurrentIndex(6);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QtToolkit::Window::Dragger::attach(this);

    connect(ui->VaultMain_listView, &QListWidget::itemClicked, this, &mainwindow::itemClicado);
}
mainwindow::~mainwindow() { delete ui; }
