//
// Created by KoTz on 30/07/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_windowItem.h" resolved

#include "../../../../include/app/keepcold/mainwindow/windowitem.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <vector>

#include "src/qt-widgets-toolkit/QtWidgetStoolkit.h"
#include "ui_windowItem.h"

#include <io/FileManager.h>
#include <QLineEdit>

#include <QFileDialog>


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

        connect(group.obj.lineName, &QLineEdit::textChanged, this, &windowItem::teste);
    }

}

void windowItem::teste()
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

void windowItem::getfile(QUrl file)
{
    if (file.isEmpty() == false)
    {
        ui->file_name_label->setText(file.fileName());
        ui->file_memory_label->setText(FileManager::SizeMemory(file));
    }
}
void windowItem::on_btn_download_file_clicked()
{
    ///qDebug () << QFileDialog::getSaveFileUrl(this,"teste",QUrl("/home/kotz/Área de trabalho/data.vx"));
}

void windowItem::btn_upload_clicked()
{
    QtToolkit::Frame::makeClickable(ui->btn_file_upload, [this]() {
        auto file =  QFileDialog::getOpenFileUrl(this, tr("Selecionar arquivo"), QUrl(), tr("Todos os arquivos (*)"));
          getfile(file);

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

windowItem::~windowItem()
{
    delete ui;
}

