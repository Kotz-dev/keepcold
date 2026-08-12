//
// Created by KoTz on 17/07/2026.
//

#ifndef KEEPCOLD_PASSWORDSTRENGTH_H
#define KEEPCOLD_PASSWORDSTRENGTH_H

#include <zxcvbn.h>
#include <QString>

class PasswordStrength {
private :
    static QString Password;
public :
    static   int evaluate(QString & text);
    static   bool PassowrdIguais(QString  text);
};


#endif // KEEPCOLD_PASSWORDSTRENGTH_H
