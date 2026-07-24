//
// Created by KoTz on 15/07/2026.
//

#ifndef KEEPCOLD_STYLE_MAINWINDOW_H
#define KEEPCOLD_STYLE_MAINWINDOW_H

#include <QAction>
#include <QPushButton>

#include "UIStyle.h"
#include "src/core/PasswordStrength.h"

#include <styles/LinePassword.h>
#include <ui_mainwindow.h>

namespace Ui {
    class mainwindow;
}

namespace UIStyle {

    class CardButton {
    public:
        static void apply(QPushButton *button, const QString &title);
    };

    namespace Styles_Page
    {
        class WELCOME {
            public :
            static void apply(QString fileName = "page_welcome.qss");
        };

       class CREATE_NEW_COFRE
       {
          static inline LinePassword *Pw;

       public :
           static void apply();
       };

        class OPEN_COFRE {
        private :
            static inline LinePassword *Pw;
        public :
        static void apply();
        };

        class VALUE_MAIN {
        public :
        static void apply();
        };

    };
}


#endif // KEEPCOLD_STYLE_MAINWINDOW_H
