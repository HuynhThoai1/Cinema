#include "TicketUI.h"
#include <iostream>
#include <iomanip>
using std::cout, std::endl, std::setw;

void TicketUI::renderSeatMap(string roomId, const vector<Seat*>& listRows) {
    cout << "\nSơ đồ ghế phòng " << roomId << ":\n\n";

    // In tiêu đề số ghế
    cout << "    ";
    for (int seatNum = 1; seatNum <= SEATS_PER_ROW; seatNum++) {
        cout << setw(3) << seatNum;
    }
    cout << endl;

    // In từng hàng ghế
    for (const auto& row : listRows) {
        cout << " " << row->getRowId() << " |"; // In ký tự hàng

        for (int seatNum = 1; seatNum <= SEATS_PER_ROW; seatNum++) {
            string seatId = row->getRowId() + std::to_string(seatNum);
            bool isBooked = !row->isAvailable(std::to_string(seatNum));

            if (isBooked) {
                cout << " X "; // Ghế đã đặt
            } else {
                cout << " O "; // Ghế trống
            }
        }
        cout << endl;
    }
    cout << "\nO: Ghế trống | X: Ghế đã đặt\n";
}