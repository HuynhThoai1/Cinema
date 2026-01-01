#include "InputUtils.h"
#include <cctype>

int InputUtils::readInt(const string& message) {
    int number;
    while (true) {
        cout << message; // In ra lời nhắc (VD: "Chon: ")
        
        if (cin >> number) {
            // Nhập thành công -> Xóa bộ nhớ đệm để tránh trôi lệnh cho lần sau
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        } 
        else {
            // Nhập lỗi (chữ cái, ký tự lạ)
            cout << ">> Lỗi: Vui lòng chỉ nhập số nguyên!\n";
            cin.clear(); // Xóa trạng thái lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ nhớ đệm
        }
    }
}

char InputUtils::readYesNo(const string& message) {
    while (true) {
        cout << message;
        string s;
        if (!std::getline(cin, s)) {
            // Khôi phục trạng thái nếu cần
            cin.clear();
            continue;
        }
        if (s.empty()) continue;
        char c = static_cast<char>(std::tolower(static_cast<unsigned char>(s[0])));
        if (c == 'y' || c == 'n') return c;
        cout << ">> Lỗi: Vui lòng chỉ nhập 'y' hoặc 'n'!\n";
    }
}