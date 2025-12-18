#ifndef TICKETBUS_H
#define TICKETBUS_H

#include "../dal/TicketDAL.h"
#include "../dto/TicketFactory.h"
#include "../dal/DALUtils.h"
#include "SeatBUS.h"
// #include "BUSUtils.h" // Tạm ẩn để tránh lỗi nếu thiếu file này
#include <string>
#include <vector>

using std::string;
using std::vector;

class TicketBUS {
private:
    TicketDAL ticketDal;
    SeatBUS seatBus;

public:
    /**
     * @brief Tạo và lưu vé (Đã cập nhật hỗ trợ ShowtimeId)
     */
    bool createAndSaveTicket(string customerName, string showtimeId, string movieTitle, string roomId, 
                             string seatId, string price, string time, string date);
    
    Ticket* getTicketById(string ticketId);
    // Hàm hủy vé (Nếu cần dùng sau này)
    bool cancelTicket(string ticketID);
};

#endif // TICKETBUS_H