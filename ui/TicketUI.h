#ifndef TICKET_UI_H
#define TICKET_UI_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "../dto/Seat.h" 

using std::string;
using std::vector;

class TicketUI {
private:
    const int SEATS_PER_ROW = 30; // Cấu hình cứng số ghế

public:
    TicketUI() {}

    /**
     * Hàm vẽ sơ đồ.
     * THAY ĐỔI LỚN: Thay vì tự gọi BUS load dữ liệu, 
     * hàm này nhận trực tiếp danh sách ghế (listRows) từ bên ngoài đưa vào.
     * -> Giúp UI tách biệt hoàn toàn khỏi logic lấy dữ liệu.
     */
    void renderSeatMap(string roomId, const vector<Seat*>& listRows);
};

#endif