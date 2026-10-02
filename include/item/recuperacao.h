//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_RECUPERACAO_H
#define KEEPCOLD_RECUPERACAO_H

#include "item/Item.h"

#include <QStringList>

class recuperacao : public Item
{
private :
     QString codigos;
public :
    using Item::Item;
    QString categoria() const override { return "recuperacao"; }
    QString toString() const override;
    nlohmann::json toJson() const override;
    QString subtitulo() const override
    {
        return QString::number(codigos.split('\n', Qt::SkipEmptyParts).size()) + " códigos";
    }

    // Getters
    QString getCodigos() const;

    // Setters
    void setCodigos(const QString &value);
};

#endif  // KEEPCOLD_RECUPERACAO_H
