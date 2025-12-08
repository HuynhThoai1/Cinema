#ifndef _SEAT_H_
#define _SEAT_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * @class Seat
 * @brief Đối tượng chuyển giao dữ liệu (DTO) đại diện cho một DÃY GHẾ trong phòng chiếu.
 * @details Mặc dù tên là Seat, nhưng cấu trúc này lưu trữ trạng thái của cả một hàng ghế (Row),
 * bao gồm danh sách các số ghế đã được đặt trong hàng đó.
 */
class Seat {
protected:
    /** * @brief Mã phòng chiếu (Ví dụ: "R01", "R02"). 
     */
    string _roomID;    

    /** * @brief Mã dãy ghế / Hàng ghế (Ví dụ: "A", "B", "C"). 
     */
    string _rowID;

    /** * @brief Danh sách các số ghế đã được đặt trong dãy này.
     * @note Ví dụ: {"1", "3", "5"} nghĩa là ghế số 1, 3, 5 trong dãy đã có người ngồi.
     */
    vector<string> _seatBooked;
};

#endif // _SEAT_H_