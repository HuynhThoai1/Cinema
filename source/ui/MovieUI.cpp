/**
 * @file MovieUI.cpp
 * @brief Cài đặt giao diện console cho module Movie.
 *
 * @details
 * - UI chỉ xử lý nhập/xuất và điều hướng.
 * - Validate nghiệp vụ được xử lý ở MovieBUS.
 */

#include "MovieUI.h"

#include "../utils/FormatUI.h"

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using std::cin;
using std::cout;
using std::string;
using std::left;
using std::setw;

static string trim(string s) {
    const char* ws = " \t\r\n";
    auto b = s.find_first_not_of(ws);
    auto e = s.find_last_not_of(ws);
    if (b == string::npos) return {};
    return s.substr(b, e - b + 1);
}

static string inputNonEmptyLine(const string& prompt) {
    while (true) {
        cout << prompt;
        string s;
        std::getline(cin, s);
        s = trim(s);
        if (!s.empty()) return s;
        cout << "-> Không được để trống. Vui lòng nhập lại!\n";
    }
}

static int inputIntInRange(const string& prompt, int minVal, int maxVal) {
    while (true) {
        cout << prompt;
        int x;
        if (cin >> x) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (x >= minVal && x <= maxVal) return x;
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cout << "-> Giá trị không hợp lệ. Vui lòng nhập lại!\n";
    }
}

void MovieUI::showAll() {
    auto movies = movieBUS.getAll();
    
    cout << "\n";
    if (movies.empty()) {
        cout << YELLOW << ">> Chưa có phim nào.\n" << RESET;
        return;
    }

    cout << GREEN << ">> Tìm thấy " << movies.size() << " phim:\n" << RESET;
    
    // Header bảng
    cout << GREEN << "-------------------------------------------------------------------------\n";
    cout << "| " << YELLOW << left << setw(10) << "ID"
         << GREEN << "| " << YELLOW << left << setw(25) << "Tên Phim"
         << GREEN << "| " << YELLOW << left << setw(15) << "Thể Loại"
         << GREEN << "| " << YELLOW << left << setw(12) << "Thời Lượng"
         << GREEN << " |\n";
    cout << "-------------------------------------------------------------------------" << RESET << "\n";

    // Dữ liệu
    for (const auto& m : movies) {
        cout << GREEN << "| " << CYAN << left << setw(10) << m.getId()
             << GREEN << "| " << RESET << left << setw(25) << m.getTitle()
             << GREEN << "| " << RESET << left << setw(15) << m.getGenre()
             << GREEN << "| " << RESET << left << setw(12) << (std::to_string(m.getDuration()) + " phút")
             << GREEN << " |" << RESET << "\n";
    }
    cout << GREEN << "-------------------------------------------------------------------------" << RESET << "\n";
}

void MovieUI::addMovie() {
    cout << "===== THÊM PHIM =====\n";
    string id = inputNonEmptyLine("Nhập ID phim: ");
    string title = inputNonEmptyLine("Nhập tên phim: ");
    string genre = inputNonEmptyLine("Nhập thể loại: ");
    int duration = inputIntInRange("Nhập thời lượng (1..500): ", 1, 500);

    Movie movie(id, title, genre, duration);
    if (movieBUS.addMovie(movie)) cout << "-> Thêm phim thành công!\n";
    else cout << "-> Thêm phim THẤT BẠI (có thể trùng ID / dữ liệu không hợp lệ)!\n";
}

void MovieUI::updateMovie() {
    cout << "===== CẬP NHẬT PHIM =====\n";
    string id = inputNonEmptyLine("Nhập ID phim cần cập nhật: ");
    string title = inputNonEmptyLine("Nhập tên phim mới: ");
    string genre = inputNonEmptyLine("Nhập thể loại mới: ");
    int duration = inputIntInRange("Nhập thời lượng mới (1..500): ", 1, 500);

    Movie movie(id, title, genre, duration);
    if (movieBUS.updateMovie(movie)) cout << "-> Cập nhật phim thành công!\n";
    else cout << "-> Cập nhật THẤT BẠI (ID không tồn tại / dữ liệu không hợp lệ)!\n";
}

void MovieUI::deleteMovie() {
    cout << "===== XÓA PHIM =====\n";
    string id = inputNonEmptyLine("Nhập ID phim cần xóa: ");

    if (movieBUS.deleteMovie(id)) cout << "-> Xóa phim thành công!\n";
    else cout << "-> Xóa THẤT BẠI (ID không tồn tại / phim đang có suất chiếu)!\n";
}

void MovieUI::run() {
    while (true) {
        clearScreen();
        printHeader("MOVIE MENU");
        cout << CYAN << "1. Xem danh sách phim" << RESET << "\n";
        cout << CYAN << "2. Thêm phim" << RESET << "\n";
        cout << CYAN << "3. Cập nhật phim" << RESET << "\n";
        cout << CYAN << "4. Xóa phim" << RESET << "\n";
        cout << CYAN << "0. Thoát" << RESET << "\n";
        cout << "Chọn: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "-> Lựa chọn không hợp lệ.\n";
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: showAll(); break;
            case 2: addMovie(); break;
            case 3: updateMovie(); break;
            case 4: deleteMovie(); break;
            case 0: return;
            default: cout << "-> Lựa chọn không hợp lệ.\n"; break;
        }
        cout << "(Ấn Enter để tiếp tục...)"; cin.ignore(); cin.get();
    }
}
