//
// Created by KoTz on 23/09/2026.
//

#include "item/cartao.h"

QString cartao::toString() const
{
    return Item::toString()
         + " titular=" + titular
         + " numero=" + numero
         + " validade=" + validade
         + " Cvv=" + Cvv
         + " bandeira=" + bandeira;
}

nlohmann::json cartao::toJson() const
{
    auto j = Item::toJson();
    j["titular"]  = titular.toStdString();
    j["numero"]   = numero.toStdString();
    j["validade"] = validade.toStdString();
    j["Cvv"]      = Cvv.toStdString();
    j["bandeira"] = bandeira.toStdString();
    return j;
}

// Getters
QString cartao::getTitular() const  { return titular; }
QString cartao::getNumero() const   { return numero; }
QString cartao::getValidade() const { return validade; }
QString cartao::getCvv() const      { return Cvv; }
QString cartao::getBandeira() const { return bandeira; }

// Setters
void cartao::setTitular(const QString &value)  { titular = value; }
void cartao::setNumero(const QString &value)   { numero = value; }
void cartao::setValidade(const QString &value) { validade = value; }
void cartao::setCvv(const QString &value)      { Cvv = value; }
void cartao::setBandeira(const QString &value) { bandeira = value; }
