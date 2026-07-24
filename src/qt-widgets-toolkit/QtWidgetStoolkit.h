//
// Created by KoTz on 23/07/2026.
//

#ifndef KEEPCOLD_QTWIDGETSTOOLKIT_H
#define KEEPCOLD_QTWIDGETSTOOLKIT_H

#include <QFrame>
#include <QLayout>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QSplitter>
#include <QString>
#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTextEdit>
#include <QSizeGrip>
#include <QMouseEvent>
#include <QEvent>




namespace QtToolkitAnimation
{

    // Anima a entrada de widget: desliza de baixo pra cima e faz fade-in de opacidade.
    void fadeSlideIn(QWidget* widget);
}

    namespace QtToolkit
    {

    namespace ProgessBar
    {
    class SegmentedProgressBar : public QProgressBar
    {
        Q_OBJECT
        Q_PROPERTY(QColor animatedColor READ animatedColor WRITE setAnimatedColor)

    public:
        explicit SegmentedProgressBar(QWidget* parent = nullptr);
        ~SegmentedProgressBar();
        void setSegments(int count);

        QColor animatedColor() const
        {
            return m_animatedColor;
        }

        void setAnimatedColor(const QColor& color);

        static void render(int value, QWidget* ProgressBar);

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        int m_segments = 5;
        QColor m_animatedColor;
        QPropertyAnimation* m_colorAnimation;

        static SegmentedProgressBar* s_instance;

        QColor colorForLevel(int filledCount) const;
        void onValueChanged(int value);
    };
    }  // namespace ProgessBar


    namespace Splitter
    {
    // Remove firstChild e secondChild do layout de parent e os recoloca lado a lado dentro de um QSplitter.
    void setupSplitter(
        QWidget* parent,
        QWidget* firstChild,
        QWidget* secondChild,
        QFrame::Shape shape = QFrame::NoFrame,
        QString styleSheet = "");
    }

    }  // namespace QtToolkit
#endif  // KEEPCOLD_QTWIDGETSTOOLKIT_H
