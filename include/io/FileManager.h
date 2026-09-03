//
// Created by KoTz on 15/07/2026.
//

#ifndef KEEPCOLD_FILEMANAGER_H
#define KEEPCOLD_FILEMANAGER_H

#include <QFile>
#include <filesystem>
#include <QUrl>

enum PATCH_TYPE_ {
    FILE_styles = 0,
    FILE_IMAGE = 1
};

class FileManager {

public :
    static void CreateFile(QString name);
    static bool CreateVaultFile(const QUrl &url);


    static QString loadStyleSheet(std::string name, PATCH_TYPE_ type);
    static QString OpenFileURL(QWidget *parent);
    static QString formattedFileSize(const QUrl &fileUrl);
};


#endif // KEEPCOLD_FILEMANAGER_H
