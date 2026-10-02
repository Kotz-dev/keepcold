//
// Created by KoTz on 23/09/2026.
//

#include "item/key.h"

QString key::toString() const
{
    return Item::toString()
         + " servico=" + servico
         + " chave=" + chave
         + " note=" + note;
}

nlohmann::json key::toJson() const
{
    auto j = Item::toJson();
    j["servico"] = servico.toStdString();
    j["chave"]   = chave.toStdString();
    j["note"]    = note.toStdString();
    return j;
}

// Getters
QString key::getServico() const { return servico; }
QString key::getChave() const   { return chave; }
QString key::getNote() const    { return note; }

// Setters
void key::setServico(const QString &value) { servico = value; }
void key::setChave(const QString &value)   { chave = value; }
void key::setNote(const QString &value)    { note = value; }
