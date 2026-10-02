//
// Created by KoTz on 30/07/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_windowitem.h" resolved

#include "../../../../include/app/keepcold/windowItem/windowitem.h"

#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <vector>

#include "item/Note.h"
#include "item/arquivo.h"
#include "item/cartao.h"
#include "item/identidade.h"
#include "item/key.h"
#include "item/logins.h"
#include "item/recuperacao.h"
#include "item/wifi.h"
#include "src/io/json_.h"
#include "src/item/itens.h"
#include "ui_windowitem.h"

#include <QtWidgetStoolkit/QtWidgetStoolkit.h>
#include <io/FileManager.h>
#include <magic_enum/magic_enum.hpp>

QUrl loadFile();
QUrl loadFile()
{
    return QFileDialog::getOpenFileUrl(
         nullptr, ("Selecionar arquivo"), QUrl(), ("Vault files (*.vault)"));
}



void windowItem::buildItemGroups()
{
    itemGroups_ = {
        {ui->btn_logins,      ui->btn_cancelar,             ui->btn_trocar_type_logins,      ui->btn_save_item_logins,      LOGINS,      QSize(0, 0), "Novo logins",      ":/images/36x36/logo_login_badge.png",       "Email, senha, 2FA e URL",           ItemGroup{ui->line_nome_item_logins}},
        {ui->btn_note,        ui->btn_cancelar_note,        ui->btn_trocar_type_note,        ui->btn_save_item_note,        NOTE,        QSize(0, 0), "Novo notas",       ":/images/36x36/logo_documento_badge.png",   "Texto livre criptografado",         ItemGroup{ui->line_nome_item_note}},
        {ui->btn_key,         ui->btn_cancelar_key,         ui->btn_trocar_type_key,         ui->btn_save_item_key,         KEYS,        QSize(0, 0), "Novo chaves",      ":/images/36x36/logo_terminal_badge.png",    "Token, API key, chave SSH",         ItemGroup{ui->line_nome_item_key}},
        {ui->btn_cartoes,     ui->btn_cancelar_cartao,      ui->btn_trocar_type_cartao,      ui->btn_save_item_cartao,      CARTAO,      QSize(0, 0), "Novo cartão",      ":/images/36x36/logo_cartao_badge.png",      "Cartão de crédito ou débito",       ItemGroup{ui->line_nome_item_cartao}},
        {ui->btn_identidade,  ui->btn_cancelar_identidade,  ui->btn_trocar_type_identidade,  ui->btn_save_item_identidade,  IDENTIDADE,  QSize(0, 0), "Novo identidade",  ":/images/36x36/logo_idadente_badge.png",    "CPF, RG, CNH e dados pessoais",     ItemGroup{ui->line_nome_item_identidade}},
        {ui->btn_wifi,        ui->btn_cancelar_wifi,        ui->btn_trocar_type_wifi,        ui->btn_save_item_wifi,        WIFI,        QSize(0, 0), "Novo WI-FI",       ":/images/36x36/logo_wifi_badge.png",        "Rede e senha de Wi-Fi",             ItemGroup{ui->line_nome_item_wifi}},
        {ui->btn_recuperacao, ui->btn_cancelar_recuperacao, ui->btn_trocar_type_recuperacao, ui->btn_save_item_recuperacao, RECUPERACAO, QSize(0, 0), "Novo recuperação", ":/images/36x36/logo_recuperacao_badge.png", "Backup codes de 2FA",               ItemGroup{ui->line_nome_item_recuperacao}},
        {ui->btn_file,        ui->btn_cancelar_file,        ui->btn_trocar_type_file,        ui->btn_save_item_file,        FILE_PAGE,   QSize(0, 0), "Novo arquivos",    ":/images/36x36/logo_file_badge.png",        "Anexar arquivo criptografado",      ItemGroup{ui->line_nome_item_file}},
    };
}

