//
// Created by KoTz on 17/07/2026.
//

#include "core/PasswordStrength.h"
#include <QDebug>

QString PasswordStrength::Password;

int PasswordStrength::evaluate(QString & text) {
    if (text.isEmpty())
    {
        return 0;
    }
    Password = text;
    auto value = ZxcvbnMatch(text.toStdString().c_str(), nullptr, nullptr);
    if (value < 20) {text = "Muito fraca"; return 1;}
    if (value < 36) {text = "Fraca"; return 2;}
    if (value < 60) {text = "Boa"; return 3;}
    if (value < 80) {text = "Forte"; return 4;}
    text = "Excelente";
    return 5;

}

bool PasswordStrength::PassowrdIguais(QString text) {
    if (text.toStdString().find(Password.toStdString()) != std::string::npos &&
        Password.isEmpty() == false)
    {
        return true;
    }
   return false;
}