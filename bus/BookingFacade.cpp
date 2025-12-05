#include "BookingFacade.h"
#include <iostream>
#include <vector>

// Đảm bảo include các DTO
#include "../dto/Movie.h"
#include "../dto/Showtime.h"

using std::cout;
using std::vector;


BookingFacade::BookingFacade() {
    // Constructor
}

bool BookingFacade::processBooking(string userId, string showtimeId, string seatId) {
    cout << "\n[BookingFacade] --- XU LY DAT VE ---" << "\n";

    // =============================================================
    // BƯỚC 1: KIỂM TRA & GIỮ GHẾ (SEAT BUS)
    // =============================================================
    if (!seatBus.checkAvailable(seatId)) {
        cout << " -> LOI: Ghe " << seatId << " khong kha dung." << "\n";
        return false;
    }

    if (!seatBus.bookSeat(seatId)) {
        cout << " -> LOI: Khong the cap nhat trang thai ghe." << "\n";
        return false;
    }
    cout << " -> B1: Ghe " << seatId << " da duoc giu." << "\n";

    // =============================================================
    // BƯỚC 2: TÌM KIẾM DỮ LIỆU (SHOWTIME & MOVIE BUS)
    // =============================================================
    /* Vấn đề: ShowtimeBUS chỉ cho tìm theo Phim (getByMovie).
       Giải pháp: Phải lấy hết Phim, sau đó duyệt từng phim để tìm ra suất chiếu ID trùng khớp.
    */

    string movieTitle = "Unknown";
    string roomName = "Unknown";
    string price = "50000"; 
    string time = "";
    string date = "";
    
    bool foundInfo = false;

    // 1. Lấy danh sách tất cả các phim đang có (MovieBUS cần có hàm này theo diagram)
    vector<Movie> allMovies = movieBus.getAllMovies();

    // 2. Duyệt qua từng phim để tìm suất chiếu
    for (const auto& movie : allMovies) {
        // Lấy danh sách suất chiếu của phim này
        vector<Showtime> shows = showtimeBus.getByMovie(movie.getId());

        // Duyệt danh sách suất chiếu để tìm ID khớp với khách chọn
        for (const auto& s : shows) {
            if (s.getId() == showtimeId) {
                // ==> ĐÃ TÌM THẤY SUẤT CHIẾU!
                
                // Lấy dữ liệu cần thiết
                movieTitle = movie.getTitle(); // Lấy ngay từ vòng lặp phim
                roomName = s.getRoom();
                time = s.getStartTime();
                // date = s.getDate(); // Nếu có
                
                foundInfo = true;
                break; // Thoát vòng lặp suất chiếu
            }
        }
        if (foundInfo) break; // Thoát vòng lặp phim
    }

    if (!foundInfo) {
        cout << " -> LOI: Khong tim thay thong tin suat chieu ID: " << showtimeId << "\n";
        
        // Quan trọng: Phải mở khóa ghế vì đặt vé thất bại
        // seatBus.unlockSeat(seatId); 
        return false;
    }

    cout << " -> B2: Tim thay phim: " << movieTitle << " | Phong: " << roomName << "\n";

    // =============================================================
    // BƯỚC 3: TẠO VÀ LƯU VÉ (TICKET BUS)
    // =============================================================
    
    bool ticketSuccess = ticketBus.createAndSaveTicket(
        userId,       
        movieTitle,
        roomName,
        seatId,
        price,
        time,
        date
    );

    if (ticketSuccess) {
        cout << " -> B3: Luu ve thanh cong." << "\n";
        cout << "[BookingFacade] THANH CONG!" << "\n";
        return true;
    } else {
        // =========================================================
        // BƯỚC 4: ROLLBACK
        // =========================================================
        cout << " -> LOI: Luu ve that bai. Hoan tac ghe..." << "\n";
        // seatBus.unlockSeat(seatId); 
        return false;
    }
}