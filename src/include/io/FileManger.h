//
// Created by KoTz on 15/07/2026.
//

#ifndef KEEPCOLD_FILEMANGER_H
#define KEEPCOLD_FILEMANGER_H

#include <QFile>
#include <filesystem>

enum PATCH_TYPE_ {
    FILE_styles = 0,
    FILE_IMAGE = 1
};

class FileManger {

public :
   static QString loadStyleSheet(std::string name, PATCH_TYPE_ type);
};


#endif // KEEPCOLD_FILEMANGER_H
