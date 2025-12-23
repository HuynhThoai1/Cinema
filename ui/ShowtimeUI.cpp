/**
 * @file ShowtimeUI.cpp
 * @brief Cài đặt giao diện console cho module Showtime.
 *
 * @details
 * - UI chỉ xử lý nhập/xuất.
 * - Edge cases được kiểm soát ở ShowtimeBUS.
 */

#include "ShowtimeUI.h"

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

void ShowtimeUI::showByMovie() {
    cout << "===== XEM SUAT CHIEU THEO PHIM =====\n";
    string movieId = inputNonEmptyLine("Nhap Movie ID: ");

    auto sts = showtimeBUS.getByMovie(movieId);
    if (sts.empty()) {
        cout << "-> Khong co suat chieu nao cho phim nay.\n";
        return;
    }

    cout << "===== DANH SACH SUAT CHIEU =====\n";
    for (const auto& s : sts) {
        cout << "ID: " << s.getId()
             << " | MovieID: " << s.getMovieId()
             << " | Start: " << s.getStartTime()
             << " | Room: " << s.getRoom() << "\n";
    }
}

void ShowtimeUI::addShowtime() {
    cout << "===== THEM SUAT CHIEU =====\n";
    string id = inputNonEmptyLine("Nhap Showtime ID: ");
    string movieId = inputNonEmptyLine("Nhap Movie ID: ");
    string startTime = inputNonEmptyLine("Nhap StartTime (yyyy-mm-dd HH:MM): ");
    string room = inputNonEmptyLine("Nhap phong: ");

    // DTO Showtime ctor: (id, movieId, room, startTime)
    Showtime s(id, movieId, room, startTime);

    if (showtimeBUS.addShowtime(s)) {
        cout << "-> Them suat chieu thanh cong!\n";
    } else {
        cout << "-> Them THAT BAI (movieId khong ton tai / trung lich / sai datetime / trung ID)!\n";
    }
}

void ShowtimeUI::deleteShowtime() {
    cout << "===== XOA SUAT CHIEU =====\n";
    string id = inputNonEmptyLine("Nhap Showtime ID can xoa: ");

    if (showtimeBUS.deleteShowtime(id)) cout << "-> Xoa suat chieu thanh cong!\n";
    else cout << "-> Xoa THAT BAI (ID khong ton tai)!\n";
}

void ShowtimeUI::run() {
    while (true) {
        cout << "\n===== SHOWTIME MENU =====\n";
        cout << "1. Xem suat chieu theo phim\n";
        cout << "2. Them suat chieu\n";
        cout << "3. Xoa suat chieu\n";
        cout << "0. Thoat\n";
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
            case 1: showByMovie(); break;
            case 2: addShowtime(); break;
            case 3: deleteShowtime(); break;
            case 0: return;
            default: cout << "-> Lua chon khong hop le.\n"; break;
        }
    }
}
