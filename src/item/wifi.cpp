//
// Created by KoTz on 23/09/2026.
//

#include "item/wifi.h"

QString wifi::toString() const
{
    return Item::toString()
         + " rede_ssid=" + rede_ssid
         + " senha=" + senha
         + " tipo=" + tipo;
}

nlohmann::json wifi::toJson() const
{
    auto j = Item::toJson();
    j["rede_ssid"] = rede_ssid.toStdString();
    j["senha"]     = senha.toStdString();
    j["tipo"]      = tipo.toStdString();
    return j;
}

// Getters
QString wifi::getRedeSsid() const { return rede_ssid; }
QString wifi::getSenha() const    { return senha; }
QString wifi::getTipo() const     { return tipo; }

// Setters
void wifi::setRedeSsid(const QString &value) { rede_ssid = value; }
void wifi::setSenha(const QString &value)    { senha = value; }
void wifi::setTipo(const QString &value)     { tipo = value; }
