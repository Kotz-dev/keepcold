//
// Created by KoTz on 23/09/2026.
//

#include "item/logins.h"


QString logins::toString() const
{
    return Item::toString()
         + " email=" + email
         + " password=" + password
         + " 2fa=" + _2fa_
         + " URL=" + URL
         + " codigo_recuperacao=" + codigo_recuperacao;
}

nlohmann::json logins::toJson() const
{
    auto j = Item::toJson();
    j["email"]              = email.toStdString();
    j["password"]           = password.toStdString();
    j["2fa"]                = _2fa_.toStdString();
    j["URL"]                = URL.toStdString();
    j["codigo_recuperacao"] = codigo_recuperacao.toStdString();
    return j;
}

// Getters
QString logins::getEmail() const             { return email; }
QString logins::getPassword() const          { return password; }
QString logins::get2fa() const               { return _2fa_; }
QString logins::getURL() const               { return URL; }
QString logins::getCodigoRecuperacao() const { return codigo_recuperacao; }

// Setters
void logins::setEmail(const QString &value)             { email = value; }
void logins::setPassword(const QString &value)          { password = value; }
void logins::set2fa(const QString &value)               { _2fa_ = value; }
void logins::setURL(const QString &value)               { URL = value; }
void logins::setCodigoRecuperacao(const QString &value) { codigo_recuperacao = value; }
