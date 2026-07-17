//
// Created by KoTz on 15/07/2026.
//

#include "io/FileManger.h"
#include <QDebug>

QString FileManger::loadStyleSheet(std::string name, PATCH_TYPE_ type) {
    QString styleSheet = "";
    std::string Path = "";

    if (name.empty())
        return "";

    if (type == FILE_styles) {
        auto get = std::filesystem::current_path().remove_filename();
        for (auto & i : std::filesystem::recursive_directory_iterator(get)) {
            if (i.path().string().find(name) != std::string::npos) {
                QFile f(QString::fromStdString(i.path().string()));
                f.open(QFile::ReadOnly);
                styleSheet = f.readAll();
                break;
            }
        }
        return styleSheet;
    }
    if (type == FILE_IMAGE) {
        auto c = std::filesystem::current_path().remove_filename() / Path / name;
        return QString::fromStdString(c.string());
    }
    return "";
}


