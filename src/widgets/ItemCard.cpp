//
// Created by KoTz on 23/09/2026.
//

#include "widgets/ItemCard.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

static QString iconePorCategoria(const QString &categoria)
{
    if (categoria == "logins")      return ":/images/36x36/logo_login_badge.png";
    if (categoria == "note")        return ":/images/36x36/logo_documento_badge.png";
    if (categoria == "key")         return ":/images/36x36/logo_terminal_badge.png";
    if (categoria == "cartao")      return ":/images/36x36/logo_cartao_badge.png";
    if (categoria == "identidade")  return ":/images/36x36/logo_idadente_badge.png";
    if (categoria == "wifi")        return ":/images/36x36/logo_wifi_badge.png";
    if (categoria == "recuperacao") return ":/images/36x36/logo_recuperacao_badge.png";
    return ":/images/36x36/logo_file_badge.png";
}

ItemCard::ItemCard(const Item &item, QWidget *parent)
    : QFrame(parent),
      itemId(item.getId())
{
    setObjectName("itemCard");

    icone = new QLabel(this);
    icone->setPixmap(QPixmap(iconePorCategoria(item.categoria()))
                         .scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    icone->setFixedSize(40, 40);

    titulo = new QLabel(item.getNome(), this);
    titulo->setObjectName("itemCardTitulo");

    subtitulo = new QLabel(item.subtitulo(), this);
    subtitulo->setObjectName("itemCardSubtitulo");

    auto *textos = new QVBoxLayout();
    textos->setSpacing(2);
    textos->addWidget(titulo);
    textos->addWidget(subtitulo);

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(12, 8, 12, 8);
    layout->setSpacing(12);
    layout->addWidget(icone);
    layout->addLayout(textos, 1);
}
