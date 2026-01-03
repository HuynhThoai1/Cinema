#include "TicketUI.h"
#include <iostream>
#include <iomanip>
#include <cstdlib> // system("cls")
#include <cctype>  // isalpha, isdigit, toupper
#include <algorithm> // transform
#include "../utils/FormatUI.h"

using namespace std;

// color macros and helpers are provided by utils/FormatUI.h

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

TicketUI::TicketUI() 
{
    // 1. movieBus tự gọi MovieBUS() -> tự gọi MovieDAL() -> tự lấy "data/Movies.txt"
    // 2. showtimeBus tự gọi ShowtimeBUS() -> tự lấy "data/Showtime.txt"
    // 3. seatBus của bạn đã tự lấy "data/Seats.txt" từ trước
    // => KHÔNG CẦN VIẾT GÌ CẢ!
    
    currentUserId = "";
}
// [THÊM MỚI]
void TicketUI::setCurrentUser(string userId) {
    this->currentUserId = userId;
}
void TicketUI::clearScreen() {
    ::clearScreen();
}

void TicketUI::printHeader(string title) {
    ::printHeader(title);
}

void TicketUI::drawSeatMap(string showtimeId, string roomId) {
    vector<SeatDisplay> seats = seatBus.getSeatsByShowtime(showtimeId, roomId);
    
    cout << "\n\t" << CYAN << "--- SƠ ĐỒ PHÒNG CHIẾU: " << roomId << " (Suất: " << showtimeId << ") ---" << RESET << "\n";
    cout << "\n\t       ___________________________________";
    cout << "\n\t      |            MÀN HÌNH               |";
    cout << "\n\t       ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n\n";

    if (seats.empty()) {
        cout << RED << "\t(!) Không tìm thấy dữ liệu ghế." << RESET << endl;
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
    cout << "\n\n\t" << GREEN << "[  ] Ghế Trống" << RESET << " | " << RED << "[XX] Đã Đặt" << RESET << endl;
}

// Vẫn giữ hàm này để hiển thị khi người dùng vào quy trình đặt vé
void TicketUI::viewMovies() {
    printHeader("DANH SÁCH PHIM ĐANG CHIẾU");
    vector<Movie> movies = movieBus.getAll(); 

    if (movies.empty()) {
        cout << "(!) Chưa có phim nào trong hệ thống.\n";
        return;
    }

    cout << left << setw(10) << "ID" << setw(30) << "Tên Phim" << setw(15) << "Thời lượng" << endl;
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
    cout << "\n>> Nhập ID Phim muốn xem (hoặc '0' để quay lại): ";
    cin >> movieId;
    if (movieId == "0") return;

    // 2. CHỌN SUẤT CHIẾU
    vector<Showtime> shows = showtimeBus.getByMovie(movieId); 
    if (shows.empty()) {
        cout << RED << "(!) Phim này hiện chưa có suất chiếu nào." << RESET << endl;
        cout << "(Ấn Enter để quay lại...)"; cin.ignore(); cin.get();
        return;
    }

    printHeader("CHỌN SUẤT CHIẾU");
    cout << left << setw(10) << "ID" << setw(20) << "Thời gian" << setw(10) << "Phòng" << endl;
    for (const auto& s : shows) {
        cout << left << setw(10) << s.getId() 
             << setw(20) << s.getStartTime() 
             << setw(10) << s.getRoom() << endl;
    }

    string showtimeId;
    cout << "\n>> Nhập ID Suất chiếu: ";
    cin >> showtimeId;

    Showtime* selectedShow = showtimeBus.findById(showtimeId);
    if (selectedShow == nullptr) {
        cout << RED << "(!) Mã suất chiếu không hợp lệ!" << RESET << endl;
        return;
    }
    string roomId = selectedShow->getRoom();

    // 3. CHỌN GHẾ (NHIỀU GHẾ)
    clearScreen();
    drawSeatMap(showtimeId, roomId);

    int qty;
    cout << "\n>> Bạn muốn đặt bao nhiêu vé? ";
    
    // VALIDATION NHẬP SỐ LƯỢNG (Code cũ giữ nguyên)
    while (true) {
        cin >> qty;
        if (cin.fail()) {
            cout << "     [!] Lỗi: Vui lòng chỉ nhập số nguyên. Nhập lại: ";
            cin.clear(); cin.ignore(10000, '\n');
        } else if (qty <= 0 || qty > 50) { // Giả sử max là 50
            cout << "     [!] Lỗi: Số lượng phải > 0 và <= 50. Nhập lại: ";
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
        cout << "   - Nhập mã ghế thứ " << (i + 1) << " (VD: A" << (i + 1) << "): ";
        cin >> s;

        // --- BƯỚC 1: KIỂM TRA ĐỊNH DẠNG (Code cũ giữ nguyên) ---
        if (!isValidSeatFormat(s)) {
             cout << RED << "     [!] Lỗi: Định dạng ghế sai! (VD đúng: A1, B12). Nhập lại!\n" << RESET;
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
            cout << YELLOW << "     [!] Ghế này đã được bạn chọn rồi. Chọn ghế khác!\n" << RESET;
            i--; continue;
        }

        // --- BƯỚC 4: KIỂM TRA TỒN TẠI & TRẠNG THÁI (Code cũ giữ nguyên) ---
        bool seatAvailable = seatBus.checkAvailable(showtimeId, roomId, s);
        long long p = seatBus.getSeatPrice(showtimeId, roomId, s); // Đây là giá gốc
        if (!BUSUtils::isValidSeatId(s)) {
            cout << RED << "     [!] Ghế " << s << " không tồn tại trong phòng " << roomId << ". Vui lòng chọn ghế khác!\n" << RESET;
            i--; continue;
        }
        if (!seatAvailable) {
            cout << RED << "     [!] Ghế " << s << " không tồn tại hoặc đã được đặt. Vui lòng chọn ghế khác!\n" << RESET;
            i--; continue;
        }

        if (p <= 0) {
             cout << RED << "     [!] Lỗi dữ liệu ghế " << s << ". Vui lòng chọn ghế khác!\n" << RESET;
             i--; continue;
        }

        // --- [THÊM MỚI] BƯỚC 4.5: CHỌN LOẠI VÉ CHO GHẾ NÀY ---
        cout << "     Loại vé cho ghế " << s << "? (1.NgườiLớn, 2.TrẻÊm-50%, 3.SinhViên-20%): ";
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
        
        cout << "     -> Đã thêm: " << GREEN << s << RESET 
             << " (" << typeStr << ")" // In thêm loại vé cho user biết
             << " | Giá: " << finalPrice << " VND\n";
    }

    cout << "\nTổng tiền dự kiến: " << YELLOW << tempTotalPrice << " VND" << RESET << endl;
    cout << "Xác nhận đặt " << qty << " vé này? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        // [SỬA] Truyền thêm tham số selectedTypes vào Facade
        // (Đây là chỗ bắt buộc phải sửa vì hàm bên kia đã thay đổi)
        bookingFacade.processBooking(currentUserId, showtimeId, selectedSeats, selectedTypes);
    } else {
        cout << "\nĐã hủy thao tác." << endl;
    }

    cout << "(Ấn Enter để tiếp tục...)"; cin.ignore(); cin.get();
}

void TicketUI::processCancelWorkflow() {
    printHeader("HỦY VÉ ĐÃ ĐẶT");
    string ticketId;

    cout << ">> Nhập Mã Vé cần hủy (VD: TKT123456789): ";
    cin >> ticketId;

    cout << "Bạn có chắc chắn muốn hủy vé " << YELLOW << ticketId << RESET << "? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "\nĐã hủy thao tác." << endl;
        cout << "(Ấn Enter để quay lại...)"; cin.ignore(); cin.get();
        return;
    }

    string resultMsg = "";
    bool success = bookingFacade.cancelTicket(ticketId, resultMsg);

    if (success) {
        cout << "\n" << GREEN << "(!) THÀNH CÔNG: " << resultMsg << RESET << endl;
    } else {
        cout << "\n" << RED << "(!) THẤT BẠI: " << resultMsg << RESET << endl;
    }

    cout << "(Ấn Enter để quay lại...)"; cin.ignore(); cin.get();
}

void TicketUI::run() {
    int choice;
    while (true) {
        clearScreen();
        printHeader("ĐẶT VÉ & HỦY VÉ");
        
        cout << CYAN << "1. Đặt vé xem phim" << RESET << "\n";
        cout << CYAN << "2. Hủy vé đã đặt" << RESET << "\n";
        cout << CYAN << "0. Quay lại" << RESET << "\n";
        cout << "------------------------------------------\n";
        cout << "Chọn: ";
        
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n'); 
            cout << RED << ">> lựa chọn không hợp lệ!" << RESET << "\n";
            cout << "(Ấn Enter để tiếp tục...)"; cin.get();
            continue;
        }

        switch (choice) {
            case 1: 
                processBookingWorkflow(); 
                break;
            case 2: 
                clearScreen();
                processCancelWorkflow(); 
                break;
            case 0: 
                return;
            default: 
                cout << RED << ">> lựa chọn không hợp lệ!" << RESET << "\n";
                cout << "(Ấn Enter để tiếp tục...)"; cin.ignore(); cin.get();
                break;
        }
    }
}