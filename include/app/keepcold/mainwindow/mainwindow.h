//
// Created by KoTz on 14/07/2026.
//

#ifndef KEEPCOLD_MAINWINDOW_H
#define KEEPCOLD_MAINWINDOW_H

#include <QMainWindow>
#include <app/Animation/Animation.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QLabel>
#include <widgets/WindowPage.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class mainwindow;
}
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
    Q_OBJECT
private slots:
    void on_btn_create_cofre_clicked();
    void on_btn_create_cofre_cp_clicked();
    void on_btn_back_clicked();
    void on_btn_open_cofre_clicked();
    void on_back_open_cofre_clicked();
    void on_line_password_mestra_textEdited(const QString &arg1);
    void on_line_cfr_passaword_mestra_textEdited(const QString &arg1);
    bool eventFilter(QObject *watched, QEvent *event) override;

    void toggleMaximize();
    void on_btn_max_window_clicked();
    void on_btn_min_window_clicked();
    void on_btn_close_window_clicked();

    void on_btn_documento_clicked();



private :
    void ClearStrengthBar(QProgressBar *widget);
     void setupStrengthBar(int value);
    void showUI();
public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;

private:
    Ui::mainwindow *ui;

    bool m_dragging = false;
    QPoint m_dragStartPosition;

    bool m_isMaximized = false;
    QRect m_normalGeometry;
    QLabel *m_frameSnapshot = nullptr;

};


#endif // KEEPCOLD_MAINWINDOW_H
