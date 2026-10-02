//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_CARTAO_H
#define KEEPCOLD_CARTAO_H

#include "item/Item.h"

class cartao : public Item
{
    QString titular;
    QString numero;
    QString validade;
    QString Cvv;
    QString bandeira;
public :
    using Item::Item;
    QString categoria() const override { return "cartao"; }
    QString toString() const override;
    nlohmann::json toJson() const override;
    QString subtitulo() const override { return "•••• " + numero.right(4); }

    // Getters
    QString getTitular() const;
    QString getNumero() const;
    QString getValidade() const;
    QString getCvv() const;
    QString getBandeira() const;

    // Setters
    void setTitular(const QString &value);
    void setNumero(const QString &value);
    void setValidade(const QString &value);
    void setCvv(const QString &value);
    void setBandeira(const QString &value);
};

#endif  // KEEPCOLD_CARTAO_H
