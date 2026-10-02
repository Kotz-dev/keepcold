//
// Created by KoTz on 23/09/2026.
//

#include "item/identidade.h"

QString identidade::toString() const
{
    return Item::toString()
         + " nome_chars=" + nome_chars_
         + " CPF=" + CPF
         + " RG=" + RG
         + " CNH=" + CNH;
}

nlohmann::json identidade::toJson() const
{
    auto j = Item::toJson();
    j["nome_chars"] = nome_chars_.toStdString();
    j["CPF"]        = CPF.toStdString();
    j["RG"]         = RG.toStdString();
    j["CNH"]        = CNH.toStdString();
    return j;
}

// Getters
QString identidade::getNomeChars() const { return nome_chars_; }
QString identidade::getCPF() const       { return CPF; }
QString identidade::getRG() const        { return RG; }
QString identidade::getCNH() const       { return CNH; }

// Setters
void identidade::setNomeChars(const QString &value) { nome_chars_ = value; }
void identidade::setCPF(const QString &value)       { CPF = value; }
void identidade::setRG(const QString &value)        { RG = value; }
void identidade::setCNH(const QString &value)       { CNH = value; }
