/**
 * @file ShowtimeUI.cpp
 * @brief Cài đặt giao diện console cho module Showtime (Phiên bản UI mới).
 */

#include "ShowtimeUI.h"
#include "../utils/InputUtils.h"
#include "../utils/FormatUI.h" // Import để dùng màu và clearScreen

#include <iostream>
#include <string>
#include <limits>
#include <iomanip> // Để dùng setw

using std::cin;
using std::cout;
using std::string;
using std::left;
using std::setw;

// --- Helper Functions Local ---
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
        cout << YELLOW << "-> Khong duoc de trong. Vui long nhap lai!\n" << RESET;
    }
}
// ------------------------------

void ShowtimeUI::showByMovie() {
    clearScreen();
    printHeader("TRA CUU SUAT CHIEU THEO PHIM");
    
    string movieId = inputNonEmptyLine("Nhap Movie ID: ");

    auto sts = showtimeBUS.getByMovie(movieId);
    
    cout << "\n";
    if (sts.empty()) {
        cout << YELLOW << ">> Khong co suat chieu nao cho phim nay.\n" << RESET;
    } else {
        cout << GREEN << ">> Tim thay " << sts.size() << " suat chieu:\n" << RESET;
        
        // Header bảng
        cout << "---------------------------------------------------------\n";
        cout << "| " << left << setw(10) << "ID"
             << "| " << left << setw(10) << "MovieID"
             << "| " << left << setw(20) << "Start Time"
             << "| " << left << setw(10) << "Room"
             << " |\n";
        cout << "---------------------------------------------------------\n";

        // Dữ liệu
        for (const auto& s : sts) {
            cout << "| " << left << setw(10) << s.getId()
                 << "| " << left << setw(10) << s.getMovieId()
                 << "| " << left << setw(20) << s.getStartTime()
                 << "| " << left << setw(10) << s.getRoom()
                 << " |\n";
        }
        cout << "---------------------------------------------------------\n";
    }

    cout << "(An Enter de quay lai...)";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Đảm bảo buffer sạch
    // Không cần cin.get() ở đây nếu inputNonEmptyLine dùng getline, 
    // nhưng để chắc chắn dừng lại thì thêm 1 lệnh chờ:
    if (cin.peek() == '\n') cin.get(); 
}

void ShowtimeUI::addShowtime() {
    clearScreen();
    printHeader("THEM SUAT CHIEU MOI");

    string id = inputNonEmptyLine("Nhap Showtime ID: ");
    string movieId = inputNonEmptyLine("Nhap Movie ID: ");
    string startTime = inputNonEmptyLine("Nhap StartTime (yyyy-mm-dd HH:MM): ");
    string room = inputNonEmptyLine("Nhap Phong chieu: ");

    // DTO Showtime ctor: (id, movieId, room, startTime)
    Showtime s(id, movieId, room, startTime);

    if (showtimeBUS.addShowtime(s)) {
        cout << GREEN << "\n>> Them suat chieu thanh cong!" << RESET << "\n";
    } else {
        cout << RED << "\n>> Them THAT BAI!" << RESET << "\n";
        cout << "   (Nguyen nhan: ID trung, MovieID khong ton tai, hoac loi Dinh dang/Trung lich)\n";
    }
    
    cout << "(An Enter de tiep tuc...)";
    // Clean buffer logic
    // cin.ignore() thường không cần thiết sau getline nếu không bị thừa ký tự, 
    // nhưng cứ thêm để an toàn
    // cin.get();
}

void ShowtimeUI::deleteShowtime() {
    clearScreen();
    printHeader("XOA SUAT CHIEU");

    string id = inputNonEmptyLine("Nhap Showtime ID can xoa: ");

    if (showtimeBUS.deleteShowtime(id)) {
        cout << GREEN << "\n>> Xoa suat chieu thanh cong!" << RESET << "\n";
    } else {
        cout << RED << "\n>> Xoa THAT BAI (ID khong ton tai)!" << RESET << "\n";
    }

    cout << "(An Enter de tiep tuc...)";
    // cin.get();
}

void ShowtimeUI::run() {
    int choice;
    while (true) {
        clearScreen();
        printHeader("QUAN LY LICH CHIEU (SHOWTIME)");

        cout << CYAN << "1. Xem suat chieu theo phim" << RESET << "\n";
        cout << CYAN << "2. Them suat chieu" << RESET << "\n";
        cout << CYAN << "3. Xoa suat chieu" << RESET << "\n";
        cout << CYAN << "0. Quay lai Admin Menu" << RESET << "\n";
        cout << "------------------------------------------\n";

        choice = InputUtils::readInt("Nhap lua chon: ");

        if (choice == 0) break;

        switch (choice) {
            case 1: 
                showByMovie(); 
                break;
            case 2: 
                addShowtime(); 
                // Pause handle after returning from add
                if (cin.peek() == '\n') cin.get();
                break;
            case 3: 
                deleteShowtime(); 
                // Pause handle after returning from delete
                if (cin.peek() == '\n') cin.get();
                break;
            default: 
                cout << YELLOW << ">> Lua chon khong hop le!" << RESET << "\n";
                cout << "(An Enter de thu lai...)";
                cin.ignore(); cin.get();
                break;
        }
    }
}