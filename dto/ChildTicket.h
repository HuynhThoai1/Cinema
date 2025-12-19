// ChildTicket.h
#ifndef CHILD_TICKET_H
#define CHILD_TICKET_H

#include "Ticket.h"
#include <string>

// 2. Vé Trẻ Em (Giảm 50%)
class ChildTicket : public Ticket {
public:
    ChildTicket(string ticketID, string showtimeID, string movie, string roomID, string seatID,
                string customerName, string price, string showTime, string date)
        : Ticket(ticketID, showtimeID, movie, roomID, seatID, customerName, price, showTime, date) 
    {
        try {
            long long val = std::stoll(_price);
            _price = std::to_string(val / 2); // Giảm 50%
        } catch (...) {
            // Nếu lỗi chuyển đổi số, giữ nguyên giá gốc
        }
    }
};

#endif // CHILD_TICKET_H