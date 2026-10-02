//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_ITEM_H
#define KEEPCOLD_ITEM_H

#include <QString>
#include <nlohmann/json.hpp>

class Item
{
public :
    Item();                            // item novo: gera id
    explicit Item(const QString &id);  // item carregado: usa id salvo
    virtual ~Item() = default;

    // Getters
    QString getId() const;
    QString getNome() const;

    // Setters
    void setNome(const QString &value);

    virtual QString categoria() const = 0;
    virtual QString toString() const;
    virtual nlohmann::json toJson() const;
    virtual QString subtitulo() const { return {}; }

private :
    QString id;
    QString nome;
};

#endif  // KEEPCOLD_ITEM_H
