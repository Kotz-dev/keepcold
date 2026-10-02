//
// Created by KoTz on 23/09/2026.
//

#include "item/Note.h"

QString Note::toString() const
{
    return Item::toString()
         + " conteudo=" + conteudo;
}

nlohmann::json Note::toJson() const
{
    auto j = Item::toJson();
    j["conteudo"] = conteudo.toStdString();
    return j;
}

// Getters
QString Note::getConteudo() const { return conteudo; }

// Setters
void Note::setConteudo(const QString &value) { conteudo = value; }
