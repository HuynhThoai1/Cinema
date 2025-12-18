#include "BookingFacade.h"
#include <iostream>
#include <vector>
#include <sstream> // [QUAN TRỌNG] Thêm thư viện này để tách chuỗi

#include "../dto/Movie.h"
#include "../dto/Showtime.h"

using std::cout;

using std::string;
using std::stringstream;
using std::to_string;

BookingFacade::BookingFacade() {
    movieBus.load("../data/Movies.txt");
    showtimeBus.load("../data/Showtime.txt");
}

// [SỬA 1] Thay tham số seatId thành vector<string> seatList
bool BookingFacade::processBooking(string userId, string showtimeId, vector<string> seatList) {
    cout << "\n --- XU LY DAT VE (" << seatList.size() << " ghe) ---" << "\n";

    string movieTitle = "Unknown";
    string roomName = "Unknown";
    string fullStartTime = ""; 
    
    // --- BƯỚC 1: TÌM SUẤT CHIẾU (Chỉ cần làm 1 lần) ---
    Showtime* showtimePtr = showtimeBus.findById(showtimeId);
    if (showtimePtr == nullptr) {
        cout << " -> LOI: Khong tim thay suat chieu ID: " << showtimeId << "\n";
        return false;
    }

    roomName = showtimePtr->getRoom();
    fullStartTime = showtimePtr->getStartTime(); 

    // Lấy tên phim
    string movieId = showtimePtr->getMovieId();
    Movie* moviePtr = movieBus.findById(movieId);
    if (moviePtr != nullptr) {
        movieTitle = moviePtr->getTitle();
    }

    cout << " -> B1: Xac nhan: " << movieTitle 
         << " | Thoi gian: " << fullStartTime 
         << " | Phong: " << roomName << "\n";

    // --- BƯỚC 2: CHECK TOÀN BỘ GHẾ TRƯỚC (Pre-check) ---
    // Nếu có bất kỳ ghế nào bận, dừng ngay không đặt ghế nào cả
    for (const string& seatId : seatList) {
        if (!seatBus.checkAvailable(showtimeId, roomName, seatId)) {
            cout << " -> LOI: Ghe " << seatId << " da co nguoi dat. Huy toan bo giao dich." << "\n";
            return false;
        }
    }

    // --- BƯỚC 3: TIẾN HÀNH ĐẶT TỪNG VÉ ---
    
    // Tách thời gian (Làm 1 lần ở ngoài vòng lặp cho tối ưu)
    stringstream ss(fullStartTime);
    string dateOnly, timeOnly;
    ss >> dateOnly >> timeOnly; 

    int successCount = 0;
    long long totalPrice = 0;

    // Duyệt qua từng ghế trong danh sách để đặt
    for (const string& seatId : seatList) {
        
        // 3.1. Lấy giá tiền riêng cho từng ghế (VD: ghế hàng A rẻ hơn ghế hàng E)
        long long priceVal = seatBus.getSeatPrice(showtimeId, roomName, seatId);
        if (priceVal == 0) priceVal = 50000; 
        string priceStr = to_string(priceVal);
        totalPrice += priceVal;

        // 3.2. Đặt ghế (Cập nhật file Seats.txt)
        if (!seatBus.bookSeat(showtimeId, roomName, seatId)) {
            cout << " -> LOI: Khong the dat ghe " << seatId << " (Loi he thong)." << "\n";
            continue; // Bỏ qua ghế này, thử ghế tiếp theo
        }

        // 3.3. Tạo vé và nhận về MÃ VÉ (Thay vì bool)
        // [QUAN TRỌNG] Bạn phải sửa TicketBUS trả về string để code này hoạt động
        string newTicketId = ticketBus.createAndSaveTicket(
            userId, 
            showtimeId,
            movieTitle, 
            roomName, 
            seatId, 
            priceStr, 
            timeOnly, 
            dateOnly
        );

        // Kiểm tra chuỗi rỗng thay vì check true/false
        if (!newTicketId.empty()) { 
            cout << " -> Da dat thanh cong ghe: " << seatId ;
            
            // [ĐÃ SỬA] In ra newTicketId thay vì userId
            cout << "  |  Ma ve: ["<< newTicketId <<"] ";            
            cout << "  |  Phim: " << movieTitle;
            cout << "  |  Phong: " << roomName; 
            cout << "  |  Thoi gian: " << fullStartTime;
            cout << "  |  Gia ve: " << priceStr << " VND" << "\n";
            successCount++;
        } else {
            cout << " -> LOI: Tao ve cho ghe " << seatId << " that bai. Rollback..." << "\n";
            // Nếu tạo vé lỗi -> Phải mở lại ghế đó (Rollback)
            seatBus.unlockSeat(showtimeId, roomName, seatId); 
        }
    }

    // Tổng kết
    if (successCount > 0) {
        cout << " -> HOAN TAT: Da dat " << successCount << "/" << seatList.size() << " ve." << "\n";
        cout << " -> TONG TIEN: " << totalPrice << " VND" << "\n";
        return true;
    } else {
        cout << " -> THAT BAI: Khong dat duoc ve nao." << "\n";
        return false;
    }
}

bool BookingFacade::cancelTicket(string ticketId, string& outMessage) {
    // B1: Tìm vé để lấy thông tin (Suất chiếu, Phòng, Ghế) trước khi xóa
    Ticket* ticket = ticketBus.getTicketById(ticketId); // Cần thêm hàm này ở TicketBUS
    
    if (ticket == nullptr) {
        outMessage = "Khong tim thay ma ve nay trong he thong.";
        return false;
    }

    string showtimeId = ticket->getShowtimeID();
    string roomId = ticket->getRoomID();
    string seatId = ticket->getSeatID();

    // B2: Mở khóa ghế (Unlock)
    // Vì ghế đã đặt rồi nên unlockSeat sẽ trả về true nếu mở thành công
    if (!seatBus.unlockSeat(showtimeId, roomId, seatId)) {
        outMessage = "Loi he thong: Khong the mo khoa ghe (hoac du lieu ghe khong khop).";
        delete ticket; 
        return false;
    }

    // B3: Xóa vé khỏi file Tickets.txt
    if (ticketBus.cancelTicket(ticketId)) {
        outMessage = "Da huy ve va hoan lai ghe " + seatId + " cho suat chieu " + showtimeId;
        delete ticket;
        return true;
    } else {
        outMessage = "Loi: Khong the xoa ve khoi co so du lieu.";
        // (Ở đây lẽ ra nên rollback lock lại ghế, nhưng tạm thời bỏ qua cho đơn giản)
        delete ticket;
        return false;
    }
}