#include "FoodBUS.h"
<<<<<<< HEAD
using namespace std;
/**
 * @brief Phương thức khởi tạo FoodBUS.
 * * Khi đối tượng được tạo, nó sẽ yêu cầu lớp FoodDAL tải dữ liệu từ nguồn (file/database)
 * vào bộ nhớ tạm để sẵn sàng sử dụng.
 */
FoodBUS::FoodBUS() {
    foodDal.loadFoods(); 
}

/**
=======

/**
 * @brief Phương thức khởi tạo FoodBUS.
 * * Khi đối tượng được tạo, nó sẽ yêu cầu lớp FoodDAL tải dữ liệu từ nguồn (file/database)
 * vào bộ nhớ tạm để sẵn sàng sử dụng.
 */
FoodBUS::FoodBUS() {
    foodDal.loadFoods(); 
}

/**
>>>>>>> 0226781a988cf730ca830fe9989d4de76c815c93
 * @brief Lấy toàn bộ danh sách thực phẩm hiện có.
 * @return Một vector chứa các đối tượng Food được lấy từ lớp truy cập dữ liệu.
 */
vector<Food> FoodBUS::getAll() {
    return foodDal.getList();
}

/**
 * @brief Thêm một món ăn mới với kiểm tra logic cơ bản.
 * * **Logic nghiệp vụ:** Nếu giá sản phẩm (price) nhỏ hơn 0, yêu cầu sẽ bị bỏ qua 
 * để đảm bảo tính toàn vẹn của dữ liệu tài chính.
 * @param id Mã định danh.
 * @param name Tên món.
 * @param price Đơn giá.
 */
void FoodBUS::addNewFood(string id, string name, int price) {
    if (price < 0) return; // Kiểm tra logic nghiệp vụ: Giá không được âm
    Food f(id, name, price);
    foodDal.addFood(f);
}

/**
 * @brief Tính tổng trị giá của một đơn hàng dựa trên danh sách ID.
 * * Hàm sẽ duyệt qua từng ID trong danh sách, tìm kiếm thông tin món ăn tương ứng
 * từ tầng dữ liệu (DAL) và cộng dồn giá vào tổng tiền.
 * @param idList Danh sách các mã món ăn người dùng đã chọn.
 * @return Tổng số tiền (int). Trả về 0 nếu danh sách trống hoặc không tìm thấy món ăn nào.
 */
int FoodBUS::calculateOrderTotal(const vector<string>& idList) {
    int total = 0;
    for (const string& id : idList) {
        Food* f = foodDal.getFoodById(id);
        if (f) {
            total += f->getPrice();
        }
    }
    return total;
}