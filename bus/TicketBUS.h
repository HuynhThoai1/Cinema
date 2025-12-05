// TicketBUS.h
#ifndef TICKETBUS_H
#define TICKETBUS_H

#include "../dal/TicketDAL.h"
#include "../dto/TicketFactory.h"
#include <string>

class TicketBUS {
private:
    TicketDAL ticketDal;

public:
    // Hàm này chỉ nhận thông tin ĐÃ ĐƯỢC XỬ LÝ (Tên phim, giá tiền...) để in vé
    bool createAndSaveTicket(string customerName, string movieTitle, string roomId, 
                             string seatId, string price, string time, string date);
};

#endif