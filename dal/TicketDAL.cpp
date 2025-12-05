#include "TicketDAL.h"
#include "DALUtils.h"
#include <fstream>
#include <sstream>
#include <format>
#include <iostream>

using std::format;

vector<Ticket> TicketDAL::readTicketsFromFile(string input) {
    vector<Ticket> tickets;
    std::ifstream file(input);
    DALUtils::fileManagementTest(input);
    string line;

    while(std::getline(file, line)) {
        vector<string> tokens = DALUtils::Split(line, " | ");
        Ticket ticket;
        if (tokens.size() >= 8) {
            ticket._ticketID = DALUtils::Trim(tokens[0]);
            ticket._movie = DALUtils::Trim(tokens[1]);   
            ticket._roomID = DALUtils::Trim(tokens[2]);
            ticket._seatID = DALUtils::Trim(tokens[3]);
            ticket._customerName = DALUtils::Trim(tokens[4]);
            ticket._price = DALUtils::Trim(tokens[5]);
            ticket._showTime = DALUtils::Trim(tokens[6]);
            ticket._date = DALUtils::Trim(tokens[7]);
            
            tickets.push_back(ticket);
        }
    }
    return tickets;
}

bool TicketDAL::writeTickets(string fileName, Ticket ticket) {
    if(!DALUtils::fileManagementTest(fileName)) {
        return false;
    }
    vector<Ticket> ticketBooked = TicketDAL::readTicketsFromFile(fileName);

    Ticket newTicket;
    newTicket._ticketID = ticket._ticketID;
    newTicket._movie = ticket._movie;
    newTicket._roomID = ticket._roomID;
    newTicket._seatID = ticket._seatID;
    newTicket._customerName = ticket._customerName;
    newTicket._price = ticket._price;
    newTicket._showTime = ticket._showTime;
    newTicket._date = ticket._date;
    ticketBooked.push_back(newTicket);

    std::ofstream file(fileName);
    string line;
    for(Ticket tickets : ticketBooked) {
        line = format("{} | {} | {} | {} | {} | {} | {} | {} \n", tickets._ticketID, tickets._movie, tickets._roomID, tickets._seatID,
                             tickets._customerName, tickets._price, tickets._showTime, tickets._date);
        file << line;
    }

    file.close();
    return true;
}

//Test

// int main() {
//     vector<Ticket> tickets = TicketDAL::readTicketsFromFile("../text/Tickets.txt");

//     for (const Ticket& ticket : tickets) {
//         std::cout << "TicketID: " << ticket._ticketID << ", Movie: " << ticket._movie 
//                   << ", RoomID: " << ticket._roomID << ", SeatID: " << ticket._seatID 
//                   << ", CustomerName: " << ticket._customerName << ", Price: " << ticket._price 
//                   << ", ShowTime: " << ticket._showTime << ", Date: " << ticket._date << std::endl;
//     }

//     Ticket newTicket{"abc", "123", "456", "789", "234", "345", "678", "125"};
//     TicketDAL::writeTickets("../text/Tickets.txt", newTicket);
//     return 0;
// }