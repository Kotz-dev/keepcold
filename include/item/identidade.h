//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_IDENTIDADE_H
#define KEEPCOLD_IDENTIDADE_H

#include "item/Item.h"

class identidade : public Item
{
private :
    QString nome_chars_;
    QString CPF;
    QString RG;
    QString CNH;
public :
    using Item::Item;
    QString categoria() const override { return "identidade"; }
    QString toString() const override;
    nlohmann::json toJson() const override;

    // Getters
    QString getNomeChars() const;
    QString getCPF() const;
    QString getRG() const;
    QString getCNH() const;

    // Setters
    void setNomeChars(const QString &value);
    void setCPF(const QString &value);
    void setRG(const QString &value);
    void setCNH(const QString &value);
};

#endif  // KEEPCOLD_IDENTIDADE_H
