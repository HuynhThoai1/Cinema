/**
 * @file Food_BUS.h
 * @brief Khai báo lớp FoodBUS xử lý nghiệp vụ liên quan đến món ăn.
 * @details File này đóng vai trò trung gian, lấy dữ liệu từ DAL và thực hiện 
 * các tính toán logic (như tính tiền) trước khi trả về cho giao diện (UI).
 */

#ifndef FOOD_BUS_H
#define FOOD_BUS_H

#include "../dal/FoodDAL.h"
#include <vector>
#include <string>

// Khai báo using để code gọn hơn trong header
using std::vector;
using std::string;

/**
 * @class FoodBUS
 * @brief Lớp Business Logic Layer (BUS) quản lý nghiệp vụ Món ăn.
 * * Lớp này không trực tiếp truy cập file dữ liệu mà gọi thông qua FoodDAL.
 * Nhiệm vụ chính là cung cấp dữ liệu cho UI và xử lý các logic tính toán giá cả.
 */
class FoodBUS {
private:
    /**
     * @brief Đối tượng FoodDAL để giao tiếp với tầng dữ liệu.
     */
    FoodDAL foodDal;

public:
    /**
     * @brief Lấy danh sách toàn bộ món ăn.
     * * Hàm này gọi xuống FoodDAL để lấy dữ liệu thô và trả về cho giao diện hiển thị.
     * * @return vector<Food> Danh sách các món ăn hiện có.
     */
    vector<Food> getAll();

    /**
     * @brief Tính tổng tiền cho một danh sách các món ăn được chọn.
     * * Hàm này nhận vào danh sách các ID, tra cứu giá của từng món (thông qua DAL)
     * và cộng dồn để ra tổng số tiền cần thanh toán.
     * * @param idList Danh sách các ID món ăn (vector<string>) mà khách hàng đã order.
     * @return int Tổng thành tiền (đơn vị tiền tệ).
     */
    int calculateOrderTotal(const vector<string>& idList);
};

#endif