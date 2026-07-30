//
// Created by KoTz on 14/07/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "app/keepcold/mainwindow/mainwindow.h"

#include "ui_mainwindow.h"

#include <io/FileManger.h>
#include <src/core/PasswordStrength.h>
#include <styles/UIStyle.h>
#include <QSplitter>
#include <src/qt-widgets-toolkit/QtWidgetStoolkit.h>

void mainwindow::on_btn_create_cofre_clicked() {
    ClearStrengthBar(ui->progressBar);
    ui->pageCreateVault->setAttribute(Qt::WA_TranslucentBackground);
    WindowPage::NavigetPage(StackPage::CreateVault);
}

void mainwindow::on_btn_back_clicked() {
    ClearStrengthBar(ui->progressBar);
    WindowPage::NavigetPage(StackPage::Welcome);
}

void mainwindow::on_btn_open_cofre_clicked() {
    WindowPage::NavigetPage(StackPage::OpenVault);
}

void mainwindow::on_back_open_cofre_clicked() {
    WindowPage::NavigetPage(StackPage::Welcome);

}

void mainwindow::on_btn_create_cofre_cp_clicked()
{
    WindowPage::NavigetPage(StackPage::VaultMain);
}

void mainwindow::showUI() {
    ui->frame_14->show();
   // this->strengthBar->show();
    ui->progressBar->show();
}

void mainwindow::ClearStrengthBar(QProgressBar *widget) {
    if (widget != nullptr) {
        widget->setValue(0);
        widget->hide();
        ui->progressBar->hide();
        ui->frame_14->hide();
        ui->label_forca_senha->clear();
        return;
    }
}

void mainwindow::on_btn_max_window_clicked() {
    toggleMaximize();
}
void mainwindow::on_btn_min_window_clicked() {
    showMinimized();
}
void mainwindow::on_btn_close_window_clicked() {
    close();
}


void mainwindow::on_btn_documento_clicked() {
   ui->stackedWidget_2->setCurrentIndex(3);
}


// Desgin QProcesdar
void mainwindow::setupStrengthBar(int value)
{

    if (ui->line_password_mestra->text().isEmpty())
    {
        ClearStrengthBar(ui->progressBar);
    }
    QtToolkit::ProgessBar::SegmentedProgressBar::render(value, ui->progressBar);
}

void mainwindow::on_line_cfr_passaword_mestra_textEdited(const QString& arg1)
{
    if (arg1.isEmpty() == true)
    {
        ui->label_erro_senha->hide();
        ui->line_cfr_passaword_mestra->setStyleSheet("border: 1px solid #3a4368");
        return;
    }
    if (!PasswordStrength::PassowrdIguais(arg1))
    {
        ui->label_erro_senha->setStyleSheet("color: rgb(239, 107, 107);");
        ui->line_cfr_passaword_mestra->setStyleSheet("border: 1px solid #ef6b6b;");
        ui->label_erro_senha->show();
    }
    else
    {
        ui->label_erro_senha->hide();
    }
}
// Line Passowrd
void mainwindow::on_line_password_mestra_textEdited(const QString& arg1)
{
    showUI();
    QString text = arg1;
    setupStrengthBar(PasswordStrength::evaluate(text));
    ui->label_forca_senha->setText(text);
}


bool mainwindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->barra_titule_) {
        if (event->type() == QEvent::MouseButtonPress) {
            auto *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                m_dragging = true;
                // guarda a diferença entre onde clicou e a posição da janela
                m_dragStartPosition = mouseEvent->globalPosition().toPoint() - frameGeometry().topLeft();
                return true;
            }
        }
        else if (event->type() == QEvent::MouseMove) {
            auto *mouseEvent = static_cast<QMouseEvent*>(event);
            if (m_dragging && (mouseEvent->buttons() & Qt::LeftButton)) {
                move(mouseEvent->globalPosition().toPoint() - m_dragStartPosition);
                return true;
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease) {
            m_dragging = false;
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);

}
mainwindow::mainwindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    WindowPage::__init__(ui, this);
    ui->stackedWidget_2->setCurrentIndex(5);
    //ui->stackedWidget->setCurrentIndex(2);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->barra_titule_->installEventFilter(this);
}
void mainwindow::toggleMaximize() {
    auto *anim = new QPropertyAnimation(this, "geometry");
    anim->setDuration(500);
    anim->setEasingCurve(QEasingCurve::OutCubic);

    if (!m_isMaximized) {
        m_normalGeometry = geometry();
        QRect screenGeometry = screen()->availableGeometry();
        anim->setStartValue(geometry());
        anim->setEndValue(screenGeometry);
        m_isMaximized = true;
    } else {
        anim->setStartValue(geometry());
        anim->setEndValue(m_normalGeometry);
        m_isMaximized = false;
    }


     ui->pageWelcome->setUpdatesEnabled(false);
    ui->frame_9->setUpdatesEnabled(false);
    connect(anim, &QPropertyAnimation::finished, this, [this]() {
         ui->pageWelcome->setUpdatesEnabled(true);
        ui->frame_9->setUpdatesEnabled(true);
        ui->pageWelcome->update();
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);

}


mainwindow::~mainwindow() { delete ui; }
