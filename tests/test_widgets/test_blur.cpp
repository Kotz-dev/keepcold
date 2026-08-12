#include <QLabel>
#include <QTest>
#include <QWidget>

#include <src/qt-widgets-toolkit/QtWidgetStoolkit.h>

class TestBlur : public QObject
{
    Q_OBJECT

private slots:
    void nullParent_returnsNull();
    void nonPositiveRadius_returnsNull();
    void validCall_returnsLabelCoveringParent();
    void validCall_pixmapFillsOriginalSizeWithoutShrinking();
    void callerOwnsLabel_deletingItLeavesNoChildBehind();
};

void TestBlur::nullParent_returnsNull()
{
    QCOMPARE(QtToolkit::Blur::render(nullptr, 5.0), nullptr);
}

void TestBlur::nonPositiveRadius_returnsNull()
{
    QWidget widget;
    widget.setFixedSize(100, 100);

    QCOMPARE(QtToolkit::Blur::render(&widget, 0.0), nullptr);
    QCOMPARE(QtToolkit::Blur::render(&widget, -1.0), nullptr);
    QCOMPARE(widget.findChildren<QLabel*>().size(), 0);
}

void TestBlur::validCall_returnsLabelCoveringParent()
{
    QWidget widget;
    widget.setFixedSize(100, 100);

    QLabel* label = QtToolkit::Blur::render(&widget, 5.0);

    QVERIFY(label != nullptr);
    QCOMPARE(label->parentWidget(), &widget);
    QCOMPARE(label->geometry(), widget.rect());
    QVERIFY(label->pixmap().isNull() == false);

    delete label;
}

// Regressao para o bug de resize: QGraphicsBlurEffect cresce o bounding rect do
// item pelo raio do blur, entao sem fixar source/target no scene.render() a
// imagem final saia encolhida (KeepAspectRatio) com bordas transparentes em vez
// de preencher o pixmap do tamanho original.
void TestBlur::validCall_pixmapFillsOriginalSizeWithoutShrinking()
{
    QWidget widget;
    widget.setFixedSize(100, 100);

    QLabel* label = QtToolkit::Blur::render(&widget, 5.0);
    QVERIFY(label != nullptr);

    QCOMPARE(label->pixmap().size(), widget.size());

    delete label;
}

// render() devolve a posse do QLabel pra quem chamou; nao ha mais acumulo interno
// de labels a cada chamada, desde que quem chama delete o retorno.
void TestBlur::callerOwnsLabel_deletingItLeavesNoChildBehind()
{
    QWidget widget;
    widget.setFixedSize(100, 100);

    delete QtToolkit::Blur::render(&widget, 5.0);
    delete QtToolkit::Blur::render(&widget, 5.0);
    delete QtToolkit::Blur::render(&widget, 5.0);

    QCOMPARE(widget.findChildren<QLabel*>().size(), 0);
}

QTEST_MAIN(TestBlur)
#include "test_blur.moc"