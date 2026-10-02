//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_ARQUIVO_H
#define KEEPCOLD_ARQUIVO_H

#include "item/Item.h"

class arquivo : public Item
{
    QString url_file;
    QString notas;
public :
    using Item::Item;
    QString categoria() const override { return "arquivo"; }
    QString toString() const override;
    nlohmann::json toJson() const override;

    // Getters
    QString getUrlFile() const;
    QString getNotas() const;

    // Setters
    void setUrlFile(const QString &value);
    void setNotas(const QString &value);
};

#endif  // KEEPCOLD_ARQUIVO_H
