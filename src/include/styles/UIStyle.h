//
// Created by KoTz on 15/07/2026.
//

#ifndef KEEPCOLD_STYLE_MAINWINDOW_H
#define KEEPCOLD_STYLE_MAINWINDOW_H

#include <QPushButton>
#include <ui_mainwindow.h>
#include <QAction>

namespace Ui {
    class mainwindow;
}

enum ModeStyle {
    DARK = 0,
    LIGHT = 1
};

namespace UIStyle {

    class CardButton {
    public:
        static void apply(QPushButton *button, const QString &title);
    };

    namespace Page
    {
        class Welcome {
            public :
             static void show(Ui::mainwindow *mainwindow,QWidget *parent,QString fileName = "page_welcome.qss");
        };

        class PasswordField {
            public :
             static inline QAction *obj;
             static void show(QLineEdit *lineEdit,QWidget *parent,QString fileName);
        };
    }
}



template<typename T>
void DeleteMemory(T *object) {
    if (object != nullptr) {
        delete object;
    }
}
#endif // KEEPCOLD_STYLE_MAINWINDOW_H
