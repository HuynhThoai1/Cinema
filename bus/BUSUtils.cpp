#include "BUSUtils.h"
#include <sstream>
#include <iostream>


std::string CurrencyFormat::formatCurrency(long long amount) {
    std::string money = std::to_string(amount);
    if (money.length() > 3) {
        for(size_t i = money.length() - 3; i > 0; i -= 3) {
            money.insert(i, ".");
            if (i <= 3) break; // Prevent underflow in next iteration
        }
    }

    return money;
}