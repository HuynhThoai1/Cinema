#include "TicketUI.h"
#include <iostream>
#include <iomanip>
#include <cstdlib> // system("cls")

using namespace std;

// --- CẤU HÌNH MÀU SẮC ANSI ---
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

TicketUI::TicketUI() {
    // Load dữ liệu cần thiết
    movieBus.load("../data/Movies.txt");
    showtimeBus.load("../data/Showtime.txt");
    
    // Giả định người dùng đăng nhập
    currentUserId = "Guest_01"; 
}

void TicketUI::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void TicketUI::printHeader(string title) {
    cout << "\n" << BLUE << "==========================================" << RESET << endl;
    cout << "   " << YELLOW << title << RESET << endl;
    cout << BLUE << "==========================================" << RESET << endl;
}

// [CẬP NHẬT] Thêm showtimeId để vẽ đúng trạng thái ghế của suất đó
void TicketUI::drawSeatMap(string showtimeId, string roomId) {
    // Gọi hàm mới: getSeatsByShowtime
    vector<SeatDisplay> seats = seatBus.getSeatsByShowtime(showtimeId, roomId);
    
    cout << "\n\t" << CYAN << "--- SO DO PHONG CHIEU: " << roomId << " (Suat: " << showtimeId << ") ---" << RESET << "\n";
    cout << "\n\t      ___________________________________";
    cout << "\n\t     |             MAN HINH              |";
    cout << "\n\t      ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n\n";

    if (seats.empty()) {
        cout << RED << "\t(!) Khong tim thay du lieu ghe." << RESET << endl;
        return;
    }

    string currentRow = "";
    for (const auto& s : seats) {
        // Xuống dòng và in giá tiền khi qua hàng mới
        if (s.row != currentRow) {
            if (currentRow != "") cout << "\n\n";
            currentRow = s.row;
            
            // [CẬP NHẬT] Truyền showtimeId để lấy giá tiền
            long long price = seatBus.getSeatPrice(showtimeId, roomId, s.id);
            // In: Hang A (50000d) |
            cout << "\t" << currentRow << YELLOW << " (" << price/1000 << "k)" << RESET << " | ";
        }

        if (s.isBooked) {
            cout << RED << "[XX]" << RESET << " ";
        } else {
            cout << GREEN << "[" << setw(2) << s.id << "]" << RESET << " ";
        }
    }
    cout << "\n\n\t" << GREEN << "[  ] Ghe Trong" << RESET << " | " << RED << "[XX] Da Dat" << RESET << endl;
}

void TicketUI::viewMovies() {
    printHeader("DANH SACH PHIM DANG CHIEU");
    vector<Movie> movies = movieBus.getAll(); 

    if (movies.empty()) {
        cout << "(!) Chua co phim nao trong he thong.\n";
        return;
    }

    cout << left << setw(10) << "ID" << setw(30) << "Ten Phim" << setw(15) << "Thoi luong" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (const auto& m : movies) {
        cout << left << setw(10) << m.getId() 
             << setw(30) << m.getTitle() 
             << setw(15) << m.getDuration() << endl;
    }
}

