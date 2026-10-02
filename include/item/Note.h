//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_NOTE_H
#define KEEPCOLD_NOTE_H


#include "item/Item.h"

class Note : public Item
{
private :
    QString conteudo;
public:
    using Item::Item;
    QString categoria() const override { return "note"; }
    QString toString() const override;
    nlohmann::json toJson() const override;

    // Getters
    QString getConteudo() const;

    // Setters
    void setConteudo(const QString &value);
};

#endif  // KEEPCOLD_NOTE_H
