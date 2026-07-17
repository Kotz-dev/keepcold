//
// Created by KoTz on 14/07/2026.
//

#ifndef KEEPCOLD_MAINWINDOW_H
#define KEEPCOLD_MAINWINDOW_H

#include <QMainWindow>
#include <app/Animation/Animation.h>
#include <app/Animation/ProgressBar.h>



enum class StackPage {

        Welcome     = 1,  // Image 1: tela inicial com os 3 cards
        CreateVault = 2,  // Image 2: formulário "Criar novo cofre"
        OpenVault   = 0,  // Image 3: tela "Abrir cofre" (senha + dica)
        VaultMain   = 3   // Image 4: tela principal, cofre desbloqueado (lista + detalhe)

};

QT_BEGIN_NAMESPACE
namespace Ui {
    class mainwindow;
}
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
    Q_OBJECT
private slots:
    void on_btn_create_cofre_clicked();
    void on_btn_back_clicked();
    void on_btn_open_cofre_clicked();
    void on_back_open_cofre_clicked();
    void on_line_password_mestra_textEdited(const QString &arg1);
private :
    void navigateTo(StackPage page, QWidget *frameToAnimate,
        const std::function<void()> &onShow = nullptr);

    void Page(StackPage page);
public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;

private:
    SegmentedProgressBar *strengthBar = new SegmentedProgressBar(this);
    Ui::mainwindow *ui;
};


#endif // KEEPCOLD_MAINWINDOW_H
