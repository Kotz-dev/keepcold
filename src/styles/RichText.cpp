//
// Created by KoTz on 17/07/2026.
//

#include "styles/RichText.h"

QString RichText::cardDescription(const QString &title, const QString &subtitle) {
    return "<div style='color:#e8eaf0; font-size:15px; font-weight:bold;'>" + title + "</div>"
           "<div style='color:#7b839e; font-size:12px; margin-top:6px;'>" + subtitle + "</div>";
}