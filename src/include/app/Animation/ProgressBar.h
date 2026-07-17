//
// Created by KoTz on 17/07/2026.
//

#ifndef KEEPCOLD_PROGRESSBAR_H
#define KEEPCOLD_PROGRESSBAR_H

#include <QProgressBar>
#include <QPainter>
#include <QStringList>

class SegmentedProgressBar : public QProgressBar {
public:
    using QProgressBar::QProgressBar;

    void setSegments(int count) { m_segments = count; update(); }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int spacing = 4;
        int totalSpacing = spacing * (m_segments - 1);
        int segmentWidth = (width() - totalSpacing) / m_segments;

        int filledCount = m_segments > 0
            ? (value() * m_segments) / qMax(1, maximum())
            : 0;

        // AGORA: uma cor só, baseada no nível atual - todos os
        // segmentos preenchidos usam essa MESMA cor
        QColor filledColor = colorForLevel(filledCount);

        for (int i = 0; i < m_segments; i++) {
            int x = i * (segmentWidth + spacing);
            QRect rect(x, 0, segmentWidth, height());

            QColor color = (i < filledCount) ? filledColor : QColor("#3a4368");

            painter.setBrush(color);
            painter.setPen(Qt::NoPen);
            painter.drawRoundedRect(rect, 2, 2);
        }
    }

private:
    int m_segments = 5;

    // Cor baseada no NÍVEL GERAL (quantos segmentos preenchidos), não na posição
    QColor colorForLevel(int filledCount) const {
        switch (filledCount) {
            case 0: return QColor("#3a4368");
            case 1: return QColor("#ef4444");
            case 2: return QColor("#f97316");
            case 3: return QColor("#3b82f6");
            case 4: return QColor("#22c55e");
            case 5: return QColor("#22c55e");
            default: return QColor("#22c55e");
        }
    }
};


#endif // KEEPCOLD_PROGRESSBAR_H
