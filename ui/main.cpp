#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include "../bus/BookingFacade.h"

// ==========================================
// INCLUDE FACADE (Sau khi đã có các BUS)
// ==========================================
// ==========================================
// UI CLASSES (Theo Diagram)
// ==========================================

// Lớp Menu giả lập giao diện console cho khách
class CustomerMenu {
private:
    BookingFacade bookingFacade; // Diagram: CustomerMenu --> BookingFacade
    string currentUserId;

public:
    CustomerMenu(string uid) : currentUserId(uid) {}

    void show() {
        int choice;
        do {
            cout << "\n--- CUSTOMER MENU (" << currentUserId << ") ---" << endl;
            cout << "1. Dat ve (Process Booking)" << endl;
            cout << "0. Quay lai" << endl;
            cout << "Chon: ";
            cin >> choice;

            if (choice == 1) {
                handleBooking();
            }
        } while (choice != 0);
    }

private:
    void handleBooking() {
        string showtimeId, seatId;
        
        cin.ignore();
        cout << "\n--- DAT VE ---" << endl;
        cout << "Nhap ID Suat Chieu (VD: SC01): ";
        getline(cin, showtimeId);

        cout << "Nhap ID Ghe (VD: A1): ";
        getline(cin, seatId);

        // Gọi Facade để xử lý toàn bộ quy trình
        // Đúng theo diagram: processBooking(userId, showtimeId, seatId)
        bool result = bookingFacade.processBooking(currentUserId, showtimeId, seatId);

        if (result) {
            cout << ">>> KET QUA: Ban da dat ve thanh cong!" << endl;
        } else {
            cout << ">>> KET QUA: Dat ve that bai. Vui long thu lai." << endl;
        }
    }
};

// Lớp ứng dụng chính
class MainApp {
public:
    void run() {
        // Giả lập việc Login (UserBUS) đã xong và trả về User ID
        string userId = "CUS_123"; 
        
        cout << "Gia lap: Dang nhap thanh cong voi User: " << userId << endl;

        // Chuyển sang menu khách hàng
        CustomerMenu cusMenu(userId);
        cusMenu.show();
    }
};

// ==========================================
// HAM MAIN
// ==========================================
int main() {
    MainApp app;
    app.run();
    return 0;
}