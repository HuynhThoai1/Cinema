#ifndef SEAT_H
#define SEAT_H

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

class Seat {
private:
    string _showtimeId;     ///< [MỚI] Mã suất chiếu (VD: ST001)
    string _room;           ///< Mã phòng
    string _rowId;          ///< Mã hàng
    long long _price;       ///< Giá vé
    vector<string> _seatBooked; 

public:
    /**
     * @brief Constructor cập nhật thêm tham số showtimeId ở đầu
     */
    Seat();
    Seat(string showtimeId, string room, string rowId, long long price = 0);

    // --- Getters ---
    string getShowtimeId() const ;
    string getRoom() const ;
    string getRowId() const ;
    long long getPrice() const ;
    vector<string> getSeatBooked() const ;

    // --- Setters ---
    void setSeatBooked(const vector<string>& bookedList) ;
    
    void setPrice(long long newPrice) ;

    // --- Business Logic ---
    void addBookedSeat(const string& seatId) ;
    bool isAvailable(const string& seatId) const ;
};

#endif