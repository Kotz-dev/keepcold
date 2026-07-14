//
// Created by KoTz on 14/07/2026.
//

#ifndef KEEPCOLD_MAINWINDOW_H
#define KEEPCOLD_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
    class mainwindow;
}
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;

private:
    Ui::mainwindow *ui;
};


#endif // KEEPCOLD_MAINWINDOW_H
