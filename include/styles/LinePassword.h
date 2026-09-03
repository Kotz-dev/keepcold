//
// Created by KoTz on 21/07/2026.
//

#ifndef KEEPCOLD_LINEPASSWORD_H
#define KEEPCOLD_LINEPASSWORD_H

#include <QLineEdit>
#include <QAction>




class LinePassword
{
public :
    QAction *toggle;
    QLineEdit *lineEdit;
public :
    LinePassword(QLineEdit *lineEdit);
    ~LinePassword();
    void setupPasswordVisibilityToggle();
    QAction *getToggle();
};

#endif  // KEEPCOLD_LINEPASSWORD_H
