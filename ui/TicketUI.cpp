#include "TicketUI.h"
#include <iostream>
#include <iomanip>
#include <cstdlib> // system("cls")
#include <cctype>  // isalpha, isdigit, toupper
#include <algorithm> // transform

using namespace std;

// --- CẤU HÌNH MÀU SẮC ANSI ---
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

// --- HÀM HỖ TRỢ KIỂM TRA ĐỊNH DẠNG (FIX LỖI NHẬP "ad") ---
bool isValidSeatFormat(const string& s) {
    if (s.length() < 2) return false; // Quá ngắn (VD: "A")
    if (!isalpha(s[0])) return false; // Ký tự đầu phải là chữ (VD: "1A" là sai)
    
    // Các ký tự phía sau phải là số
    for (size_t i = 1; i < s.length(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

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

void TicketUI::drawSeatMap(string showtimeId, string roomId) {
    vector<SeatDisplay> seats = seatBus.getSeatsByShowtime(showtimeId, roomId);
    
    cout << "\n\t" << CYAN << "--- SO DO PHONG CHIEU: " << roomId << " (Suat: " << showtimeId << ") ---" << RESET << "\n";
    cout << "\n\t       ___________________________________";
    cout << "\n\t      |            MAN HINH               |";
    cout << "\n\t       ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n\n";

    if (seats.empty()) {
        cout << RED << "\t(!) Khong tim thay du lieu ghe." << RESET << endl;
        return;
    }

    string currentRow = "";
    for (const auto& s : seats) {
        if (s.row != currentRow) {
            if (currentRow != "") cout << "\n\n";
            currentRow = s.row;
            long long price = seatBus.getSeatPrice(showtimeId, roomId, s.id);
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

// Vẫn giữ hàm này để hiển thị khi người dùng vào quy trình đặt vé
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
    
    // VALIDATION NHẬP SỐ LƯỢNG (Code cũ giữ nguyên)
    while (true) {
        cin >> qty;
        if (cin.fail()) {
            cout << "     [!] Loi: Vui long chi nhap so nguyen. Nhap lai: ";
            cin.clear(); cin.ignore(10000, '\n');
        } else if (qty <= 0 || qty > 50) { // Giả sử max là 50
            cout << "     [!] Loi: So luong phai > 0 va <= 50. Nhap lai: ";
        } else {
            cin.ignore(10000, '\n'); // Xóa enter thừa
            break;
        }
    }

    vector<string> selectedSeats;
    // [THÊM MỚI] Vector lưu loại vé song song với ghế
    vector<string> selectedTypes; 
    
    long long tempTotalPrice = 0;

    for (int i = 0; i < qty; i++) {
        string s;
        cout << "   - Nhap ma ghe thu " << (i + 1) << " (VD: A" << (i + 1) << "): ";
        cin >> s;

        // --- BƯỚC 1: KIỂM TRA ĐỊNH DẠNG (Code cũ giữ nguyên) ---
        if (!isValidSeatFormat(s)) {
             cout << RED << "     [!] Loi: Dinh dang ghe sai! (VD dung: A1, B12). Nhap lai!\n" << RESET;
             i--; continue;
        }

        // --- BƯỚC 2: CHUẨN HÓA (Code cũ giữ nguyên) ---
        s[0] = toupper(s[0]); 

        // --- BƯỚC 3: KIỂM TRA TRÙNG LẶP (Code cũ giữ nguyên) ---
        bool isDuplicate = false;
        for (const string& seat : selectedSeats) {
            if (seat == s) { isDuplicate = true; break; }
        }
        if (isDuplicate) {
            cout << YELLOW << "     [!] Ghe nay da duoc ban chon roi. Chon ghe khac!\n" << RESET;
            i--; continue;
        }

        // --- BƯỚC 4: KIỂM TRA TỒN TẠI & TRẠNG THÁI (Code cũ giữ nguyên) ---
        bool seatAvailable = seatBus.checkAvailable(showtimeId, roomId, s);
        long long p = seatBus.getSeatPrice(showtimeId, roomId, s); // Đây là giá gốc

        if (!seatAvailable) {
            cout << RED << "     [!] Ghe " << s << " khong ton tai hoac da duoc dat. Vui long chon ghe khac!\n" << RESET;
            i--; continue;
        }

        if (p <= 0) {
             cout << RED << "     [!] Loi du lieu ghe " << s << ". Vui long chon ghe khac!\n" << RESET;
             i--; continue;
        }

        // --- [THÊM MỚI] BƯỚC 4.5: CHỌN LOẠI VÉ CHO GHẾ NÀY ---
        cout << "     Loai ve cho ghe " << s << "? (1.NguoiLon, 2.TreEm-50%, 3.SinhVien-20%): ";
        int typeChoice;
        // Validate nhập số đơn giản
        if(!(cin >> typeChoice)) { 
            cin.clear(); cin.ignore(1000, '\n'); 
            typeChoice = 1; // Mặc định nếu nhập sai
        }
        
        string typeStr = "ADULT";
        long long finalPrice = p; // Giá hiển thị tạm tính

        if (typeChoice == 2) {
            typeStr = "CHILD";
            finalPrice = p * 0.5;
        } else if (typeChoice == 3) {
            typeStr = "STUDENT";
            finalPrice = p * 0.8;
        }

        // --- THÀNH CÔNG (Cập nhật danh sách) ---
        selectedSeats.push_back(s);
        
        // [THÊM MỚI] Lưu loại vé vào danh sách
        selectedTypes.push_back(typeStr); 

        // [SỬA] Cộng giá đã giảm vào tổng tiền hiển thị (thay vì giá gốc p)
        tempTotalPrice += finalPrice;
        
        cout << "     -> Da them: " << GREEN << s << RESET 
             << " (" << typeStr << ")" // In thêm loại vé cho user biết
             << " | Gia: " << finalPrice << " VND\n";
    }

    cout << "\nTong tien du kien: " << YELLOW << tempTotalPrice << " VND" << RESET << endl;
    cout << "Xac nhan dat " << qty << " ve nay? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        // [SỬA] Truyền thêm tham số selectedTypes vào Facade
        // (Đây là chỗ bắt buộc phải sửa vì hàm bên kia đã thay đổi)
        bookingFacade.processBooking(currentUserId, showtimeId, selectedSeats, selectedTypes);
    } else {
        cout << "\nDa huy thao tac." << endl;
    }

    cout << "(An Enter de tiep tuc...)"; cin.ignore(); cin.get();
}

void TicketUI::processCancelWorkflow() {
    printHeader("HUY VE DA DAT");
    string ticketId;

    cout << ">> Nhap Ma Ve can huy (VD: TKT123456789): ";
    cin >> ticketId;

    cout << "Ban co chac chan muon huy ve " << YELLOW << ticketId << RESET << "? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "\nDa huy thao tac." << endl;
        cout << "(An Enter de quay lai...)"; cin.ignore(); cin.get();
        return;
    }

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
        
        // --- MENU ĐÃ ĐƯỢC RÚT GỌN ---
        cout << "1. Dat ve xem phim (Booking)" << endl;
        cout << "2. Huy ve da dat (Cancel Ticket)" << endl;
        cout << "0. Thoat" << endl;
        
        cout << "------------------------------------------" << endl;
        cout << ">> Nhap lua chon: ";
        
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n'); continue;
        }

        switch (choice) {
            case 1: 
                // Không cần clearScreen ở đây vì trong hàm Booking đã có rồi
                processBookingWorkflow(); 
                break;
            case 2: 
                clearScreen(); // Cancel cần clear màn hình cho sạch
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