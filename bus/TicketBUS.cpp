// TicketBUS.cpp
#include "TicketBUS.h"
#include <iostream>

bool TicketBUS::createAndSaveTicket(string customerName, string movieTitle, string roomId, 
                                    string seatId, string price, string time, string date) {
    
    // 1. Gọi Factory để tạo đối tượng (Factory sẽ tự sinh ID)
    Ticket* newTicket = TicketFactory::createTicket(movieTitle, roomId, seatId, customerName, price, time, date);
    
    if (newTicket == nullptr) {
        std::cout << "[TicketBUS] Loi: Khong the tao doi tuong Ve.\n";
        return false;
    }

    // 2. Lưu xuống File qua DAL
    // Lưu ý: DAL nên tự quản lý tên file, hoặc truyền từ config, tránh hardcode string
    bool success = TicketDAL::saveTickets("Tickets.txt", *newTicket);

    if (!success) {
        std::cout << "[TicketBUS] Loi: Khong the ghi ve xuong File.\n";
        delete newTicket; // Xóa ngay nếu lưu lỗi
        return false;
    }

    // 3. Dọn dẹp bộ nhớ
    // Vì ta đã lưu xuống file text rồi, đối tượng này không cần giữ trong RAM nữa
    delete newTicket; 
    
    return true;
}