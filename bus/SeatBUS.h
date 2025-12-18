#ifndef SEAT_BUS_H
#define SEAT_BUS_H

#include "../dal/SeatDAL.h"
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;

struct SeatDisplay {
    string id;
    string row;
    int number;
    bool isBooked;
};

class SeatBUS {
private:
    SeatDAL seatDal; 
    const string FILE_NAME = "../data/Seats.txt"; 
    const vector<string> ALL_ROWS = {"A", "B", "C", "D", "E"}; 
    const int SEATS_PER_ROW = 10; 

public:
    // [CẬP NHẬT] Thêm showtimeId vào tất cả các hàm
    
    // Lấy danh sách ghế của một suất chiếu cụ thể
    vector<SeatDisplay> getSeatsByShowtime(string showtimeId, string roomId);

    bool checkAvailable(string showtimeId, string roomId, string seatId);
    bool bookSeat(string showtimeId, string roomId, string seatId);
    bool unlockSeat(string showtimeId, string roomId, string seatId);
    long long getSeatPrice(string showtimeId, string roomId, string seatId);

private:
    void parseSeatId(string fullSeatId, string& rowOut, string& numOut);
};

#endif