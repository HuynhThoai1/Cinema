#include "SeatDAL.h"
#include "DALUtils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <format> 

using std::string;
using std::vector;
using std::format;

// 1. LOAD SEATS (Đọc file: ShowtimeID | Room | Row | Price | Seats...)
vector<Seat> SeatDAL::loadSeats(string fileName) {
    vector<Seat> seats;
    
    if (!DALUtils::fileManagementTest(fileName)) {
        return seats;
    }

    std::ifstream file(fileName);
    string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        vector<string> tokens = DALUtils::Split(line, " | ");
        
        // [SỬA 1] Phải có ít nhất 4 trường: ST, Room, Row, Price
        if (tokens.size() < 4) {
            continue; 
        }

        // [SỬA 2] Cập nhật index đúng
        string stID = DALUtils::Trim(tokens[0]);   
        string roomID = DALUtils::Trim(tokens[1]); // Index 1
        string rowID = DALUtils::Trim(tokens[2]);  // Index 2
        
        // [SỬA 3] Giá tiền ở Index 3
        long long price = 0;
        try {
            string priceStr = DALUtils::Trim(tokens[3]);
            if (!priceStr.empty()) {
                price = std::stoll(priceStr);
            }
        } catch (...) {
            price = 0;
        }

        // [SỬA 4] Truyền đủ 4 tham số vào Constructor
        Seat rowData(stID, roomID, rowID, price);

        // [SỬA 5] Duyệt từ index 4 trở đi (vì 0,1,2,3 là thông tin hàng ghế)
        for (size_t i = 4; i < tokens.size(); i++) {
            string seatNum = DALUtils::Trim(tokens[i]);
            if (!seatNum.empty()) {
                rowData.addBookedSeat(seatNum);
            }
        }
        
        seats.push_back(rowData);
    }

    file.close();
    return seats;
}

// 2. SAVE SEATS
bool SeatDAL::saveSeats(string showtimeId, string room, string rowID, vector<string> seatBooked, string fileName) {
    if (!DALUtils::fileManagementTest(fileName)) {
        return false;
    }

    // Bước 1: Load dữ liệu cũ
    vector<Seat> seats = loadSeats(fileName);
    bool found = false;

    // Bước 2: Tìm và cập nhật (Check cả Showtime và Room cho chắc chắn)
    for (auto& seat : seats) {
        if (seat.getShowtimeId() == showtimeId && 
            seat.getRoom() == room && 
            seat.getRowId() == rowID) {
            
            seat.setSeatBooked(seatBooked);
            found = true; 
            break;
        }
    }

    // Bước 3: Nếu chưa có thì tạo mới
    if (!found) {
        // [SỬA 6] Thêm showtimeId vào Constructor
        // Giá mặc định: Hàng A-C 50k, D trở đi 80k (Logic tạm)
        long long defaultPrice = (rowID >= "D") ? 80000 : 50000;
        
        Seat newSeat(showtimeId, room, rowID, defaultPrice);
        newSeat.setSeatBooked(seatBooked);
        seats.push_back(newSeat);
    }

    // Bước 4: Ghi file
    std::ofstream file(fileName);
    if (!file.is_open()) return false;

    for (const auto& seat : seats) {
        string bookedStr = DALUtils::Join(seat.getSeatBooked(), " | ");
        string line;
        
        // [SỬA 7 - QUAN TRỌNG NHẤT] 
        // Dùng seat.getShowtimeId() thay vì biến showtimeId truyền vào hàm
        // Để tránh việc ghi đè tất cả các dòng thành 1 ID giống nhau
        if (bookedStr.empty()) {
            line = format("{} | {} | {} | {}\n", 
                          seat.getShowtimeId(), seat.getRoom(), seat.getRowId(), seat.getPrice());
        } else {
            line = format("{} | {} | {} | {} | {}\n", 
                          seat.getShowtimeId(), seat.getRoom(), seat.getRowId(), seat.getPrice(), bookedStr);
        }

        file << line;
    }

    file.close();
    return true;
}