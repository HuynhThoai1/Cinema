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
    movieBus.load(DATA_PATH("Movies.txt"));
    showtimeBus.load(DATA_PATH("Showtime.txt"));
}


bool BookingFacade::processBooking(string userId, string showtimeId, vector<string> seatList, vector<string> typeList) {
    cout << "\n --- XỬ LÝ ĐẶT VÉ (" << seatList.size() << " ghế) ---" << "\n";

    string movieTitle = "Unknown";
    string roomName = "Unknown";
    string fullStartTime = ""; 
    
    // --- BƯỚC 1: TÌM SUẤT CHIẾU (Chỉ cần làm 1 lần) ---
    Showtime* showtimePtr = showtimeBus.findById(showtimeId);
    if (showtimePtr == nullptr) {
        cout << " -> Lỗi: Không tìm thấy suất chiếu ID: " << showtimeId << "\n";
        return false;
    }

    roomName = showtimePtr->getRoom();
    fullStartTime = showtimePtr->getStartTime(); 

    // Lấy tên phim
    string movieId = showtimePtr->getMovieId();
    std::optional<Movie> optMovie = movieBus.findById(movieId);
    if (optMovie.has_value()) {
        movieTitle = optMovie->getTitle();
    }


    cout << " -> B1: xác nhận: " << movieTitle 
         << " | Thời gian: " << fullStartTime 
         << " | Phòng: " << roomName << "\n";

    // --- BƯỚC 2: CHECK TOÀN BỘ GHẾ TRƯỚC (Pre-check) ---
    for (const string& seatId : seatList) {
        // 🔴 2.1. Check ghế có tồn tại không
        if (!BUSUtils::isValidSeatId(seatId)) {
            cout << " -> Lỗi: Ghế " << seatId << " KHÔNG TỒN TẠI trong phòng " << roomName << "\n";
            return false;
        }
        if (!seatBus.checkAvailable(showtimeId, roomName, seatId)) {
            cout << " -> Lỗi: Ghế " << seatId << " đã có người đặt. Hủy toàn bộ giao dịch." << "\n";
            return false;
        }
    }

    // --- BƯỚC 3: TIẾN HÀNH ĐẶT TỪNG VÉ ---
    
    // Tách thời gian
    stringstream ss(fullStartTime);
    string dateOnly, timeOnly;
    ss >> dateOnly >> timeOnly; 

    int successCount = 0;
    long long totalPrice = 0; // Sẽ lưu tổng giá ĐÃ GIẢM

    // [SỬA] Đổi vòng lặp từ for-each sang for index
    for (size_t i = 0; i < seatList.size(); i++) {
        string seatId = seatList[i];
        
        // Lấy loại vé tương ứng
        string ticketType = "ADULT";
        if (i < typeList.size()) {
            ticketType = typeList[i];
        }

        // 3.1. Lấy giá tiền GỐC
        long long basePrice = seatBus.getSeatPrice(showtimeId, roomName, seatId);
        if (basePrice == 0) basePrice = 50000; 
        
        // [MỚI] TÍNH TOÁN GIÁ THỰC TẾ ĐỂ CỘNG VÀO TỔNG BILL
        long long finalPrice = basePrice;
        if (ticketType == "CHILD") {
            finalPrice = basePrice / 2;       // Giảm 50%
        } else if (ticketType == "STUDENT") {
            finalPrice = (long long)(basePrice * 0.8); // Giảm 20%
        }

        // Cộng giá ĐÃ GIẢM vào tổng tiền thanh toán
        totalPrice += finalPrice;

        string basePriceStr = to_string(basePrice); // Vẫn truyền giá gốc xuống Factory

        // 3.2. Đặt ghế
        if (!seatBus.bookSeat(showtimeId, roomName, seatId)) {
            cout << " -> Lỗi: Không thể đặt ghế " << seatId << " (ỗi hệ thống)." << "\n";
            totalPrice -= finalPrice; // Trừ lại tiền nếu lỗi
            continue; 
        }

        // 3.3. Tạo vé và nhận về MÃ VÉ
        string newTicketId = ticketBus.createAndSaveTicket(
            ticketType,    // Loại vé
            userId, 
            showtimeId,
            movieTitle, 
            roomName, 
            seatId, 
            basePriceStr,  // Truyền giá gốc (Factory tự chia tiền để lưu file)
            timeOnly, 
            dateOnly
        );

        // Kiểm tra chuỗi rỗng
        if (!newTicketId.empty()) { 
            cout << " -> [" << ticketType << "] Da dat thanh cong ghe: " << seatId << "\n";
            cout << "  |  Ma ve:     ["<< newTicketId <<"] "<<"\n";            
            cout << "  |  Phim:       " << movieTitle << "\n"; 
            cout << "  |  Phong:      " << roomName << "\n";
            cout << "  |  Thoi gian:  " << fullStartTime << "\n";
            
            // [SỬA] In ra giá thực tế để người dùng thấy
            cout << "  |  Gia ve:     " << finalPrice << " VND (Goc: " << basePrice << ")" << "\n";
            successCount++;
        } else {
            cout << " -> LOI: Tao ve cho ghe " << seatId << " that bai. Rollback..." << "\n";
            seatBus.unlockSeat(showtimeId, roomName, seatId); 
            totalPrice -= finalPrice; // Trừ lại tiền nếu tạo vé thất bại
        }
    }

    // Tổng kết
    if (successCount > 0) {
        cout << " -> HOAN TAT: Da dat " << successCount << "/" << seatList.size() << " ve." << "\n";
        // [SỬA] In ra label đúng nghĩa
        cout << " -> TONG THANH TOAN: " << totalPrice << " VND" << "\n";
        
        // [MỚI] GHI NHẬN DOANH THU TỰ ĐỘNG
        if (totalPrice > 0) {
            string movieId = showtimePtr->getMovieId();
            string info = "User: " + userId + ", Showtime: " + showtimeId + ", Seats: " + to_string(successCount);
            revenueBus.recordRevenue("TICKET", movieId, (int)totalPrice, info);
            cout << " -> [DOANH THU] Da ghi nhan " << totalPrice << " VND tu ban ve." << "\n";
        }
        
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
        outMessage = "Không tìm thấy mã vé này trong hệ thống.";
        return false;
    }

    string showtimeId = ticket->getShowtimeID();
    string roomId = ticket->getRoomID();
    string seatId = ticket->getSeatID();

    // B2: Mở khóa ghế (Unlock)
    // Vì ghế đã đặt rồi nên unlockSeat sẽ trả về true nếu mở thành công
    if (!seatBus.unlockSeat(showtimeId, roomId, seatId)) {
        outMessage = "Lỗi hệ thống: Không thể mở khóa ghế (hoặc dữ liệu ghế không khớp).";
        delete ticket; 
        return false;
    }

    // B3: Xóa vé khỏi file Tickets.txt
    if (ticketBus.cancelTicket(ticketId)) {
        outMessage = "Đã hủy vé và hoàn lại ghế " + seatId + " cho suất chiếu " + showtimeId;
        delete ticket;
        return true;
    } else {
        outMessage = "Lỗi: Không thể xóa vé khỏi cơ sở dữ liệu.";
        // (Ở đây lẽ ra nên rollback lock lại ghế, nhưng tạm thời bỏ qua cho đơn giản)
        delete ticket;
        return false;
    }
}