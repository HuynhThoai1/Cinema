/**
 * @file TicketUI.h
 * @brief Định nghĩa lớp giao diện người dùng (Console) cho hệ thống đặt vé xem phim.
 * @author YourName
 * @date 2025-12-18
 */

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
 * @brief Lớp giao diện Console tương tác trực tiếp với người dùng.
 * * @details Lớp này đóng vai trò là Presentation Layer (Giao diện). Nhiệm vụ chính:
 * - Hiển thị menu và các thông tin (Phim, Suất chiếu, Sơ đồ ghế).
 * - Nhận input từ bàn phím.
 * - Gọi xuống Business Logic Layer (thông qua Facade hoặc BUS) để xử lý.
 */
class TicketUI {
private:
    /** * @brief Đối tượng Facade để xử lý các nghiệp vụ phức tạp (như transaction đặt vé). 
     */
    BookingFacade bookingFacade;

    /** @brief Service quản lý thông tin phim. */
    MovieBUS movieBus;

    /** @brief Service quản lý thông tin suất chiếu. */
    ShowtimeBUS showtimeBus;

    /** * @brief Service quản lý ghế ngồi. 
     * @note Cần thiết để lấy dữ liệu vẽ sơ đồ (drawSeatMap) và kiểm tra trạng thái ghế.
     */
    SeatBUS seatBus; 

    /** * @brief Mã người dùng hiện tại (Giả lập session đăng nhập). 
     */
    string currentUserId;

public:
    /**
     * @brief Constructor mặc định.
     * @details Khởi tạo các đối tượng BUS, load dữ liệu ban đầu và thiết lập user mặc định.
     */
    TicketUI();

    /**
     * @brief Hàm chạy chính của chương trình.
     * @details Chứa vòng lặp vô hạn hiển thị Menu chính cho đến khi người dùng chọn Thoát.
     */
    void run();
    void setCurrentUser(string userId);
private:
    // --- CÁC MÀN HÌNH CHỨC NĂNG ---
    
    /**
     * @brief Hiển thị danh sách tất cả các phim đang chiếu.
     * @details Lấy dữ liệu từ MovieBUS và in ra màn hình dạng bảng.
     */
    void viewMovies();
    
    /**
     * @brief Thực hiện quy trình đặt vé trọn gói.
     * @details Bao gồm các bước tuần tự:
     * 1. Hiển thị danh sách phim -> Người dùng chọn Phim.
     * 2. Hiển thị các suất chiếu của phim đó -> Người dùng chọn Suất.
     * 3. Hiển thị sơ đồ ghế -> Người dùng nhập các ghế muốn đặt.
     * 4. Tính tiền và gọi BookingFacade để chốt đơn.
     */
    void processBookingWorkflow();
    
    /**
     * @brief Thực hiện quy trình hủy vé.
     * @details Yêu cầu người dùng nhập Mã vé, sau đó gọi Facade để hoàn tác (trả lại trạng thái ghế trống).
     */
    void processCancelWorkflow();

    // --- HÀM HỖ TRỢ HIỂN THỊ (HELPER) ---
    
    /**
     * @brief Vẽ trực quan sơ đồ ghế của phòng chiếu lên màn hình console.
     * * @param showtimeId Mã suất chiếu (để xác định trạng thái ghế booked/available trong suất đó).
     * @param roomId Mã phòng chiếu (để xác định cấu trúc hàng/cột của phòng).
     */
    void drawSeatMap(string showtimeId, string roomId);
    
    // --- HÀM HỖ TRỢ HIỂN THỊ (HELPER) ---
    void clearScreen();
    void printHeader(string title);

 
};

#endif // TICKET_UI_H