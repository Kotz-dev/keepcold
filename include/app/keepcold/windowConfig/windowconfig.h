//
// Created by KoTz on 18/08/2026.
//

#ifndef KEEPCOLD_WINDOWCONFIG_H
#define KEEPCOLD_WINDOWCONFIG_H

#include <QDialog>

QT_BEGIN_NAMESPACE

namespace Ui
{
class windowConfig;
}

QT_END_NAMESPACE

class windowConfig : public QDialog
{
    Q_OBJECT

private slots:
    void on_btn_fechar_clicked();

public:
    explicit windowConfig(QWidget* parent = nullptr);
    ~windowConfig() override;

private:
    Ui::windowConfig* ui;
};

#endif  // KEEPCOLD_WINDOWCONFIG_H
