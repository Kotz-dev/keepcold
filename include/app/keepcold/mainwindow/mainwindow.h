//
// Created by KoTz on 14/07/2026.
//

#ifndef KEEPCOLD_MAINWINDOW_H
#define KEEPCOLD_MAINWINDOW_H

#include <QMainWindow>
#include <widgets/WindowPage.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class mainwindow;
}
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
    Q_OBJECT
private slots:

    void on_btn_max_window_clicked();
    void on_btn_min_window_clicked();
    void on_btn_close_window_clicked();


    // WELCOME

    void on_Welcome_btn_criar_cofre_clicked();
    void on_Welcome_btn_abrir_cofre_clicked();


    // CREATE VAULT

    void on_CreateVault_btn_criar_clicked();
    void on_CreateVault_btn_voltar_clicked();;
    void on_CreateVault_line_senha_mestra_textEdited(const QString &arg1);
    void on_CreateVault_line_confirmar_senha_textEdited(const QString &arg1);

     // OPEN VAULT
    void on_OpenVault_btn_voltar_clicked();
    void on_OpenVault_btn_trocar_arquivo_clicked();


    // VAULT MAIN

    void on_VaultMain_btn_documento_clicked();
    void on_VaultMain_btn_add_item_clicked();
    void on_VaultMain_btn_configuracao_clicked();



private :
    void ClearStrengthBar(QProgressBar *widget);
     void setupStrengthBar(int value);
    void showUI();
public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;

private:
    Ui::mainwindow *ui;
};


#endif // KEEPCOLD_MAINWINDOW_H
