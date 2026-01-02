/**
 * @file ShowtimeUI.cpp
 * @brief Cài đặt UI console cho Showtime, tách menu Admin và Customer.
 */

#include "ShowtimeUI.h"
#include "../utils/InputUtils.h"
#include "../utils/FormatUI.h" // Import để dùng màu và clearScreen
#include "MovieUI.h"

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
        cout << YELLOW << "-> Không được để trống. Vui lòng nhập lại!\n" << RESET;
    }
}
// ------------------------------


void ShowtimeUI::showAllShowtimes() {
    cout << "===== TẤT CẢ SUẤT CHIẾU (LỊCH CHIẾU) =====\n";


    ShowtimeDAL dal(DATA_PATH("Showtime.txt"));
    auto showtimes = dal.loadShowtimes();

    if (showtimes.empty()) {
        cout << "-> Chưa có suất chiếu nào.\n";
        return;
    }

    for (const auto& s : showtimes) {
        cout << "ID: " << s.getId()
             << " | MovieID: " << s.getMovieId()
             << " | Start: " << s.getStartTime()
             << " | Room: " << s.getRoom() << "\n";
    }
}

void ShowtimeUI::searchShowtimesByMovieId() {
    printHeader("TÌM SUẤT CHIẾU THEO MOVIE ID");
    string movieId = inputNonEmptyLine("Nhập Movie ID: ");

    auto sts = showtimeBUS.getByMovie(movieId);
    
    cout << "\n";
    if (sts.empty()) {
        cout << YELLOW << ">> Không có suất chiếu nào cho phim này.\n" << RESET;
    } else {
        cout << GREEN << ">> Tìm thấy " << sts.size() << " suất chiếu:\n" << RESET;
        
        // Header bảng
        cout << GREEN << "---------------------------------------------------------\n";
        cout << "| " << YELLOW << left << setw(10) << "ID"
             << GREEN << "| " << YELLOW << left << setw(10) << "MovieID"
             << GREEN << "| " << YELLOW << left << setw(20) << "Start Time"
             << GREEN << "| " << YELLOW << left << setw(10) << "Room"
             << GREEN << " |\n";
        cout << "---------------------------------------------------------" << RESET << "\n";

        // Dữ liệu
        for (const auto& s : sts) {
            cout << GREEN << "| " << CYAN << left << setw(10) << s.getId()
                 << GREEN << "| " << RESET << left << setw(10) << s.getMovieId()
                 << GREEN << "| " << RESET << left << setw(20) << s.getStartTime()
                 << GREEN << "| " << RESET << left << setw(10) << s.getRoom()
                 << GREEN << " |" << RESET << "\n";
        }
        cout << GREEN << "---------------------------------------------------------" << RESET << "\n";
    }
}

void ShowtimeUI::addShowtime() {
    cout << "===== ADMIN: THÊM SUẤT CHIẾU =====\n";
    string id = inputNonEmptyLine("Nhập Showtime ID: ");
    string movieId = inputNonEmptyLine("Nhập Movie ID: ");
    string startTime = inputNonEmptyLine("Nhập StartTime (yyyy-mm-dd HH:MM): ");
    string room = inputNonEmptyLine("Nhập Phòng chiếu: ");

    // DTO Showtime ctor: (id, movieId, room, startTime)
    Showtime s(id, movieId, room, startTime);

    if (showtimeBUS.addShowtime(s)) {
        cout << GREEN << "\n>> Thêm suất chiếu thành công!" << RESET << "\n";
    } else {
        cout << RED << "\n>> Thêm THẤT BẠI!" << RESET << "\n";
        cout << "   (Nguyên nhân: ID trùng, MovieID không tồn tại, hoặc lỗi Định dạng/Trùng lịch)\n";
    }
}

void ShowtimeUI::deleteShowtime() {
    cout << "===== ADMIN: XÓA SUẤT CHIẾU =====\n";
    string id = inputNonEmptyLine("Nhập Showtime ID cần xóa: ");

    if (showtimeBUS.deleteShowtime(id)) {
        cout << "-> Xóa suất chiếu thành công!\n";
    } else {
        cout << "-> Xóa THẤT BẠI (ID không tồn tại)!\n";
    }
}

void ShowtimeUI::runAdmin() {
    MovieUI movieUI;
    while (true) {
        clearScreen();
        printHeader("SHOWTIME MENU (ADMIN)");
        
        cout << CYAN << "1. Xem lịch chiếu" << RESET << "\n";
        cout << CYAN << "2. Thêm suất chiếu" << RESET << "\n";
        cout << CYAN << "3. Xóa suất chiếu" << RESET << "\n";
        cout << CYAN << "0. Thoát" << RESET << "\n";
        cout << "------------------------------------------\n";
        cout << "Chọn: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << RED << "-> Lựa chọn không hợp lệ." << RESET << "\n";
            cout << "(Ấn Enter để tiếp tục...)"; cin.get();
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: 
                clearScreen();
                movieUI.showAll();
                searchShowtimesByMovieId();
                cout << "(Ấn Enter để tiếp tục...)"; cin.get();
                break;
            case 2: 
                clearScreen();
                addShowtime();
                cout << "(Ấn Enter để tiếp tục...)"; cin.get();
                break;
            case 3: 
                clearScreen();
                deleteShowtime();
                cout << "(Ấn Enter để tiếp tục...)"; cin.get();
                break;
            case 0: return;
            default: 
                cout << RED << "-> Lựa chọn không hợp lệ." << RESET << "\n";
                cout << "(Ấn Enter để tiếp tục...)"; cin.get();
                break;
        }
    }
}

void ShowtimeUI::runCustomer() {
    MovieUI movieUI;
    while (true) {
        clearScreen();
        printHeader("SHOWTIME MENU (CUSTOMER)");
        
        cout << CYAN << "1. Xem lịch chiếu" << RESET << "\n";
        cout << CYAN << "0. Thoát" << RESET << "\n";
        cout << "------------------------------------------\n";
        cout << "Chọn: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << RED << "-> Lựa chọn không hợp lệ." << RESET << "\n";
            cout << "(Ấn Enter để tiếp tục...)"; cin.get();
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: 
                clearScreen();
                movieUI.showAll();
                searchShowtimesByMovieId();
                cout << "(Ấn Enter để tiếp tục...)"; cin.get();
                break;
            case 0: return;
            default: 
                cout << RED << "-> Lựa chọn không hợp lệ." << RESET << "\n";
                cout << "(Ấn Enter để tiếp tục...)"; cin.get();
                break;
        }
    }
}

void ShowtimeUI::run() {
    // Theo yêu cầu: run() dành cho Admin
    runAdmin();
}
