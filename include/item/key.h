//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_KEY_H
#define KEEPCOLD_KEY_H

#include "item/Item.h"

class key : public Item
{
private :
    QString servico;
    QString chave;
    QString note;

public :
    using Item::Item;
    QString categoria() const override { return "key"; }
    QString toString() const override;
    nlohmann::json toJson() const override;

    // Getters
    QString getServico() const;
    QString getChave() const;
    QString getNote() const;

    // Setters
    void setServico(const QString &value);
    void setChave(const QString &value);
    void setNote(const QString &value);
};

#endif  // KEEPCOLD_KEY_H
