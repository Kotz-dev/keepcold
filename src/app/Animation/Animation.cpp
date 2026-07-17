//
// Created by KoTz on 15/07/2026.
//

#include "app/Animation/Animation.h"

void animateIn(QWidget *widget) {
    QPoint endPos = widget->pos();
    widget->move(endPos.x(), endPos.y() + 20);

    auto *effect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(effect);

    QEasingCurve customCurve(QEasingCurve::BezierSpline);
    customCurve.addCubicBezierSegment(
        QPointF(0.34, -0.04),
        QPointF(0.49, 0.93),
        QPointF(1.0, 1.0)
    );

    auto *fade = new QPropertyAnimation(effect, "opacity");
    fade->setDuration(750);
    fade->setStartValue(0.0);
    fade->setEndValue(1.0);
    fade->setEasingCurve(customCurve);

    auto *slide = new QPropertyAnimation(widget, "pos");
    slide->setDuration(740);
    slide->setEndValue(endPos);
    slide->setEasingCurve(customCurve);

    auto *group = new QParallelAnimationGroup(widget);
    group->addAnimation(fade);
    group->addAnimation(slide);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}