//
// Created by KoTz on 23/09/2026.
//

#include "item/Item.h"

#include <QUuid>

Item::Item()
    : id(QUuid::createUuid().toString(QUuid::WithoutBraces))
{
}

Item::Item(const QString &id)
    : id(id)
{
}

// Getters
QString Item::getId() const   { return id; }
QString Item::getNome() const { return nome; }

// Setters
void Item::setNome(const QString &value) { nome = value; }

QString Item::toString() const
{
    return "[" + categoria() + "] id=" + id + " nome=" + nome;
}

nlohmann::json Item::toJson() const
{
    return {
        {"id",        id.toStdString()},
        {"nome",      nome.toStdString()},
        {"categoria", categoria().toStdString()}
    };
}
