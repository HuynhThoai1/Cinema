#ifndef TICKET_H
#define TICKET_H
#include <string>

using std::string;

class Ticket {
private:
    string _ticketID;
    string _movie;
    string _roomID;
    string _seatID;
    string _customerName;
    string _price;
    string _showTime;
    string _date;
public:
    Ticket(string ticketID, string movie,  string roomID, string seatID,
         string customerName, string price, string showTime, string date) {
        this->_ticketID = ticketID;
        this->_movie = movie;
        this->_roomID = roomID;
        this->_seatID = seatID;
        this->_customerName = customerName;
        this->_price = price;
        this->_showTime = showTime;
        this->_date = date;
    }

    string getTicketID() const { return _ticketID; }
    string getMovie() const { return _movie; }
    string getRoomID() const { return _roomID; }
    string getSeatID() const { return _seatID; }
    string getCustomerName() const { return _customerName; }
    string getPrice() const { return _price; }
    string getShowTime() const { return _showTime; }
    string getDate() const { return _date; }
};

#endif