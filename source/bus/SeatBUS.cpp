#include "SeatBUS.h"
#include <iostream>
#include <algorithm>

void SeatBUS::parseSeatId(string fullSeatId, string& rowOut, string& numOut) {
    if (fullSeatId.empty()) return;
    rowOut = fullSeatId.substr(0, 1); 
    if (fullSeatId.length() > 1) numOut = fullSeatId.substr(1);
    else numOut = "";
}

long long SeatBUS::getSeatPrice(string showtimeId, string roomId, string seatId) {
    string row, num;
    parseSeatId(seatId, row, num);
    vector<Seat> loadedData = seatDal.loadSeats(FILE_NAME);

    // Tìm đúng suất chiếu, phòng và hàng
    for (const auto& s : loadedData) {
        if (s.getShowtimeId() == showtimeId && s.getRoom() == roomId && s.getRowId() == row) {
            return s.getPrice();
        }
    }
    // Nếu suất chiếu này MỚI TINH (chưa có trong file Seats.txt)
    // Trả về giá mặc định dựa trên hàng ghế
    if (row >= "D") return 80000;
    return 50000;
}

vector<SeatDisplay> SeatBUS::getSeatsByShowtime(string showtimeId, string roomId) {
    vector<SeatDisplay> displayList;
    vector<Seat> loadedData = seatDal.loadSeats(FILE_NAME);

    for (const string& r : ALL_ROWS) {
        vector<string> bookedInThisRow;
        
        // Tìm dữ liệu đã lưu của suất chiếu này
        for (const auto& s : loadedData) {
            if (s.getShowtimeId() == showtimeId && s.getRoom() == roomId && s.getRowId() == r) {
                bookedInThisRow = s.getSeatBooked();
                break;
            }
        }

        for (int i = 1; i <= SEATS_PER_ROW; ++i) {
            string numStr = std::to_string(i);
            SeatDisplay seat;
            seat.row = r;
            seat.number = i;
            seat.id = r + numStr;
            
            bool found = std::find(bookedInThisRow.begin(), bookedInThisRow.end(), numStr) != bookedInThisRow.end();
            seat.isBooked = found;
            displayList.push_back(seat);
        }
    }
    return displayList;
}
// Chỉ gọi seatDal() mặc định, vì bên trong SeatDAL nó đã tự lo đường dẫn rồi
SeatBUS::SeatBUS() : seatDal() { 
    // Load ghế nếu cần
    // ...
}
bool SeatBUS::checkAvailable(string showtimeId, string roomId, string seatId) {
    string row, num;
    parseSeatId(seatId, row, num);
    vector<Seat> loadedData = seatDal.loadSeats(FILE_NAME);

    for (const auto& s : loadedData) {
        if (s.getShowtimeId() == showtimeId && s.getRoom() == roomId && s.getRowId() == row) {
            return s.isAvailable(num); 
        }
    }
    // Nếu không tìm thấy dòng nào => Suất mới => Ghế trống
    return false; 
}

bool SeatBUS::bookSeat(string showtimeId, string roomId, string seatId) {
    string row, num;
    parseSeatId(seatId, row, num);

    vector<Seat> seats = seatDal.loadSeats(FILE_NAME);
    vector<string> currentBookedList;

    // Load danh sách cũ
    for (const auto& s : seats) {
        if (s.getShowtimeId() == showtimeId && s.getRoom() == roomId && s.getRowId() == row) {
            currentBookedList = s.getSeatBooked();
            break;
        }
    }

    // Check trùng
    for (const string& booked : currentBookedList) {
        if (booked == num) return false; 
    }

    currentBookedList.push_back(num);
    // Gọi hàm save mới có showtimeId
    return seatDal.saveSeats(showtimeId, roomId, row, currentBookedList, FILE_NAME);
}

bool SeatBUS::unlockSeat(string showtimeId, string roomId, string seatId) {
    string row, num;
    parseSeatId(seatId, row, num);

    vector<Seat> seats = seatDal.loadSeats(FILE_NAME);
    vector<string> currentBookedList;
    bool foundRow = false;

    for (const auto& s : seats) {
        if (s.getShowtimeId() == showtimeId && s.getRoom() == roomId && s.getRowId() == row) {
            currentBookedList = s.getSeatBooked();
            foundRow = true;
            break;
        }
    }

    if (!foundRow) return false;

    auto it = std::remove(currentBookedList.begin(), currentBookedList.end(), num);
    if (it == currentBookedList.end()) return false;
    currentBookedList.erase(it, currentBookedList.end());

    return seatDal.saveSeats(showtimeId, roomId, row, currentBookedList, FILE_NAME);
}