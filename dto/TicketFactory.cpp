#include "TicketFactory.h"
Ticket* TicketFactory::createTicket(string showtimeId, string movie, string roomID, string seatID,
                               string customerName, string price, 
                               string showTime, string date) {
        string newTicketID = generateUniqueID();
        return new Ticket(newTicketID, showtimeId, movie, roomID, seatID, customerName, price, showTime, date);
    }