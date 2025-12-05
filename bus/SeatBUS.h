#ifndef SEAT_BUS_H
#define SEAT_BUS_H

#include "../dal/SeatDAL.h"
#include <vector>
#include <string>
#include <algorithm> // Để dùng std::find, std::remove

// Định nghĩa struct cho Ghế đơn lẻ để UI dễ hiển thị
// (Vì Seat trong DAL của bạn là nguyên 1 dòng, UI khó vẽ)
struct SeatDisplay {
    string id;      // VD: "A1"
    string row;     // VD: "A"
    int number;     // VD: 1
    bool isBooked;  // true/false
};

class SeatBUS {
private:
    SeatDAL seatDal;
    const string FILE_NAME = "../data/Seats.txt"; // Đường dẫn file cứng

public:
    // Lấy danh sách ghế đơn lẻ để vẽ sơ đồ (Map từ DAL -> UI)
    // Bạn cần truyền roomId (VD: "R01") chứ không phải showtimeId
    vector<SeatDisplay> getSeatsByRoom(string roomId);

    // Kiểm tra ghế trống (Cần RoomID để biết ghế phòng nào)
    bool checkAvailable(string roomId, string seatId);

    // Đặt ghế
    bool bookSeat(string roomId, string seatId);

    // Hủy ghế (Rollback)
    bool unlockSeat(string roomId, string seatId);

private:
    // Hàm phụ trợ: Tách "A1" -> Row "A", Number "1"
    void parseSeatId(string fullSeatId, string& rowOut, string& numOut);
};

#endif