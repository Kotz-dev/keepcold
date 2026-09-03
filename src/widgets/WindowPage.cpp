//
// Created by KoTz on 21/07/2026.
//

#include "../include/widgets/WindowPage.h"
#include "../include/styles/UIStyle.h"
#include <io/FileManager.h>

Ui::mainwindow *WindowPage::ui_mainwindow = nullptr;
QWidget *WindowPage::parent = nullptr;

Ui::mainwindow* WindowPage::getMainWindow()
{
    return ui_mainwindow;
}

QWidget* WindowPage::getParent()
{
    return parent;
}

void WindowPage::__init__(Ui::mainwindow* ui,QWidget *ptn)
{
    if (ui != nullptr && ptn != nullptr)
    {
       ui_mainwindow = ui;
       parent = ptn;
        ui->CreateVault_label_erro_senha->hide();
        NavigetPage(StackPage::Welcome);
        ui->frame_barra_titulo->setStyleSheet(
            FileManager::loadStyleSheet(
                "keepcold\\resources\\Styles\\mainwindow\\dark\\barra_titule.qss", PATCH_TYPE_::FILE_styles));
    }
}

void WindowPage::NavigetPage(StackPage page)
{
    if (ui_mainwindow != nullptr && parent != nullptr)
    {
        ui_mainwindow->stackedWidget->setCurrentIndex(static_cast<int>(page));

        switch (page)
        {
        case StackPage::Welcome:
            UIStyle::Styles_Page::WELCOME::apply();
            break;
        case StackPage::CreateVault:
            UIStyle::Styles_Page::CREATE_NEW_COFRE::apply();
            break;
        case StackPage::OpenVault:
            UIStyle::Styles_Page::OPEN_COFRE::apply();
            break;
        case StackPage::VaultMain:
            UIStyle::Styles_Page::VALUE_MAIN::apply();
            break;
        }
    }
}