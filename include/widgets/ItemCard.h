//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_ITEMCARD_H
#define KEEPCOLD_ITEMCARD_H

#include <QFrame>

#include "item/Item.h"

class QLabel;

class ItemCard : public QFrame
{
    Q_OBJECT
public :
    explicit ItemCard(const Item &item, QWidget *parent = nullptr);

    QString getItemId() const { return itemId; }

private :
    QString itemId;
    QLabel *icone;
    QLabel *titulo;
    QLabel *subtitulo;
};

#endif  // KEEPCOLD_ITEMCARD_H
