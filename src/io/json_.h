//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_JSON__H
#define KEEPCOLD_JSON__H

#include <vector>
#include <algorithm>
#include <memory/Memory.h>
#include <src/item/itens.h>
#include <nlohmann/json.hpp>
#include <QUrl>



class json_
{
public :
    static bool writeFileToJson(const std::vector<std::unique_ptr<Item>> &obj, const QString &URL);
};

#endif  // KEEPCOLD_JSON__H
