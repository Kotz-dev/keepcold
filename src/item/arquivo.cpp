//
// Created by KoTz on 23/09/2026.
//

#include "item/arquivo.h"

QString arquivo::toString() const
{
    return Item::toString()
         + " url_file=" + url_file
         + " notas=" + notas;
}

nlohmann::json arquivo::toJson() const
{
    auto j = Item::toJson();
    j["url_file"] = url_file.toStdString();
    j["notas"]    = notas.toStdString();
    return j;
}

// Getters
QString arquivo::getUrlFile() const { return url_file; }
QString arquivo::getNotas() const   { return notas; }

// Setters
void arquivo::setUrlFile(const QString &value) { url_file = value; }
void arquivo::setNotas(const QString &value)   { notas = value; }
