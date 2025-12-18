#ifndef TICKET_UI_H
#define TICKET_UI_H

#include "../bus/BookingFacade.h"
#include "../bus/MovieBUS.h"
#include "../bus/ShowtimeBUS.h"
#include "../bus/SeatBUS.h"
#include <string>

using std::string;

/**
 * @class TicketUI
 * @brief Lớp giao diện Console tương tác với người dùng.
 */
class TicketUI {
private:
    // Các đối tượng xử lý nghiệp vụ
    BookingFacade bookingFacade;
    MovieBUS movieBus;
    ShowtimeBUS showtimeBus;
    SeatBUS seatBus; // Cần để vẽ map và unlock ghế thủ công

    // Thông tin người dùng hiện tại (Giả lập session)
    string currentUserId;

public:
    TicketUI();

    /**
     * @brief Hàm chạy chính của chương trình (Vòng lặp menu).
     */
    void run();

private:
    // --- CÁC MÀN HÌNH CHỨC NĂNG ---
    
    // Hiển thị danh sách phim đang chiếu
    void viewMovies();
    
    // Quy trình đặt vé: Chọn Phim -> Chọn Suất -> Chọn Ghế -> Thanh toán
    void processBookingWorkflow();
    
    // Hủy vé (Mở khóa ghế - Tính năng cho Admin/Testing)
    void processCancelWorkflow();

    // --- HÀM HỖ TRỢ HIỂN THỊ ---
    
    // Vẽ sơ đồ ghế của một phòng cụ thể
    void drawSeatMap(string showtimeId, string roomId);
    
    // Xóa màn hình console
    void clearScreen();
    
    // In tiêu đề đẹp
    void printHeader(string title);
};

#endif // TICKET_UI_H