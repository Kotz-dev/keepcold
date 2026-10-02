//
// Created by KoTz on 23/09/2026.
//

#include "json_.h"

#include <QDebug>
#include <QFile>

bool json_::writeFileToJson(const std::vector<std::unique_ptr<Item>> &obj, const QString &URL)
{

        nlohmann::json json = nlohmann::json::array();

        for (const auto &item : obj)
        {
            json.push_back(item->toJson());
        }

        QFile file(URL);
        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate) == false)
        {
            throw;
            return false;
        }

        file.write(QByteArray::fromStdString(json.dump(4)));

    return true;
}
