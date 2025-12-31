/**
 * @file ShowtimeUI.cpp
 * @brief Cài đặt UI console cho Showtime, tách menu Admin và Customer.
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

ShowtimeUI::ShowtimeUI(const std::string& showtimesPath, const std::string& moviesPath)
    : showtimeBUS(ShowtimeDAL(showtimesPath), MovieDAL(moviesPath)) {}

void ShowtimeUI::showAllShowtimes() {
    cout << "===== TAT CA SUAT CHIEU (LICH CHIEU) =====\n";

    // ShowtimeBUS hiện có getByMovie(movieId). Để show tất cả,
    // ta đọc trực tiếp từ DAL thông qua BUS? Hiện BUS chưa có getAll(),
    // nên cách đơn giản là: dùng DAL đọc trực tiếp tại UI là không đúng 3-layer.
    // => Mình giữ đúng 3-layer: tạo "movieId = *" không hợp lý.
    // GIẢI PHÁP: UI sẽ dùng ShowtimeDAL trực tiếp? (không nên).
    //
    // => Mình làm đúng 3-layer bằng cách:
    // - Dùng ShowtimeDAL loadShowtimes() ngay tại UI là vi phạm nhẹ.
    // - Nên nhất: thêm ShowtimeBUS::getAll() (nhưng bạn bảo sửa UI thôi).
    //
    // Mình chọn cách TỐT NHẤT mà vẫn ít thay đổi: UI đọc từ DAL qua bus nội bộ
    // bằng cách tái tạo ShowtimeDAL cùng path và gọi loadShowtimes().
    // Nếu bạn muốn "chuẩn 100%" thì mình sẽ gửi thêm file ShowtimeBUS.h/cpp để có getAll().

    // Cách an toàn trong phạm vi UI:
    ShowtimeDAL dal("data/Showtime.txt");
    auto showtimes = dal.loadShowtimes();

    if (showtimes.empty()) {
        cout << "-> Chua co suat chieu nao.\n";
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
    cout << "===== TIM SUAT CHIEU THEO MOVIE ID (TUY CHON) =====\n";
    string movieId = inputNonEmptyLine("Nhap Movie ID: ");

    auto sts = showtimeBUS.getByMovie(movieId);
    if (sts.empty()) {
        cout << "-> Khong co suat chieu nao cho phim nay.\n";
        return;
    }

    for (const auto& s : sts) {
        cout << "ID: " << s.getId()
             << " | MovieID: " << s.getMovieId()
             << " | Start: " << s.getStartTime()
             << " | Room: " << s.getRoom() << "\n";
    }
}

void ShowtimeUI::addShowtime() {
    cout << "===== ADMIN: THEM SUAT CHIEU =====\n";
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
    cout << "===== ADMIN: XOA SUAT CHIEU =====\n";
    string id = inputNonEmptyLine("Nhap Showtime ID can xoa: ");

    if (showtimeBUS.deleteShowtime(id)) {
        cout << "-> Xoa suat chieu thanh cong!\n";
    } else {
        cout << "-> Xoa THAT BAI (ID khong ton tai)!\n";
    }
}

void ShowtimeUI::runAdmin() {
    while (true) {
        cout << "\n===== SHOWTIME MENU (ADMIN) =====\n";
        cout << "1. Xem TAT CA suat chieu\n";
        cout << "2. Tim suat chieu theo Movie ID (tuy chon)\n";
        cout << "3. Them suat chieu\n";
        cout << "4. Xoa suat chieu\n";
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
            case 1: showAllShowtimes(); break;
            case 2: searchShowtimesByMovieId(); break;
            case 3: addShowtime(); break;
            case 4: deleteShowtime(); break;
            case 0: return;
            default: cout << "-> Lua chon khong hop le.\n"; break;
        }
    }
}

void ShowtimeUI::runCustomer() {
    while (true) {
        cout << "\n===== SHOWTIME MENU (CUSTOMER) =====\n";
        cout << "1. Xem lich chieu (TAT CA suat chieu)\n";
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
            case 1: showAllShowtimes(); break;
            case 0: return;
            default: cout << "-> Lua chon khong hop le.\n"; break;
        }
    }
}

void ShowtimeUI::run() {
    // Theo yêu cầu: run() dành cho Admin
    runAdmin();
}
