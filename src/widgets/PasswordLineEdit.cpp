//
// Created by KoTz on 15/07/2026.
//

#include "widgets/PasswordLineEdit.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QStyle>
#include <QObject>

void setupPasswordVisibilityToggle(QLineEdit *lineEdit, QAction *toggleAction) {
    lineEdit->clear();
    toggleAction->setIcon(QIcon(":/imagen/images/pwoff.png"));
    toggleAction->setCheckable(true);
    lineEdit->addAction(toggleAction, QLineEdit::TrailingPosition);

    QObject::connect(toggleAction, &QAction::toggled, lineEdit, [lineEdit, toggleAction](bool checked) {
        lineEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
        toggleAction->setIcon(QIcon(checked ? ":/imagen/images/pw.png" : ":/imagen/images/pwoff.png"));
    });
}