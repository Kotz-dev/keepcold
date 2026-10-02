//
// Created by KoTz on 15/07/2026.
//

#include "io/FileManager.h"
#include <QDebug>
#include <QFile>
#include <QLocale>
#include <filesystem>
#include <QFileInfo>
#include <fstream>
#include <QFileDialog>
#include <QUrl>


QString FileManager::Local_usado;

QString FileManager::OpenFileURL(QWidget *parent)
{
    QString URL = "";

    if (parent != nullptr)
    {
        auto getURL = QFileDialog::getOpenFileUrl(
                parent, "Abrir arquivos Existentes", QUrl(), "Vault files (*.vault)");

        URL = getURL.toLocalFile();
        return URL;
    }
        return URL;
    }


void FileManager::CreateFile(QString name)
{
    if (name.isEmpty() == false)
    {
        std::fstream file(name.toStdString(), std::ios::out);
        if (file.fail())
        {
            qDebug() << "Falha ao criar arquivo:";
        }
        file.close();
    }
}


/// criar os arquivos vault
bool FileManager::CreateVaultFile(const QUrl &url)
{
    if (url.isEmpty())
        return false;

    CreateFile(url.toLocalFile());
    return true;
}

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


