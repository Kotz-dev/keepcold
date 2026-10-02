//
// Created by KoTz on 23/09/2026.
//

#include "item/recuperacao.h"

QString recuperacao::toString() const
{
    return Item::toString()
         + " codigos=" + codigos;
}

nlohmann::json recuperacao::toJson() const
{
    auto j = Item::toJson();
    j["codigos"] = codigos.toStdString();
    return j;
}

// Getters
QString recuperacao::getCodigos() const { return codigos; }

// Setters
void recuperacao::setCodigos(const QString &value) { codigos = value; }
