//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_WIFI_H
#define KEEPCOLD_WIFI_H
#include "item/Item.h"

class wifi : public Item
{
     QString rede_ssid;
     QString senha;
     QString tipo;
public :
    using Item::Item;
    QString categoria() const override { return "wifi"; }
    QString toString() const override;
    nlohmann::json toJson() const override;
    QString subtitulo() const override { return tipo; }

    // Getters
    QString getRedeSsid() const;
    QString getSenha() const;
    QString getTipo() const;

    // Setters
    void setRedeSsid(const QString &value);
    void setSenha(const QString &value);
    void setTipo(const QString &value);
};

#endif  // KEEPCOLD_WIFI_H
