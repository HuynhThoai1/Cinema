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

using std::cin;
using std::cout;
using std::string;

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
        cout << "-> Khong duoc de trong. Vui long nhap lai!\n";
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
        cout << "-> Gia tri khong hop le. Vui long nhap lai!\n";
    }
}

void MovieUI::showAll() {
    auto movies = movieBUS.getAll();
    if (movies.empty()) {
        cout << "Chua co phim nao.\n";
        return;
    }

    cout << "===== DANH SACH PHIM =====\n";
    for (const auto& m : movies) {
        cout << CYAN << "ID: " << m.getId()
             << " | Ten: " << m.getTitle()
             << " | The loai: " << m.getGenre()
             << " | Thoi luong: " << m.getDuration() << " phut"<< RESET <<"\n";
    }
}

void MovieUI::addMovie() {
    cout << "===== THEM PHIM =====\n";
    string id = inputNonEmptyLine("Nhap ID phim: ");
    string title = inputNonEmptyLine("Nhap ten phim: ");
    string genre = inputNonEmptyLine("Nhap the loai: ");
    int duration = inputIntInRange("Nhap thoi luong (1..500): ", 1, 500);

    Movie movie(id, title, genre, duration);
    if (movieBUS.addMovie(movie)) cout << "-> Them phim thanh cong!\n";
    else cout << "-> Them phim THAT BAI (co the trung ID / du lieu khong hop le)!\n";
}

void MovieUI::updateMovie() {
    cout << "===== CAP NHAT PHIM =====\n";
    string id = inputNonEmptyLine("Nhap ID phim can cap nhat: ");
    string title = inputNonEmptyLine("Nhap ten phim moi: ");
    string genre = inputNonEmptyLine("Nhap the loai moi: ");
    int duration = inputIntInRange("Nhap thoi luong moi (1..500): ", 1, 500);

    Movie movie(id, title, genre, duration);
    if (movieBUS.updateMovie(movie)) cout << "-> Cap nhat phim thanh cong!\n";
    else cout << "-> Cap nhat THAT BAI (ID khong ton tai / du lieu khong hop le)!\n";
}

void MovieUI::deleteMovie() {
    cout << "===== XOA PHIM =====\n";
    string id = inputNonEmptyLine("Nhap ID phim can xoa: ");

    if (movieBUS.deleteMovie(id)) cout << "-> Xoa phim thanh cong!\n";
    else cout << "-> Xoa THAT BAI (ID khong ton tai / phim dang co suat chieu)!\n";
}

void MovieUI::run() {
    while (true) {
        clearScreen();
        printHeader("MOVIE MENU");
        cout << CYAN << "1. Xem danh sach phim" << RESET << "\n";
        cout << CYAN << "2. Them phim" << RESET << "\n";
        cout << CYAN << "3. Cap nhat phim" << RESET << "\n";
        cout << CYAN << "4. Xoa phim" << RESET << "\n";
        cout << CYAN << "0. Thoat" << RESET << "\n";
        cout << "Chon: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "-> Lua chon khong hop le.\n";
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: showAll(); break;
            case 2: addMovie(); break;
            case 3: updateMovie(); break;
            case 4: deleteMovie(); break;
            case 0: return;
            default: cout << "-> Lua chon khong hop le.\n"; break;
        }
        cout << "(An Enter de tiep tuc...)"; cin.ignore(); cin.get();
    }
}
