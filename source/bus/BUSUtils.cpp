#include "BUSUtils.h"
#include <sstream>
#include <iostream>

using std::string;
using std::stoi;
using std::isdigit;
using std::cout;
std::string BUSUtils::formatCurrency(long long amount) {
    std::string money = std::to_string(amount);
    for(int i=money.length()-3; i>0; i-=3) {
        money.insert(i, ".");
    }

    return money;
}

bool BUSUtils::isValidSeatId(const std::string& seatId) {
    if (seatId.length() < 2 || seatId.length() > 3) return false;

    char row = seatId[0];                // A, B, C...
    if (row < 'A' || row > 'Z') return false;

    string numberPart = seatId.substr(1);
    for (char c : numberPart) {
        if (!isdigit(c)) return false;
    }

    int seatNum = stoi(numberPart);

    // 🔴 CẤU HÌNH RẠP
    const char MAX_ROW = 'C';   // chỉ có A,B,C
    const int MAX_COL = 10;     // chỉ có ghế 1 → 10

    if (row > MAX_ROW) return false;
    if (seatNum < 1 || seatNum > MAX_COL) return false;

    return true;
}

