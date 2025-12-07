
#include "Food.h"

// 1. Constructor mặc định
// Khởi tạo giá trị rỗng và giá = 0 để tránh lỗi rác bộ nhớ
Food::Food() {
    this->id = "";
    this->name = "";
    this->basePrice = 0;
}

// 2. Constructor có tham số
// Dùng danh sách khởi tạo (Member Initializer List) để gán giá trị nhanh
Food::Food(string id, string name, int price) 
    : id(id), name(name), basePrice(price) {
}

// 3. Các hàm Getter
string Food::getId() const {
    return this->id;
}

string Food::getName() const {
    return this->name;
}

int Food::getPrice() const {
    return this->basePrice;
}

// 4. Hàm hiển thị
// Sử dụng setw để căn lề cột cho thẳng hàng
void Food::display() const {
    cout << left << setw(10) << id 
         << setw(20) << name 
         << setw(10) << basePrice 
         << " VND" << endl;
}