/**
 * @file TicketUI.h
 * @brief Định nghĩa giao diện hiển thị sơ đồ ghế (Presentation Layer).
 *
 * Class này chịu trách nhiệm vẽ trực quan trạng thái của phòng chiếu
 * dựa trên dữ liệu được truyền vào từ bên ngoài (thường là từ Controller hoặc Main).
 * @date 2023-10-27
 */

#ifndef TICKET_UI_H
#define TICKET_UI_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "../dto/Seat.h" 

using std::string;
using std::vector;

/**
 * @class TicketUI
 * @brief Lớp giao diện người dùng (UI) quản lý việc hiển thị đặt vé.
 *
 * Lớp này được thiết kế theo hướng "Stateless" (không lưu trạng thái dữ liệu),
 * chỉ nhận dữ liệu và hiển thị (Rendering).
 */
class TicketUI {
private:
    /**
     * @brief Số lượng ghế tối đa trên một hàng.
     * Dùng để định dạng độ rộng khi in ra console hoặc xác định giới hạn vòng lặp vẽ ghế.
     */
    const int SEATS_PER_ROW = 30; 

public:
    /**
     * @brief Constructor mặc định.
     */
    TicketUI() {}

    /**
     * @brief Vẽ sơ đồ ghế của phòng chiếu ra màn hình console.
     *
     * Hàm này thực hiện các nhiệm vụ:
     * 1. Nhận danh sách các hàng ghế (Seat*) đã được load từ BUS/DAL.
     * 2. Duyệt qua từng hàng, kiểm tra loại ghế (VIP/Normal) để đổi màu hoặc ký hiệu.
     * 3. Duyệt từng số ghế trong hàng, đối chiếu với danh sách đã đặt (`seatBooked`) 
     * để hiển thị trạng thái (VD: [X] là đã đặt, [ ] là trống).
     *
     * @note **Design Pattern**: Áp dụng nguyên lý tách biệt (Separation of Concerns). 
     * UI không tự gọi BUS để lấy dữ liệu mà đợi dữ liệu được truyền vào (Dependency Injection).
     * Điều này giúp UI dễ dàng tái sử dụng cho nhiều phòng chiếu hoặc dữ liệu giả lập khác nhau.
     *
     * @param roomId Mã phòng chiếu đang hiển thị (để in tiêu đề).
     * @param listRows Vector chứa các con trỏ `Seat*`. Nhờ tính đa hình, vector này
     * có thể chứa cả `NormalSeat` và `VipSeat`.
     */
    void renderSeatMap(string roomId, const vector<Seat*>& listRows);
};

#endif // TICKET_UI_H