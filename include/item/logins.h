//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_LOGINS_H
#define KEEPCOLD_LOGINS_H

#include "item/Item.h"

class logins : public Item
{
private :
    QString email;
    QString password;
    QString _2fa_;
    QString URL;
    QString codigo_recuperacao;
public :
    using Item::Item;
    QString categoria() const override { return "logins"; }
    QString toString() const override;
    nlohmann::json toJson() const override;
    QString subtitulo() const override { return email; }

    // Getters
    QString getEmail() const;
    QString getPassword() const;
    QString get2fa() const;
    QString getURL() const;
    QString getCodigoRecuperacao() const;

    // Setters
    void setEmail(const QString &value);
    void setPassword(const QString &value);
    void set2fa(const QString &value);
    void setURL(const QString &value);
    void setCodigoRecuperacao(const QString &value);
};

#endif  // KEEPCOLD_LOGINS_H
