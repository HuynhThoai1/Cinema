#ifndef TICKETFACTORY_H
#define TICKETFACTORY_H

#include "Ticket.h"
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>

using std::string;
using std::to_string;

class TicketFactory {
public:
    /**
     * Phương thức tĩnh (static) để tạo đối tượng Ticket.
     * Người dùng KHÔNG cần truyền ticketID, Factory sẽ tự sinh.
     */
    static Ticket* createTicket(string movie, string roomID, string seatID,
                               string customerName, string price, 
                               string showTime, string date) {
        
        // 1. Tự động sinh ID duy nhất cho vé
        string newTicketID = generateUniqueID();

        // 2. Trả về đối tượng Ticket đã được khởi tạo đầy đủ
        return new Ticket(newTicketID, movie, roomID, seatID, customerName, price, showTime, date);
    }
    
private:
    /**
     * Hàm hỗ trợ sinh ID ngẫu nhiên hoặc theo quy luật.
     * Ví dụ: TKT + Random số. 
     * Trong thực tế, bạn có thể lấy ID lớn nhất từ Database + 1.
     */
    static string generateUniqueID() {
        // Ví dụ đơn giản: TKT + số ngẫu nhiên từ 1000 đến 9999
        // Lưu ý: Cần srand(time(0)) ở hàm main để số thực sự ngẫu nhiên
        int randomNum = 1000 + (rand() % 9000); 
        return "TKT" + to_string(randomNum);
    }
};

#endif