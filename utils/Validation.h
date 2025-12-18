#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
#include <regex>

using namespace std;

class Validation {
public:
    // Kiểm tra Username: 5-20 ký tự, chỉ chứa chữ cái, số và gạch dưới (_)
    static bool isValidUsername(const string& username);

    // Kiểm tra Password: Tối thiểu 6 ký tự
    static bool isValidPassword(const string& password);
};

#endif