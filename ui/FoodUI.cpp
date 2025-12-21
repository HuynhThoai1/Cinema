#include "FoodUI.h" 
#include <iomanip>

/**
 * @brief Constructor mặc định của lớp FoodUI.
 */
FoodUI::FoodUI() {}

/**
 * @brief Điều hướng menu chính của chức năng quản lý món ăn.
 * * Sử dụng vòng lặp do-while để duy trì giao diện cho đến khi người dùng chọn thoát (0).
 * * Kết nối các lựa chọn của người dùng với các phương thức thực thi tương ứng.
 */
void FoodUI::process() {
    int choice;
    do {
        cout << "\n--- QUAN LY MON AN ---\n";
        cout << "1. Xem danh sach\n2. Them mon\n3. Tinh tien thu\n0. Quay lai\nChon: ";
        cin >> choice; cin.ignore();
        switch (choice) {
            case 1: showAllFoods(); break;
            case 2: inputNewFood(); break;
            case 3: orderDemo(); break;
        }
    } while (choice != 0);
}

/**
 * @brief Giao diện nhập liệu để thêm món ăn mới.
 * * Thu thập thông tin từ bàn phím và gửi yêu cầu xử lý tới `foodBus`.
 */
void FoodUI::inputNewFood() {
    string id, name; int price;
    cout << "Nhap ID: "; getline(cin, id);
    cout << "Nhap Ten: "; getline(cin, name);
    cout << "Nhap Gia: "; cin >> price; cin.ignore();
    foodBus.addNewFood(id, name, price);
    cout << ">> Da them thanh cong!\n";
}

/**
 * @brief Hiển thị danh sách tất cả món ăn dưới dạng bảng.
 * * Sử dụng `std::setw` để căn lề các cột ID, Tên và Giá sao cho thẳng hàng, dễ đọc.
 */
void FoodUI::showAllFoods() {
    vector<Food> list = foodBus.getAll();
    cout << "--------------------------------\n";
    cout << left << setw(10) << "ID" << setw(20) << "TEN" << "GIA\n";
    for(auto& f : list) {
        cout << left << setw(10) << f.getId() << setw(20) << f.getName() << f.getPrice() << endl;
    }
    cout << "--------------------------------\n";
}

/**
 * @brief Giả lập tính năng đặt hàng để tính tổng tiền.
 * * Cho phép người dùng nhập một danh sách mã món ăn (ID), sau đó gọi 
 * nghiệp vụ từ tầng BUS để tính toán tổng chi phí.
 */
void FoodUI::orderDemo() {
    cout << "Nhap so luong mon: "; int n; cin >> n; cin.ignore();
    vector<string> ids;
    for(int i=0; i<n; i++) {
        string id; cout << "Mon " << i+1 << ": "; getline(cin, id);
        ids.push_back(id);
    }
    cout << ">> Tong tien: " << foodBus.calculateOrderTotal(ids) << " VND\n";
}