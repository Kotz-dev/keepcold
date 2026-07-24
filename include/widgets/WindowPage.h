//
// Created by KoTz on 21/07/2026.
//

#ifndef KEEPCOLD_WINDOWPAGE_H
#define KEEPCOLD_WINDOWPAGE_H

#include <QMainWindow>
#include "ui_mainwindow.h"

enum class StackPage {

    Welcome     = 2,
    CreateVault = 3,
    OpenVault   = 0,
    VaultMain   = 1
};

class WindowPage
{
private:
    static Ui::mainwindow* ui_mainwindow;
    static QWidget* parent;
public:
    static void __init__(Ui::mainwindow* ui, QWidget* parent);
    static void NavigetPage(StackPage page);
    static Ui::mainwindow * getMainWindow();
    static QWidget* getParent();
};

#endif  // KEEPCOLD_WINDOWPAGE_H
