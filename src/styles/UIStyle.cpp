//
// Created by KoTz on 15/07/2026.
//

#include "styles/UIStyle.h"

#include <QDir>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QSizeGrip>
#include <QStyle>
#include <QVBoxLayout>
#include <QWidget>

#include <io/FileManager.h>
#include <memory/Memory.h>
#include <QtWidgetStoolkit/QtWidgetStoolkit.h>
#include <styles/RichText.h>
#include <widgets/WindowPage.h>

void UIStyle::CardButton::apply(QPushButton* button, const QString& title)
{
    if (button == nullptr || button->layout() != nullptr)
    {
        return;
    }
    QLabel* content = new QLabel(button);
    content->setText(title);

    content->setWordWrap(true);

    content->setAttribute(Qt::WA_TransparentForMouseEvents);

    QVBoxLayout* layout = new QVBoxLayout(button);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(12);
    layout->setAlignment(Qt::AlignTop);

    QLabel* icon = new QLabel(button);
    icon->setFixedSize(36, 36);

    content->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    layout->addWidget(icon);
    layout->addWidget(content);
}
void UIStyle::Styles_Page::WELCOME::apply(QString fileName) {
    if (WindowPage::getParent() == nullptr && WindowPage::getMainWindow() == nullptr) {
        return;
    }
    auto mainwindow =      WindowPage::getMainWindow();
    auto parent = WindowPage::getParent();

    QString text = "";
    text = RichText::cardDescription(
        "Criar novo cofre", "Defina uma senha mestra e escolha onde salvar seu arquivo.");
    UIStyle::CardButton::apply(mainwindow->btn_create_cofre, text);
    text = RichText::cardDescription(
        "Abrir cofre existente", "Selecione um arquivo\t\t .vault e digite a senha.");
    UIStyle::CardButton::apply(mainwindow->btn_open_cofre, text);

    parent->setStyleSheet(
        FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\" + fileName.toStdString(),
            PATCH_TYPE_::FILE_styles));

    QtToolkit::Animation::fadeSlideIn(mainwindow->pageWelcome);

}

void UIStyle::Styles_Page::CREATE_NEW_COFRE::apply()
{
    safeDelete(Pw);

    auto mainwindow = WindowPage::getMainWindow();
    auto parent = WindowPage::getParent();

    Pw = new LinePassword(mainwindow->line_password_mestra);

   auto style = FileManager::loadStyleSheet(
         "keepcold\\resources\\Styles\\mainwindow\\dark\\page_create_new_cofre.qss", PATCH_TYPE_::FILE_styles)
       + FileManager::loadStyleSheet(
         "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\cofre_form.qss", PATCH_TYPE_::FILE_styles)
       + FileManager::loadStyleSheet(
         "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\back_button.qss", PATCH_TYPE_::FILE_styles)
       + FileManager::loadStyleSheet(
         "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\cta_button.qss", PATCH_TYPE_::FILE_styles);

     Pw->setupPasswordVisibilityToggle();
     parent->setStyleSheet(style);
     QtToolkit::Animation::fadeSlideIn(mainwindow->frame_8);
}

void UIStyle::Styles_Page::OPEN_COFRE::apply()
{
    safeDelete(Pw);

    auto mainwindow = WindowPage::getMainWindow();
    auto parent = WindowPage::getParent();

    Pw = new LinePassword(mainwindow->line_passowrd_open_cofre);
    Pw->setupPasswordVisibilityToggle();

    parent->setStyleSheet(
        FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\page_open_exist_cofre.qss",
            PATCH_TYPE_::FILE_styles)
        + FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\cofre_form.qss",
            PATCH_TYPE_::FILE_styles)
        + FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\back_button.qss",
            PATCH_TYPE_::FILE_styles)
        + FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\cta_button.qss",
            PATCH_TYPE_::FILE_styles));

    QtToolkit::Animation::fadeSlideIn(mainwindow->frame_13);
}

void applyItemStyles(Ui_mainwindow *mainwindow);
void applyItemStyles(Ui_mainwindow *mainwindow)
{
    if (mainwindow != nullptr)
    {
        std::map<QWidget*, QString> styles =
        {
            {mainwindow->logins,     "keepcold\\resources\\Styles\\mainwindow\\dark\\itens\\login.qss"},
            {mainwindow->notas,      "keepcold\\resources\\Styles\\mainwindow\\dark\\itens\\notas.qss"},
            {mainwindow->Wifi,       "keepcold\\resources\\Styles\\mainwindow\\dark\\itens\\wifi.qss"},
            {mainwindow->chaves,     "keepcold\\resources\\Styles\\mainwindow\\dark\\itens\\chaves.qss"},
            {mainwindow->recuperacao,"keepcold\\resources\\Styles\\mainwindow\\dark\\itens\\recuperacao.qss"},
            {mainwindow->identidade, "keepcold\\resources\\Styles\\mainwindow\\dark\\itens\\idadente.qss"},
            {mainwindow->cartoes,    "keepcold\\resources\\Styles\\mainwindow\\dark\\itens\\cartao.qss"}
        };

        QString favoritoStyle = FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\favorito.qss", PATCH_TYPE_::FILE_styles);
        QString removerStyle = FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\remover.qss", PATCH_TYPE_::FILE_styles);
        QString copyTextStyle = FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\copy_text.qss", PATCH_TYPE_::FILE_styles);
        QString togglePasswordStyle = FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\toggle_password.qss", PATCH_TYPE_::FILE_styles);

        for (auto style : styles)
        {
            if (style.first != nullptr)
            {
                style.first->setStyleSheet(
                    FileManager::loadStyleSheet(style.second.toStdString(), PATCH_TYPE_::FILE_styles)
                    + favoritoStyle + removerStyle + copyTextStyle + togglePasswordStyle);
            }
        }
    }
}

void UIStyle::Styles_Page::VALUE_MAIN::apply()
{
    auto mainwindow = WindowPage::getMainWindow();
    auto parent = WindowPage::getParent();

    mainwindow->stackedWidget_2->setStyleSheet(
        FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\page_value_main\\stackwidget.qss",
            PATCH_TYPE_::FILE_styles)
        + FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\shared\\cofre_form.qss",
            PATCH_TYPE_::FILE_styles));

    parent->setStyleSheet(
        FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\page_value_main.qss",
            PATCH_TYPE_::FILE_styles)
        + FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\page_value_main\\categoria.qss",
            PATCH_TYPE_::FILE_styles)
        + FileManager::loadStyleSheet(
            "keepcold\\resources\\Styles\\mainwindow\\dark\\page_value_main\\line_search.qss",
            PATCH_TYPE_::FILE_styles));


      applyItemStyles(mainwindow);

    QtToolkit::Animation::fadeSlideIn(mainwindow->pageVaultMain);
    QtToolkit::ProgessBar::SegmentedProgressBar::render(4,mainwindow->progressBar_2);
}