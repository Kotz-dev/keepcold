//
// Created by KoTz on 15/07/2026.
//

#include "styles/UIStyle.h"
#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>
#include <QWidget>
#include <widgets/PasswordLineEdit.h>
#include <io/FileManger.h>
#include <styles/RichText.h>


void UIStyle::CardButton::apply(QPushButton *button, const QString &title) {
    if (button == nullptr || button->layout() != nullptr) {
        return;
    }
    QLabel *content = new QLabel(button);
    content->setText(title);

    content->setWordWrap(true);

    content->setAttribute(Qt::WA_TransparentForMouseEvents);

    QVBoxLayout *layout = new QVBoxLayout(button);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(12);
    layout->setAlignment(Qt::AlignTop);

    QLabel *icon = new QLabel(button);
    icon->setFixedSize(36, 36);

    content->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    layout->addWidget(icon);
    layout->addWidget(content);
}
void UIStyle::Page::Welcome::show(Ui::mainwindow *obj,QWidget *parent,QString fileName) {
    if (parent == nullptr) {
        return;
    }

 QString text = "";
   text = RichText::cardDescription("Criar novo cofre","Defina uma senha mestra e escolha onde salvar seu arquivo.");
      UIStyle::CardButton::apply(obj->btn_create_cofre,text);
   text =  RichText::cardDescription("Abrir cofre existente","Selecione um arquivo\t\t .vault e digite a senha.");
    UIStyle::CardButton::apply(obj->btn_open_cofre,text);

    parent->setStyleSheet(FileManger::loadStyleSheet("keepcold\\resources\\Styles\\dark\\" + fileName.toStdString(), PATCH_TYPE_::FILE_styles));

}
void UIStyle::Page::PasswordField::show(QLineEdit *lineEdit, QWidget *parent, QString fileName) {
    if (lineEdit == nullptr || lineEdit->layout() != nullptr) {
        return;
    }
    DeleteMemory(obj);
    setupPasswordVisibilityToggle(lineEdit,obj = new QAction);
    parent->setStyleSheet(FileManger::loadStyleSheet("keepcold\\resources\\Styles\\dark\\" + fileName.toStdString(), PATCH_TYPE_::FILE_styles));

}