void TicketUI::processBookingWorkflow() {
    // 1. CHỌN PHIM
    viewMovies();
    string movieId;
    cout << "\n>> Nhap ID Phim muon xem (hoac '0' de quay lai): ";
    cin >> movieId;
    if (movieId == "0") return;

    // 2. CHỌN SUẤT CHIẾU
    vector<Showtime> shows = showtimeBus.getByMovieId(movieId); 
    if (shows.empty()) {
        cout << RED << "(!) Phim nay hien chua co suat chieu nao." << RESET << endl;
        cout << "(An Enter de quay lai...)"; cin.ignore(); cin.get();
        return;
    }

    printHeader("CHON SUAT CHIEU");
    cout << left << setw(10) << "ID" << setw(20) << "Thoi gian" << setw(10) << "Phong" << endl;
    for (const auto& s : shows) {
        cout << left << setw(10) << s.getId() 
             << setw(20) << s.getStartTime() 
             << setw(10) << s.getRoom() << endl;
    }

    string showtimeId;
    cout << "\n>> Nhap ID Suat chieu: ";
    cin >> showtimeId;

    // Tìm thông tin suất chiếu để lấy RoomID
    Showtime* selectedShow = showtimeBus.findById(showtimeId);
    if (selectedShow == nullptr) {
        cout << RED << "(!) Ma suat chieu khong hop le!" << RESET << endl;
        return;
    }
    string roomId = selectedShow->getRoom();

    // 3. CHỌN GHẾ (NHIỀU GHẾ)
    clearScreen();
    drawSeatMap(showtimeId, roomId);

    int qty;
    cout << "\n>> Ban muon dat bao nhieu ve? ";
    
    // --- BẮT ĐẦU VALIDATION NHẬP SỐ LƯỢNG ---
    while (true) {
        cin >> qty;
        if (cin.fail()) {
            cout << "     [!] Loi: Vui long chi nhap so nguyen. Nhap lai: ";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (qty <= 0) {
            cout << "     [!] Loi: So luong phai lon hon 0. Nhap lai: ";
        } else {
            cin.ignore(10000, '\n'); // Xóa enter thừa
            break; // Nhập đúng thì thoát
        }
    }
    // --- KẾT THÚC VALIDATION ---

    vector<string> selectedSeats;
    long long tempTotalPrice = 0;

    for (int i = 0; i < qty; i++) {
        string s;
        cout << "   - Nhap ma ghe thu " << (i + 1) << " (VD: A" << (i + 1) << "): ";
        cin >> s;

        // --- VALIDATION 1: Kiểm tra trùng lặp trong danh sách đang chọn ---
        // (Ví dụ: Đã chọn A1 rồi, giờ nhập lại A1 tiếp)
        bool isDuplicate = false;
        for (const string& seat : selectedSeats) {
            if (seat == s) {
                isDuplicate = true;
                break;
            }
        }
        if (isDuplicate) {
            cout << "     [!] Ban da chon ghe nay roi. Vui long chon ghe khac!\n";
            i--; // Lùi lại 1 bước để nhập lại
            continue;
        }

        // --- VALIDATION 2: Kiểm tra ghế có hợp lệ (Tồn tại & Chưa đặt) ---
        // Gọi xuống BUS để check. Giả sử BUS bạn có hàm isSeatAvailable
        // Nếu BUS chưa có, hãy xem phần gợi ý bên dưới để thêm vào.
        bool seatExistsAndAvailable = seatBus.checkAvailable(showtimeId, roomId, s);
        if (!seatExistsAndAvailable) {
            cout << "     [!] Ghe khong ton tai hoac da duoc dat (" << s << "). Vui long nhap lai!\n";
            i--; // Lùi lại 1 bước
            continue;
        }

        // --- VALIDATION 3: Lấy giá tiền ---
        long long p = seatBus.getSeatPrice(showtimeId, roomId, s);
        if (p <= 0) {
            // Nếu giá = 0 nghĩa là dữ liệu ghế bị lỗi
            cout << "     [!] Loi du lieu gia ve. Vui long chon ghe khac!\n";
            i--;
            continue;
        }

        // Nếu mọi thứ OK
        selectedSeats.push_back(s);
        tempTotalPrice += p;
        cout << "     -> Da them: " << s << " | Gia: " << p << " VND\n";
    }

    cout << "\nTong tien du kien: " << YELLOW << tempTotalPrice << " VND" << RESET << endl;
    cout << "Xac nhan dat " << qty << " ve nay? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        // Gọi hàm xử lý danh sách
        bookingFacade.processBooking(currentUserId, showtimeId, selectedSeats);
    } else {
        cout << "\nDa huy thao tac." << endl;
    }

    cout << "(An Enter de tiep tuc...)"; cin.ignore(); cin.get();
}

// Triển khai logic Hủy vé
void TicketUI::processCancelWorkflow() {
    printHeader("HUY VE DA DAT");
    string ticketId;

    cout << ">> Nhap Ma Ve can huy (VD: TKT1234): ";
    cin >> ticketId;

    // Xác nhận
    cout << "Ban co chac chan muon huy ve " << YELLOW << ticketId << RESET << "? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "\nDa huy thao tac." << endl;
        cout << "(An Enter de quay lai...)"; cin.ignore(); cin.get();
        return;
    }

    // GỌI FACADE ĐỂ XỬ LÝ (Cần thêm hàm này vào Facade)
    // Hàm này sẽ trả về chuỗi thông báo lỗi/thành công để in ra
    string resultMsg = "";
    bool success = bookingFacade.cancelTicket(ticketId, resultMsg);

    if (success) {
        cout << "\n" << GREEN << "(!) THANH CONG: " << resultMsg << RESET << endl;
    } else {
        cout << "\n" << RED << "(!) THAT BAI: " << resultMsg << RESET << endl;
    }

    cout << "(An Enter de quay lai...)"; cin.ignore(); cin.get();
}

void TicketUI::run() {
    int choice;
    while (true) {
        clearScreen();
        printHeader("HE THONG DAT VE XEM PHIM (DEMO)");
        cout << "1. Xem danh sach phim" << endl;
        cout << "2. Dat ve xem phim (Booking)" << endl;
        cout << "3. Huy ve da dat (Cancel Ticket)" << endl; // <--- Sửa dòng này
        cout << "0. Thoat" << endl;
        cout << "------------------------------------------" << endl;
        cout << ">> Nhap lua chon: ";
        
        
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n'); continue;
        }

        switch (choice) {
            case 1: 
                clearScreen();
                viewMovies(); 
                cout << "\n(An Enter de quay lai...)"; cin.ignore(); cin.get();
                break;
            case 2: 
                processBookingWorkflow(); 
                break;
            case 3: 
                processCancelWorkflow(); 
                break;
            case 0: 
                cout << "Tam biet!" << endl; 
                return;
            default: 
                cout << "Lua chon khong hop le!" << endl;
        }
    }
}