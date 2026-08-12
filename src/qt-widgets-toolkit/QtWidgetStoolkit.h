//
// Created by KoTz on 23/07/2026.
//

#ifndef KEEPCOLD_QTWIDGETSTOOLKIT_H
#define KEEPCOLD_QTWIDGETSTOOLKIT_H

#include <QEvent>
#include <QFrame>
#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QLabel>
#include <QLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QSplitter>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <QScreen>
#include <QObject>
#include <qwindow.h>

namespace QtToolkit
{

namespace Frame {

class ClickHelper : public QObject {
public:
    ClickHelper(QFrame *target, std::function<void()> callback)
        : QObject(target), m_callback(callback) {
        target->installEventFilter(this);
        m_enabled = true;
    }
    static void setEnabled(bool enable) {
        m_enabled = enable;
    }
protected:
    bool eventFilter(QObject *watched, QEvent *event) override {
        if (!m_enabled) {
            return false;
        }
        if (event->type() == QEvent::MouseButtonPress) {
            if (m_callback) {
                m_callback();
            }
            return true;
        }
        return QObject::eventFilter(watched, event);

    }
private:

    static bool m_enabled;
    std::function<void()> m_callback;
};

void makeClickable(QFrame* frame, std::function<void()> onClick);

}



namespace Signal
{
    template <typename T>
    T* getObjet(QObject* get = QObject::sender())
    {
        if (get != nullptr)
        return qobject_cast<T*>(get);
    }
}

namespace Animation
{
void fadeSlideIn(QWidget* widget,int OpDuration = 750,int posDuration = 740);
}

namespace Window
{
class Maximizer : public QWidget
{
private:
    static bool m_isMaximized;
    static QRect m_normalGeometry;

public :
    static QScreen* oldScreen;
    static QWidget* oldWidget;

public:
    void toggle(QWidget* widget, int msec = 500);
    static void resync(QWidget* widget);
};

class Dragger : public QObject
{
    bool m_dragging = false;
    QPoint m_dragStartPosition;
    static QWidget* s_target;
    static Dragger* s_instance;

private:
    bool eventFilter(QObject* watched, QEvent* event) override;

public:
    static void attach(QWidget* widget);
};
}  // namespace Window

namespace Blur
{
QLabel* render(QWidget* parent, qreal blurRadius = 3);
}

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
// Remove firstChild e secondChild do layout de parent e os recoloca lado a lado dentro de um
// QSplitter.
void setupSplitter(
    QWidget* parent,
    QWidget* firstChild,
    QWidget* secondChild,
    QFrame::Shape shape = QFrame::NoFrame,
    QString styleSheet = "");
}  // namespace Splitter

}  // namespace QtToolkit
#endif  // KEEPCOLD_QTWIDGETSTOOLKIT_H
