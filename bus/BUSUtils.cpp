#include "BUSUtils.h"
#include <sstream>
#include <iostream>


std::string CurrencyFormat::formatCurrency(long long amount) {
    std::string money = std::to_string(amount);
    for(int i=static_cast<int>(money.length())-3; i>0; i-=3) {
        money.insert(i, ".");
    }

    return money;
}