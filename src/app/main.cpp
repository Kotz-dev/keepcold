#include <QApplication>
#include <app/keepcold/mainwindow/mainwindow.h>
#include <src/core/third_party/zxcvbn/zxcvbn.h>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainwindow w;
    w.show();
    std::string text = "5a1d8sa4d8qwd4q8d4qw";
    qDebug () << ZxcvbnMatch(text.c_str(),nullptr,nullptr);
    return QApplication::exec();
}
