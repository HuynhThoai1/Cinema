// StudentTicket.h
#ifndef STUDENT_TICKET_H
#define STUDENT_TICKET_H

#include "Ticket.h"
#include <string>

// 3. Vé Học Sinh (Giảm 20%)
class StudentTicket : public Ticket {
public:
    StudentTicket(string ticketID, string showtimeID, string movie, string roomID, string seatID,
                  string customerName, string price, string showTime, string date)
        : Ticket(ticketID, showtimeID, movie, roomID, seatID, customerName, price, showTime, date) 
    {
        try {
            long long val = std::stoll(_price);
            _price = std::to_string((long long)(val * 0.8)); // Giảm 20%
        } catch (...) {
            // Nếu lỗi chuyển đổi số, giữ nguyên giá gốc
        }
    }
};

#endif // STUDENT_TICKET_H