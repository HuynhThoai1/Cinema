#include "SeatBUS.h"
#include <iostream>

using std::to_string;

// Hàm phụ trợ: Tách "A1" thành "A" và "1"
// Tách "B12" thành "B" và "12"
void SeatBUS::parseSeatId(string fullSeatId, string& rowOut, string& numOut) {
    if (fullSeatId.empty()) return;
    
    // Giả định ký tự đầu là Hàng (A, B, C...)
    rowOut = fullSeatId.substr(0, 1);
    
    // Các ký tự sau là Số (1, 10, 12...)
    numOut = fullSeatId.substr(1);
}

// 1. Lấy danh sách ghế để UI vẽ
vector<SeatDisplay> SeatBUS::getSeatsByRoom(string roomId) {
    vector<SeatDisplay> displayList;
    
    // Load dữ liệu thô từ DAL (Danh sách các Dòng)
    vector<Seat> rowsData = seatDal.loadSeats(FILE_NAME);

    // Giả lập cấu trúc phòng: 5 hàng (A-E), mỗi hàng 10 ghế (1-10)
    // Vì DAL chỉ lưu ghế ĐÃ ĐẶT, ta phải tự tạo ra ghế TRỐNG
    string rowLabels[] = {"A", "B", "C", "D", "E"};
    int seatsPerRow = 10;

    for (const string& rLabel : rowLabels) {
        // Tìm xem hàng này có trong file không
        vector<string> bookedInThisRow;
        
        for (const auto& rowData : rowsData) {
            if (rowData._roomID == roomId && rowData._rowID == rLabel) {
                bookedInThisRow = rowData._seatBooked;
                break;
            }
        }

        // Tạo 10 ghế cho hàng này
        for (int i = 1; i <= seatsPerRow; i++) {
            SeatDisplay s;
            s.row = rLabel;
            s.number = i;
            s.id = rLabel + to_string(i); // VD: A1, A2
            s.isBooked = false;

            // Kiểm tra xem số này có trong list đã đặt không
            string numStr = to_string(i);
            for (const string& bookedNum : bookedInThisRow) {
                if (bookedNum == numStr) {
                    s.isBooked = true;
                    break;
                }
            }
            displayList.push_back(s);
        }
    }
    return displayList;
}

// 2. Kiểm tra ghế trống
bool SeatBUS::checkAvailable(string roomId, string seatId) {
    string row, num;
    parseSeatId(seatId, row, num);

    // Load tất cả dòng
    vector<Seat> allRows = seatDal.loadSeats(FILE_NAME);

    for (const auto& rData : allRows) {
        // Tìm đúng Phòng và đúng Dòng
        if (rData._roomID == roomId && rData._rowID == row) {
            // Kiểm tra số ghế có trong list booked không
            for (const string& bookedNum : rData._seatBooked) {
                if (bookedNum == num) {
                    return false; // Đã có người đặt
                }
            }
        }
    }
    return true; // Chưa ai đặt (hoặc dòng chưa được tạo trong file)
}

// 3. Đặt ghế
bool SeatBUS::bookSeat(string roomId, string seatId) {
    string row, num;
    parseSeatId(seatId, row, num);

    // Bước 1: Load dữ liệu hiện tại
    vector<Seat> allRows = seatDal.loadSeats(FILE_NAME);
    vector<string> currentBookedList;
    bool rowFound = false;

    // Bước 2: Tìm danh sách đã đặt của dòng này
    for (const auto& rData : allRows) {
        if (rData._roomID == roomId && rData._rowID == row) {
            currentBookedList = rData._seatBooked;
            rowFound = true;
            break;
        }
    }

    // Bước 3: Thêm số ghế mới vào list
    // (Kiểm tra trùng lặp lần cuối cho chắc)
    bool alreadyExist = false;
    for(const string& s : currentBookedList) {
        if(s == num) alreadyExist = true;
    }

    if (!alreadyExist) {
        currentBookedList.push_back(num);
    } else {
        return false; // Đã tồn tại, không thể đặt đè
    }

    // Bước 4: Gọi DAL lưu lại
    // DAL của bạn hàm saveSeats nhận: room, rowID, vector<booked>
    return seatDal.saveSeats(roomId, row, currentBookedList, FILE_NAME);
}

// 4. Hủy ghế (Dùng cho Rollback khi tạo vé lỗi)
bool SeatBUS::unlockSeat(string roomId, string seatId) {
    string row, num;
    parseSeatId(seatId, row, num);

    vector<Seat> allRows = seatDal.loadSeats(FILE_NAME);
    vector<string> currentBookedList;

    for (const auto& rData : allRows) {
        if (rData._roomID == roomId && rData._rowID == row) {
            currentBookedList = rData._seatBooked;
            break;
        }
    }

    // Xóa số ghế khỏi vector
    // Thuật toán remove-erase idiom
    auto it = std::remove(currentBookedList.begin(), currentBookedList.end(), num);
    if (it == currentBookedList.end()) {
        return false; // Không tìm thấy ghế để xóa
    }
    currentBookedList.erase(it, currentBookedList.end());

    // Lưu lại danh sách mới
    return seatDal.saveSeats(roomId, row, currentBookedList, FILE_NAME);
}