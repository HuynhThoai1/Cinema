#ifndef SEAT_H
#define SEAT_H

#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

class Seat {
private:
    
    string _rowId;         // Hàng ghế (ví dụ: A, B)
    string _room;        // Tên phòng chiếu
    string _type;        // Loại ghế: "NORMAL", "VIP"
    int _basePrice;      // Giá cơ bản
    vector<string> _seatBooked; // Danh sách các ghế đã được đặt (theo thiết kế của bạn)

public:
    // 1. Constructor (Hàm khởi tạo) - Rất quan trọng để tạo đối tượng
    Seat( string rowId, string room, string type, int price) {
        
        this->_rowId = rowId;
        this->_room = room;
        this->_type = type;
        this->_basePrice = price;
    }
    // 2. Getters (Hàm lấy thông tin)
    string getRowId() const { return _rowId; }
    string getRoom() const { return _room; }
    string getType() const { return _type; }    
    int getBasePrice() const { return _basePrice; }
    vector<string> getSeatBooked() const { return _seatBooked; }

    void addBookedSeat(const string& seatId) {
        _seatBooked.push_back(seatId);
    }
    bool isAvailable(const string& seatId) const {
        // Kiểm tra xem ghế cụ thể có trong danh sách đã đặt không
        for (const string& bookedSeat : _seatBooked) {
            if (bookedSeat == seatId) {
                return false; // Ghế đã được đặt
            }
        }
        return true; // Ghế còn trống
    }
    // 4. Các phương thức khác
    virtual int calculatePrice() const = 0; // Phương thức thuần ảo
};

#endif