//
// Created by KoTz on 15/07/2026.
//

#include "styles/UIStyle.h"

#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>
#include <QWidget>

#include "app/Animation/Animation.h"

#include <io/FileManger.h>
#include <memory/Memory.h>
#include <styles/RichText.h>
#include <widgets/WindowPage.h>

#include <src/qt-widgets-toolkit/QtWidgetStoolkit.h>

#include <QSizeGrip>




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
        FileManger::loadStyleSheet(
            "keepcold\\resources\\Styles\\dark\\" + fileName.toStdString(),
            PATCH_TYPE_::FILE_styles));

    QtToolkitAnimation::fadeSlideIn(mainwindow->pageWelcome);

}

void UIStyle::Styles_Page::CREATE_NEW_COFRE::apply()
{
    safeDelete(Pw);

    auto mainwindow = WindowPage::getMainWindow();
    auto parent = WindowPage::getParent();

    Pw = new LinePassword(mainwindow->line_password_mestra);

   auto style = FileManger::loadStyleSheet(
         "keepcold\\resources\\Styles\\dark\\page_create_new_cofre.qss", PATCH_TYPE_::FILE_styles);

     Pw->setupPasswordVisibilityToggle();
     parent->setStyleSheet(style);
     QtToolkitAnimation::fadeSlideIn(mainwindow->frame_8);
}

void UIStyle::Styles_Page::OPEN_COFRE::apply()
{
    safeDelete(Pw);

    auto mainwindow = WindowPage::getMainWindow();
    auto parent = WindowPage::getParent();

    Pw = new LinePassword(mainwindow->line_passowrd_open_cofre);
    Pw->setupPasswordVisibilityToggle();

    parent->setStyleSheet(
        FileManger::loadStyleSheet(
            "keepcold\\resources\\Styles\\dark\\page_open_exist_cofre.qss",
            PATCH_TYPE_::FILE_styles));

    QtToolkitAnimation::fadeSlideIn(mainwindow->frame_13);
}

void UIStyle::Styles_Page::VALUE_MAIN::apply()
{
    auto mainwindow = WindowPage::getMainWindow();
    auto parent = WindowPage::getParent();

    mainwindow->stackedWidget_2->setStyleSheet(FileManger::loadStyleSheet(
            "keepcold\\resources\\Styles\\dark\\stackwidget.qss",
            PATCH_TYPE_::FILE_styles));

    parent->setStyleSheet(
        FileManger::loadStyleSheet(
            "keepcold\\resources\\Styles\\dark\\page_value_main.qss",
            PATCH_TYPE_::FILE_styles));



    mainwindow->notas->setStyleSheet(FileManger::loadStyleSheet(
            "keepcold\\resources\\Styles\\dark\\item\\notas.qss",
            PATCH_TYPE_::FILE_styles));


    QtToolkitAnimation::fadeSlideIn(mainwindow->pageVaultMain);
   // QtToolkit::ProgessBar::SegmentedProgressBar(mainwindow->progressBar_2);
}