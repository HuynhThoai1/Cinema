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
    static Ticket* createTicket(string showtimeId,string movie, string roomID, string seatID,
                               string customerName, string price, 
                               string showTime, string date) {
        string newTicketID = generateUniqueID();
        return new Ticket(newTicketID, showtimeId, movie, roomID, seatID, customerName, price, showTime, date);
    }
    
private:
    static string generateUniqueID() {
        // Lưu ý: Nhớ gọi srand(time(0)) trong main()
        int randomNum = 1000 + (rand() % 9000); 
        return "TKT" + to_string(randomNum);
    }
};

#endif