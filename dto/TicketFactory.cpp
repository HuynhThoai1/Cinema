#include "TicketFactory.h"
Ticket* TicketFactory::createTicket(string type, string showtimeId, string movie, string roomID, string seatID,
                                    string customerName, string price, 
                                    string showTime, string date) {
    
    // 1. Tự động sinh ID duy nhất
    string newTicketID = generateUniqueID();

    // 2. Dựa vào 'type' để tạo đúng lớp con
    // Các lớp con sẽ tự tính toán lại giá tiền trong Constructor của chúng
    if (type == "CHILD") {
        return new ChildTicket(newTicketID, showtimeId, movie, roomID, seatID, customerName, price, showTime, date);
    } 
    else if (type == "STUDENT") {
        return new StudentTicket(newTicketID, showtimeId, movie, roomID, seatID, customerName, price, showTime, date);
    } 
    else {
        // Mặc định là Vé Người Lớn (ADULT)
        return new NormalTicket(newTicketID, showtimeId, movie, roomID, seatID, customerName, price, showTime, date);
    }
}