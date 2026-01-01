#include "TicketBUS.h"
#include <iostream>
#include <format> // Cần cho hàm format trong cancelTicket
#include <fstream>
using std::cout;


#include "TicketBUS.h"


string TicketBUS::createAndSaveTicket(string type, string customerName, string showtimeId, string movieTitle, string roomId, 
                                      string seatId, string price, string time, string date) {
    
    // 1. Gọi Factory để tạo đối tượng
   
    Ticket* newTicket = TicketFactory::createTicket(type, showtimeId, movieTitle, roomId, seatId, customerName, price, time, date);
    
    if (newTicket == nullptr) {
        cout << "[TicketBUS] Loi: Khong the tao doi tuong Ve.\n";
        return ""; // Trả về chuỗi rỗng báo lỗi
    }

    // [QUAN TRỌNG] Lấy ID vé ra trước khi lưu và xóa object
    // Vì sau khi delete newTicket, dữ liệu sẽ mất
    string generatedID = newTicket->getTicketID();

    // 2. Lưu xuống File qua DAL
    bool success = TicketDAL::saveTickets("../data/Tickets.txt", *newTicket);

    // 3. Dọn dẹp bộ nhớ (Vì Factory dùng 'new', ta phải 'delete')
    delete newTicket; 

    if (!success) {
        cout << "[TicketBUS] Loi: Khong the ghi ve xuong File.\n";
        return ""; // Thất bại
    } 
    
    // 4. Trả về ID vé vừa tạo thành công
    return generatedID;
}



Ticket* TicketBUS::getTicketById(string ticketId) {
    string fileName = "../data/Tickets.txt"; // [SỬA] Đường dẫn tương đối
    if(!DALUtils::fileManagementTest(fileName)) return nullptr;

    vector<Ticket> allTickets = TicketDAL::loadTickets(fileName);
    for(auto& ticket : allTickets) {
        if(ticketId == ticket.getTicketID()) {
            // Tìm thấy vé, trả về con trỏ đến vé đó
            return new Ticket(ticket); // Cần tạo bản sao để tránh trả về tham chiếu đến biến cục bộ
        }
    }
    // Không tìm thấy vé
    return nullptr;
}
bool TicketBUS::cancelTicket(string ticketID) {
    string fileName = "../data/Tickets.txt"; // [SỬA] Đường dẫn tương đối
    if(!DALUtils::fileManagementTest(fileName)) return false;

    // Lưu ý: TicketDAL::loadTickets cần được implement đúng để hàm này chạy
    vector<Ticket> allTickets = TicketDAL::loadTickets(fileName);
    
    std::ofstream file(fileName);
    if (!file.is_open()) return false;

    for(auto ticket : allTickets) {
        if(ticketID == ticket.getTicketID()) {
            continue; // Bỏ qua vé cần hủy
        }
        
        // Ghi lại các vé còn lại
        // Lưu ý: Cần đảm bảo logic ghi này khớp với TicketDAL::saveTickets
        string line = std::format("{} | {} | {} | {} | {} | {} | {} | {} | {}\n", 
            ticket.getTicketID(), 
            ticket.getShowtimeID(), // Nhớ ghi lại cả ShowtimeID
            ticket.getMovie(), 
            ticket.getRoomID(), 
            ticket.getSeatID(),
            ticket.getCustomerName(), 
            ticket.getPrice(), 
            ticket.getShowTime(), 
            ticket.getDate());
        file << line;
    } 

    file.close();
    return true;
}