#include "Seat.h"
Seat::Seat(){
    //do nothing
}
Seat::Seat(string showtimeId, string room, string rowId, long long price) {
        this->_showtimeId = showtimeId;
        this->_room = room;
        this->_rowId = rowId;
        this->_price = price;
    }

    // --- Getters ---
string Seat::getShowtimeId() const { 
    return _showtimeId; 
}
string Seat::getRoom() const { 
    return _room; 
}
string Seat::getRowId() const {
    return _rowId; 
}
long long Seat::getPrice() const { 
    return _price; 
}
vector<string> Seat::getSeatBooked() const { 
    return _seatBooked; 
}

    // --- Setters ---
void Seat::setSeatBooked(const vector<string>& bookedList) {
        _seatBooked = bookedList;
}
    
void Seat::setPrice(long long newPrice) {
        _price = newPrice;
}

    // --- Business Logic ---
void Seat::addBookedSeat(const string& seatId) {
        if (isAvailable(seatId)) {
            _seatBooked.push_back(seatId);
        }
    }

bool Seat::isAvailable(const string& seatId) const {
        for (const string& booked : _seatBooked) {
            if (booked == seatId) return false;
        }
        return true;
    }


