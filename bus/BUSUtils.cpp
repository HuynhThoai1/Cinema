#include "BUSUtils.h"
#include <sstream>
#include <iostream>


std::string BUSUtils::formatCurrency(long long amount) {
    std::string money = std::to_string(amount);
    for(int i=money.length()-3; i>0; i-=3) {
        money.insert(i, ".");
    }

    return money;
}

// void BUSUtils::cancelTicket(Ticket ticket) {
//     ticket.setTicketID("");
//     ticket.setCustomerName("");
//     ticket.setDate("");
//     ticket.setMovie("");
// }
