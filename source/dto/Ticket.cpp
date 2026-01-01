#include "Ticket.h"

Ticket::Ticket(string ticketID, string showtimeID, string movie, string roomID, string seatID,
               string customerName, string price, string showTime, string date) {
    this->_ticketID = ticketID;
    this->_showtimeID = showtimeID;
    this->_movie = movie;
    this->_roomID = roomID;
    this->_seatID = seatID;
    this->_customerName = customerName;
    this->_price = price;
    this->_showTime = showTime;
    this->_date = date;
}

Ticket::Ticket() {
    //Do nothing
}

//getter part
string Ticket::getTicketID() const{
    return _ticketID;
}

string Ticket::getShowtimeID() const {
    return _showtimeID;
}

string Ticket::getMovie() const{
    return _movie;
}

string Ticket::getRoomID() const{
    return _roomID;
}

string Ticket::getSeatID() const{
    return _seatID;
}

string Ticket::getCustomerName() const{
    return _customerName;
}

string Ticket::getPrice() const{
    return _price;
}

string Ticket::getShowTime() const{
    return _showTime;
}

string Ticket::getDate() const{
    return _date;
}

//setter part
void Ticket::setTicketID(string ticketID) {
    this->_ticketID = ticketID;
}

void Ticket::setMovie(string movie) {
    this->_movie = movie;
}

void Ticket::setRoomID(string roomID) {
    this->_roomID = roomID;
}

void Ticket::setSeatID(string seatID) {
    this->_seatID = seatID;
}

void Ticket::setCustomerName(string customerName) {
    this->_customerName = customerName;
}

void Ticket::setPrice(string price) {
    this->_price = price;
}

void Ticket::setShowTime(string showTime) {
    this->_showTime = showTime;
}

void Ticket::setDate(string date) {
    this->_date = date;
}