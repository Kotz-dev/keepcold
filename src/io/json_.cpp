//
// Created by KoTz on 23/09/2026.
//

#include "json_.h"

#include <QDebug>
#include <QFile>
#include <QSaveFile>

void json_::writeFileToJson(const std::vector<std::unique_ptr<Item>> &obj, const QString &URL)
{
    if (URL.isEmpty())
    {
        return;
    }
    try
    {
        QFile file(URL);
        nlohmann::json json = nlohmann::json::array();
        for (const auto &item : obj)
        {
            json.push_back(item->toJson());
        }
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate) == false)
        {
            throw;
        }
        file.write(QByteArray::fromStdString(json.dump(4)));
        file.close();
    }catch (nlohmann::json::exception &e)
    {

    }
}