void windowItem::setupButtonCards()
{
    for (const auto& group : itemGroups_)
    {

        QPushButton* button = group.btnCard;
        if (button == nullptr)
            continue;

        const QString title = button->text();
        button->setText("");

        auto* icon = new QLabel(button);
        icon->setPixmap(QPixmap(group.icone).scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        icon->setFixedSize(32, 32);
        icon->setAttribute(Qt::WA_TransparentForMouseEvents);

        auto* titleLabel = new QLabel(title, button);
        titleLabel->setStyleSheet("font-weight: bold; font-size: 13px;");
        titleLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

        auto* descLabel = new QLabel(group.descricao, button);
        descLabel->setStyleSheet("color: rgb(122, 133, 168); font-size: 11px;");
        descLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        descLabel->setWordWrap(true);

        auto* textLayout = new QVBoxLayout();
        textLayout->setContentsMargins(0, 5, 4, 4);
        textLayout->setSpacing(0);
        textLayout->addWidget(titleLabel);
        textLayout->addWidget(descLabel);

        auto* layout = new QHBoxLayout(button);
        layout->setContentsMargins(14, 0, 14, 0);
        layout->setSpacing(12);
        layout->addWidget(icon, 0, Qt::AlignVCenter);
        layout->addLayout(textLayout, 0);
        layout->addStretch(1);
    }
}

void windowItem::init_()
{
    for (const auto& group : itemGroups_)
    {
        group.btnSalvar->setEnabled(false);
        group.btnSalvar->setCheckable(false);
        for (QPushButton* btn : {group.btnCard, group.btnCancelar, group.btnTrocarType, group.btnSalvar})
        {
            if (btn != nullptr)
                connect(btn, &QPushButton::clicked, this, &windowItem::onMenuButtonClicked);
        }

        connect(group.obj.lineName, &QLineEdit::textChanged, this, &windowItem::atualizarEstadoBotaoSalvar);
    }

}

void windowItem::atualizarEstadoBotaoSalvar()
{
    auto* line = QtToolkit::Signal::getObjet<QLineEdit>(sender());
    if (line == nullptr)
        return;

    for (const auto& group : itemGroups_)
    {
        if (group.obj.lineName != line)
            continue;

        const bool hasText = !line->text().isEmpty();
        group.btnSalvar->setEnabled(hasText);
        group.btnSalvar->setCheckable(hasText);
        return;
    }
}

windowItem::windowItem(QWidget* parent)
    : QDialog(parent),
      ui(new Ui::windowItem)
{
    ui->setupUi(this);
    buildItemGroups();
    applyItemStyle();
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    QtToolkit::Animation::fadeSlideIn(ui->page_itens,100,50);
    setStyleSheet(FileManager::loadStyleSheet("keepcold\\resources\\Styles\\windowItem\\dark\\windowItem.qss", PATCH_TYPE_::FILE_styles));
    setAttribute(Qt::WA_TranslucentBackground);
    setupButtonCards();
    ui->logo_item->hide();
    setFixedSize(janela);
    ui->stackedWidget->setCurrentIndex(MENU);
    ui->progressBar->hide();
    btn_upload_clicked();
    init_();
}

void windowItem::on_btn_trocar_file_clicked()
{
    getfile(loadFile());
    ui->stack_file->setCurrentIndex(1);
    QtToolkit::Frame::ClickHelper::setEnabled(false);
}

void windowItem::getfile(QUrl file)
{
    if (file.isEmpty() == false)
    {
        ui->file_name_label->setText(file.fileName());
        ui->file_memory_label->setText(FileManager::formattedFileSize(file));
    }
}

void windowItem::on_btn_download_file_clicked()
{
    //qDebug () << QFileDialog::getSaveFileUrl(this,"teste",QUrl("/home/kotz/Área de trabalho/data.vx"));
}

void windowItem::btn_upload_clicked()
{
    QtToolkit::Frame::makeClickable(ui->btn_file_upload, [this]() {
          getfile(loadFile());

            ui->stack_file->setCurrentIndex(1);
           QtToolkit::Frame::ClickHelper::setEnabled(false);
    });
}

void windowItem::applyItemStyle()
{
    const std::vector<QWidget*> pages = {
        ui->page_note,
        ui->page_keys,
        ui->page_item_logins,
        ui->page_cartao,
        ui->page_identidade,
        ui->page_wifi,
        ui->page_file,
        ui->page_recuperacao,
    };

    for (auto* p : pages)
    {
        if (p == nullptr)
            continue;

        p->setStyleSheet("");
        p->setStyleSheet(FileManager::loadStyleSheet("keepcold\\resources\\Styles\\windowItem\\dark\\newItem\\item_.qss", PATCH_TYPE_::FILE_styles));
    }
}

void windowItem::on_btn_close_clicked()
{
    close();
}

void windowItem::onMenuButtonClicked()
{
    auto* btn = QtToolkit::Signal::getObjet<QPushButton>(sender());
    if (btn == nullptr)
        return;


    for (const auto& group : itemGroups_)
    {

        if (btn == group.btnCancelar)
        {
            close();
            return;
        }

        if (btn == group.btnTrocarType)
        {
            setFixedSize(janela);
            ui->page_itens->setStyleSheet("");
            ui->stackedWidget->setCurrentIndex(MENU);
            ui->label->setText("Novo Item");
            ui->logo_item->hide();
            if (group.obj.lineName != nullptr)
            {
                const QString nome = group.obj.lineName->text();
                for (auto& i : itemGroups_)
                {
                    if (i.obj.lineName != nullptr)
                        i.obj.lineName->setText(nome);
                }
            }
            return;
        }

        if (btn == group.btnSalvar)
        {
            adicionarItem(group.pageIndex);
            json_::writeFileToJson(itens::todos,FileManager::Local_usado);
            close();
            return;
        }

        if (btn == group.btnCard)
        {
            ui->logo_item->setPixmap(QPixmap(group.icone));
            ui->logo_item->show();
            ui->label->setText(group.titulo);
            setFixedSize(group.size);
            ui->stackedWidget->setCurrentIndex(group.pageIndex);
            return;
        }
    }
}

void windowItem::adicionarItem(int pageIndex)
{
    switch (pageIndex)
    {
    case LOGINS:
    {
        auto novo = std::make_unique<logins>();
        novo->setNome(ui->line_nome_item_logins->text());
        novo->setEmail(ui->lineEdit_2->text());
        novo->setPassword(ui->lineEdit_3->text());
        novo->set2fa(ui->lineEdit_4->text());
        novo->setURL(ui->lineEdit_5->text());
        novo->setCodigoRecuperacao(ui->lineEdit_6->text());
        itens::todos.push_back(std::move(novo));
        break;
    }
    case NOTE:
    {
        auto novo = std::make_unique<Note>();
        novo->setNome(ui->line_nome_item_note->text());
        novo->setConteudo(ui->textEdit_note->toPlainText());
        itens::todos.push_back(std::move(novo));
        break;
    }
    case KEYS:
    {
        auto novo = std::make_unique<key>();
        novo->setNome(ui->line_nome_item_key->text());
        novo->setServico(ui->line_service_key->text());
        novo->setChave(ui->line_key_ItemKey->text());
        novo->setNote(ui->text_note_key->toPlainText());
        itens::todos.push_back(std::move(novo));
        break;
    }
    case RECUPERACAO:
    {
        auto novo = std::make_unique<recuperacao>();
        novo->setNome(ui->line_nome_item_recuperacao->text());
        novo->setCodigos(ui->textEdit_key_recuperacao->toPlainText());
        itens::todos.push_back(std::move(novo));
        break;
    }
    case CARTAO:
    {
        auto novo = std::make_unique<cartao>();
        novo->setNome(ui->line_nome_item_cartao->text());
        novo->setTitular(ui->line_titular_cartao->text());
        novo->setNumero(ui->line_numero_cartao->text());
        novo->setValidade(ui->line_validade_cartao->text());
        novo->setCvv(ui->line_cvv_cartao->text());
        novo->setBandeira(ui->line_bandeira_cartao->text());
        itens::todos.push_back(std::move(novo));
        break;
    }
    case IDENTIDADE:
    {
        auto novo = std::make_unique<identidade>();
        novo->setNome(ui->line_nome_item_identidade->text());
        novo->setNomeChars(ui->line_name_identidade_2->text());
        novo->setCPF(ui->line_cpf_identidade->text());
        novo->setRG(ui->line_rg_identidade->text());
        novo->setCNH(ui->line_cnh_identidade->text());
        itens::todos.push_back(std::move(novo));
        break;
    }
    case WIFI:
    {
        auto novo = std::make_unique<wifi>();
        novo->setNome(ui->line_nome_item_wifi->text());
        novo->setRedeSsid(ui->line_rede_ssid_wifi->text());
        novo->setSenha(ui->line_passowrd_wifi->text());
        novo->setTipo(ui->line_type_wifi->text());
        itens::todos.push_back(std::move(novo));
        break;
    }
    case FILE_PAGE:
    {
        auto novo = std::make_unique<arquivo>();
        novo->setNome(ui->line_nome_item_file->text());
        novo->setNotas(ui->textEdit_files->toPlainText());
        itens::todos.push_back(std::move(novo));
        break;
    }
    }
}

windowItem::~windowItem()
{
    delete ui;
}

