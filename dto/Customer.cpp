#include "Customer.h"

// --- 1. Constructor ---
Customer::Customer(): User() {
    this->setRole("Customer");
}

Customer::Customer(string id, string username, string password)
    : User(id, username, password, "Customer") {}

// --- 2. Destructor ---
Customer::~Customer() {
    // Do nothing
}

// ---3. Method ---
void Customer::viewMovies() {
    cout << "[Customer] đang xem danh sách phim...\n";
    //CustomerMenu::show();
}

void Customer::viewShowtimes() {
    cout << "[Customer] đang xem lịch chiếu phim...\n";
    //CustomerMenu::show();
}

void Customer::bookTicket() {
    cout << "[Customer] đang thực hiện đặt vé...\n";
    // CustomerMenu::show();
}