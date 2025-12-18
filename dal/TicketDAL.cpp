#include "TicketDAL.h"
#include "DALUtils.h"
#include <fstream>
#include <iostream>
#include <format> // C++20

using std::format;
using std::vector;
using std::string;

vector<Ticket> TicketDAL::loadTickets(string input) {
    vector<Ticket> tickets;
    
    // Kiểm tra file trước khi mở
    if (!DALUtils::fileManagementTest(input)) {
        return tickets;
    }

    std::ifstream file(input);
    string line;

    while(std::getline(file, line)) {
        if(line.empty()) continue;

        vector<string> tokens = DALUtils::Split(line, " | ");
        // Đảm bảo đủ 8 trường dữ liệu
        if (tokens.size() >= 8) {
            string id = DALUtils::Trim(tokens[0]);
            string stID = DALUtils::Trim(tokens[1]);
            string movie = DALUtils::Trim(tokens[2]);   
            string room = DALUtils::Trim(tokens[3]);
            string seat = DALUtils::Trim(tokens[4]);
            string cust = DALUtils::Trim(tokens[5]);
            string price = DALUtils::Trim(tokens[6]);
            string time = DALUtils::Trim(tokens[7]);
            string date = DALUtils::Trim(tokens[8]);

            // Sử dụng constructor của Ticket thay vì gán từng biến private (nếu class Ticket private biến)
            Ticket ticket(id, stID,movie, room, seat, cust, price, time, date);
            tickets.push_back(ticket);
        }
    }
    file.close();
    return tickets;
}

bool TicketDAL::saveTickets(string fileName, Ticket ticket) {
    // 1. Load danh sách cũ
    vector<Ticket> ticketBooked = TicketDAL::loadTickets(fileName);

    // 2. Thêm vé mới
    ticketBooked.push_back(ticket);

    // 3. Ghi đè lại file
    std::ofstream file(fileName);
    if (!file.is_open()) return false;

    for(const auto& t : ticketBooked) {
        // Sử dụng getter để lấy dữ liệu
        string line = format("{} | {} | {} | {} | {} | {} | {} | {} | {}\n", 
                             t.getTicketID(), t.getShowtimeID(), t.getMovie(), t.getRoomID(), t.getSeatID(),
                             t.getCustomerName(), t.getPrice(), t.getShowTime(), t.getDate());
        file << line;
    }

    file.close();
    return true;
}