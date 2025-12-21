/**
 * @file FoodBUS.h
 * @brief Lớp xử lý nghiệp vụ (Business Logic) cho Món ăn.
 */

#ifndef FOOD_BUS_H
#define FOOD_BUS_H

#include "../dal/FoodDAL.h"
#include <vector>
#include <string>

/**
 * @class FoodBUS
 * @brief Trung gian xử lý logic giữa giao diện và dữ liệu món ăn.
 */
class FoodBUS {
private:
    FoodDAL foodDal; ///< Đối tượng thao tác dữ liệu

public:
    /**
     * @brief Khởi tạo FoodBUS và nạp dữ liệu ban đầu.
     */
    FoodBUS();

    /**
     * @brief Lấy danh sách tất cả món ăn.
     * @return std::vector<Food> Danh sách món.
     */
    std::vector<Food> getAll();

    /**
     * @brief Thêm món ăn mới (có kiểm tra tính hợp lệ cơ bản).
     * @param id Mã món.
     * @param name Tên món.
     * @param price Giá bán (phải >= 0).
     */
    void addNewFood(std::string id, std::string name, int price);

    /**
     * @brief Tính tổng tiền cho một danh sách ID món ăn được chọn.
     * @param idList Danh sách các ID món ăn.
     * @return int Tổng thành tiền.
     */
    int calculateOrderTotal(const std::vector<std::string>& idList);
};

#endif