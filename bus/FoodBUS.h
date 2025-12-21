#ifndef FOOD_BUS_H
#define FOOD_BUS_H

#include "../dal/FoodDAL.h"
#include <vector>
#include <string>

/**
 * @class FoodBUS
 * @brief Lớp xử lý nghiệp vụ (Business Logic Layer) cho thực phẩm.
 * * Lớp này đóng vai trò trung gian giữa tầng truy cập dữ liệu (FoodDAL) và tầng giao diện,
 * đảm nhận việc kiểm tra logic và tính toán dữ liệu.
 */
class FoodBUS {
private:
    /** @brief Đối tượng truy cập dữ liệu để làm việc với nguồn dữ liệu thực phẩm. */
    FoodDAL foodDal;

public:
    /**
     * @brief Khởi tạo đối tượng FoodBUS.
     */
    FoodBUS();

    /**
     * @brief Lấy danh sách tất cả món ăn.
     * @return Danh sách (vector) các đối tượng Food.
     */
    vector<Food> getAll();

    /**
     * @brief Thêm một món ăn mới vào hệ thống.
     * @param id Mã định danh duy nhất của món ăn.
     * @param name Tên món ăn.
     * @param price Đơn giá của món ăn.
     */
    void addNewFood(string id, string name, int price);

    /**
     * @brief Tính tổng tiền cho một danh sách các món ăn được chọn.
     * * Hàm này sẽ duyệt qua danh sách mã định danh, tìm giá tương ứng và cộng dồn.
     * * @param idList Danh sách các mã món ăn (ID) trong đơn hàng.
     * @return Tổng số tiền của đơn hàng.
     */
    int calculateOrderTotal(const vector<string>& idList);
};

#endif