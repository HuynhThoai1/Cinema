#include "InputUtils.h"

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