//
// Created by KoTz on 21/07/2026.
//

#include "../include/styles/LinePassword.h"

void LinePassword::setupPasswordVisibilityToggle()
{
    auto Toggle  = this->toggle;
    auto LineEdit = this->lineEdit;

    if (LineEdit != nullptr && Toggle != nullptr)
    {
        LineEdit->clear();
        Toggle->setIcon(QIcon(":/images/16x16/pwoff.png"));
        Toggle->setCheckable(true);
        LineEdit->addAction(Toggle, QLineEdit::TrailingPosition);

        QObject::connect(
            Toggle,
            &QAction::toggled,
            LineEdit,
            [LineEdit, Toggle](bool checked)
            {
                LineEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
                Toggle->setIcon(
                    QIcon(checked ? ":/images/16x16/pw.png" : ":/images/16x16/pwoff.png"));
            });
    }
}

LinePassword::LinePassword(QLineEdit *lineEdit):lineEdit(lineEdit)
{
    this->toggle = new QAction(lineEdit);
}

LinePassword::~LinePassword()
{
    delete toggle;
}

QAction* LinePassword::getToggle()
{
    return this->toggle;
}