//
// Created by KoTz on 30/07/2026.
//

#ifndef KEEPCOLD_WINDOWITEM_H
#define KEEPCOLD_WINDOWITEM_H

#include <QDialog>
#include <QLineEdit>
#include <QSize>
#include <QString>
#include <vector>

QT_BEGIN_NAMESPACE
class QPushButton;

enum class StackedPage : int
   {
       Menu = 0,
       Logins = 1,
       Note = 2,
       Keys = 3,
       Recuperacao = 4,
       Cartao = 5,
       Identidade = 6,
       Wifi = 7,
       File = 8,
   };
constexpr int MENU        = static_cast<int>(StackedPage::Menu);
constexpr int LOGINS      = static_cast<int>(StackedPage::Logins);
constexpr int NOTE        = static_cast<int>(StackedPage::Note);
constexpr int KEYS        = static_cast<int>(StackedPage::Keys);
constexpr int RECUPERACAO = static_cast<int>(StackedPage::Recuperacao);
constexpr int CARTAO      = static_cast<int>(StackedPage::Cartao);
constexpr int IDENTIDADE  = static_cast<int>(StackedPage::Identidade);
constexpr int WIFI        = static_cast<int>(StackedPage::Wifi);
constexpr int FILE_PAGE   = static_cast<int>(StackedPage::File);


namespace Ui
{
class windowItem;
}

QT_END_NAMESPACE


struct ItemGroup
{
    QLineEdit* lineName = nullptr;
};

struct ItemButtonGroup
{
    QPushButton* btnCard        = nullptr;
    QPushButton* btnCancelar    = nullptr;
    QPushButton* btnTrocarType  = nullptr;
    QPushButton* btnSalvar      = nullptr;
    int pageIndex               = 0;
    QSize size                  = QSize(0, 0);
    QString titulo;
    QString icone;
    QString descricao;
    ItemGroup obj;
};

class windowItem : public QDialog
{
    Q_OBJECT
private slots:
    void onMenuButtonClicked();
    void on_btn_close_clicked();

    void init_ ();

    void teste();

    void btn_upload_clicked();

    void on_btn_download_file_clicked();

    void getfile(QUrl file);
public:
    QSize janela = QSize(542,467);

    explicit windowItem(QWidget* parent = nullptr);
    void setupButtonCards();
    ~windowItem() override;

private:
    Ui::windowItem* ui;
    std::vector<ItemButtonGroup> itemGroups_;

    void applyItemStyle();
    void buildItemGroups();
};

#endif  // KEEPCOLD_WINDOWITEM_H
