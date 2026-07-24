//
// Created by KoTz on 21/07/2026.
//

#ifndef KEEPCOLD_MEMORY_H
#define KEEPCOLD_MEMORY_H

template<typename T>
void safeDelete(T*& obj)
{
    if (obj != nullptr)
    {
        delete obj;
        obj = nullptr;
    }
}

#endif // KEEPCOLD_MEMORY_H