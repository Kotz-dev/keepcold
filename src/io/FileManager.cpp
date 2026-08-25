//
// Created by KoTz on 15/07/2026.
//

#include "io/FileManager.h"
#include <QDebug>
#include <QFile>
#include <QLocale>
#include <filesystem>
#include <QFileInfo>

QString FileManager::formattedFileSize(const QUrl &fileUrl)
{
    if (fileUrl.isEmpty())
        return QString();

    const QFileInfo info(fileUrl.toLocalFile());
    if (!info.exists())
        return QString();

    return QLocale::system().formattedDataSize(info.size());
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


