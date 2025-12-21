#include <iostream>
#include <vector>
#include <string>

// Include BUS
#include "../../bus/SeatBUS.h"

using namespace std;

// Hàm hỗ trợ in kết quả PASS/FAIL
void printResult(string testName, bool result) {
    if (result) {
        cout << "\033[1;32m[PASS]\033[0m " << testName << endl; // Màu xanh
    } else {
        cout << "\033[1;31m[FAIL]\033[0m " << testName << endl; // Màu đỏ
    }
}

int main() {
    SeatBUS seatBus;
    string roomId = "R01";
    
    // Test với 2 loại ghế để check giá
    string seatStandard = "A1"; // Ghế thường
    string seatVIP = "D1";      // Ghế VIP

    cout << "========== BAT DAU TEST LOGIC (Ghe + Gia Tien) ==========\n" << endl;

    // --- TEST 1: LOAD DU LIEU ---
    cout << "--- 1. Test Load Data ---" << endl;
    vector<SeatDisplay> seats = seatBus.getSeatsByRoom(roomId);
    if (!seats.empty()) {
        cout << "   -> Da load duoc " << seats.size() << " ghe cho phong " << roomId << endl;
        printResult("Load danh sach ghe tu file", true);
    } else {
        cout << "   -> Khong load duoc du lieu." << endl;
        printResult("Load danh sach ghe tu file", false);
    }

    // --- TEST 2: KIỂM TRA GIÁ TIỀN (TÍNH NĂNG MỚI) ---
    cout << "\n--- 2. Test Get Seat Price (Kiem tra gia tien) ---" << endl;
    
    // Test ghế thường (Hàng A)
    long long priceA = seatBus.getSeatPrice(roomId, seatStandard);
    cout << "   -> Gia ghe " << seatStandard << " (Hang A): " << priceA << " VND" << endl;
    printResult("Check gia ghe thuong (Mong doi: 50000)", priceA == 50000);

    // Test ghế VIP (Hàng D)
    long long priceD = seatBus.getSeatPrice(roomId, seatVIP);
    cout << "   -> Gia ghe " << seatVIP << " (Hang D): " << priceD << " VND" << endl;
    printResult("Check gia ghe VIP (Mong doi: 80000)", priceD == 80000);


    // --- TEST 3: CHECK AVAILABLE (KIEM TRA TRONG) ---
    cout << "\n--- 3. Test Check Available ---" << endl;
    bool isFree = seatBus.checkAvailable(roomId, seatStandard);
    cout << "   -> Trang thai hien tai cua " << seatStandard << ": " << (isFree ? "TRONG" : "DA DAT") << endl;


    // --- TEST 4: BOOKING (DAT GHE) ---
    cout << "\n--- 4. Test Book Seat (Dat ghe) ---" << endl;
    
    if (isFree) {
        bool bookSuccess = seatBus.bookSeat(roomId, seatStandard);
        printResult("Dat ghe " + seatStandard, bookSuccess);
        
        // Check lại xem nó đã thành bận chưa
        bool isFreeNow = seatBus.checkAvailable(roomId, seatStandard);
        printResult("Kiem tra lai trang thai sau khi dat (Phai la false)", !isFreeNow);
        
        // Check xem giá tiền có bị mất sau khi ghi đè file không
        long long priceAfterBook = seatBus.getSeatPrice(roomId, seatStandard);
        printResult("Kiem tra bao toan gia tien sau khi dat", priceAfterBook == 50000);

    } else {
        cout << "   -> Ghe dang ban, thu dat chong len xem co chan duoc khong..." << endl;
        bool bookSuccess = seatBus.bookSeat(roomId, seatStandard);
        printResult("Chan dat ghe trung (Phai return false)", !bookSuccess);
    }


    // --- TEST 5: UNLOCK (HUY GHE - ROLLBACK) ---
    cout << "\n--- 5. Test Unlock Seat (Huy ghe) ---" << endl;
    bool unlockSuccess = seatBus.unlockSeat(roomId, seatStandard);
    printResult("Huy dat ghe " + seatStandard, unlockSuccess);

    // Check lại lần cuối
    bool finalCheck = seatBus.checkAvailable(roomId, seatStandard);
    printResult("Kiem tra lai trang thai sau khi huy (Phai la true)", finalCheck);

    cout << "\n========== KET THUC TEST ==========" << endl;

    return 0;
}