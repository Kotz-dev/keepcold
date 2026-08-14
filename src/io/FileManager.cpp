//
// Created by KoTz on 15/07/2026.
//

#include "io/FileManager.h"
#include <QDebug>
#include <QFile>
#include <boost/filesystem.hpp>
#include <QFileInfo>

QString FileManager::SizeMemory(QUrl patch)
{
    if (patch.isEmpty() == false)
    {
        auto bytes = boost::filesystem::file_size(patch.path().toStdString());
        if (bytes > 0){
            QString size;
            if (bytes < 1024)
               return size = QString::number(bytes) + " Bytes";
            else if (bytes < 1024 * 1024)
               return size = QString::number(bytes / 1024.0, 'f', 1) + " KB";
            else if (bytes < 1024 * 1024 * 1024)
               return size = QString::number(bytes / (1024.0 * 1024), 'f', 1) + " MB";
            else
               return size = QString::number(bytes / (1024.0 * 1024 * 1024), 'f', 2) + " GB";
        }
    }
}

QString FileManager::loadStyleSheet(std::string name, PATCH_TYPE_ type)
{
    QString styleSheet = "";
    std::string Path = "";

    if (name.empty())
        return "";

    if (type == FILE_styles)
    {
        std::replace(name.begin(), name.end(), '\\', '/');
        auto get = std::filesystem::current_path().remove_filename();
        for (auto& i : std::filesystem::recursive_directory_iterator(get))
        {
            if (i.path().generic_string().find(name) != std::string::npos)
            {
                QFile f(QString::fromStdString(i.path().string()));
                f.open(QFile::ReadOnly);
                styleSheet = f.readAll();
                break;
            }
        }
        return styleSheet;
    }
    if (type == FILE_IMAGE)
    {
        auto c = std::filesystem::current_path().remove_filename() / Path / name;
        return QString::fromStdString(c.string());
    }
    return "";
}


