#include "Validation.h"

bool Validation::isValidUsername(const string& username) {
    // Regex: ^ (bắt đầu), [a-zA-Z0-9_] (chữ thường, hoa, số, _), {5,20} (độ dài), $ (kết thúc)
    const regex pattern("^[a-zA-Z0-9_]{5,20}$");
    return regex_match(username, pattern);
}

bool Validation::isValidPassword(const string& password) {
    // Đơn giản là độ dài >= 6
    return password.length() >= 6;
}