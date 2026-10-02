//
// Created by KoTz on 23/09/2026.
//

#ifndef KEEPCOLD_ITENS_H
#define KEEPCOLD_ITENS_H
#include <memory>
#include <vector>

#include "item/Item.h"


class itens
{
public:
    static inline std::vector<std::unique_ptr<Item>> todos;
public:

};

#endif  // KEEPCOLD_ITENS_H
