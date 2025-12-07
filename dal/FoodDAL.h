/**
 * @file Food_DAL.h
 * @brief Khai báo lớp FoodDAL dùng để quản lý truy cập dữ liệu món ăn.
 * @details File này chứa các định nghĩa hàm để tương tác với dữ liệu Food (đọc, tìm kiếm).
 */

#ifndef FOOD_DAL_H
#define FOOD_DAL_H

#include <vector>
#include <string> // Nên include string nếu dùng string
#include "../dto/Food.h" 

using namespace std;

/**
 * @class FoodDAL
 * @brief Lớp Data Access Layer (DAL) quản lý các thao tác dữ liệu cho đối tượng Food.
 * * Lớp này chịu trách nhiệm tải dữ liệu từ bộ nhớ lưu trữ (file/DB),
 * cung cấp danh sách và các chức năng tìm kiếm món ăn.
 */
class FoodDAL {
private:
    /**
     * @brief Danh sách lưu trữ các đối tượng Food sau khi tải lên.
     */
    vector<Food> listFood;

public:
    /**
     * @brief Đọc dữ liệu món ăn từ nguồn lưu trữ.
     * * Hàm này sẽ đọc file (hoặc database), parse dữ liệu và 
     * đẩy vào vector listFood.
     */
    void loadFoods();

    /**
     * @brief Lấy danh sách toàn bộ món ăn.
     * * @return vector<Food> Vector chứa danh sách các đối tượng Food hiện có.
     */
    vector<Food> getList() const;

    /**
     * @brief Tìm kiếm một món ăn cụ thể dựa trên ID.
     * * @param id Mã định danh (ID) của món ăn cần tìm.
     * @return Food* Con trỏ trỏ đến đối tượng Food tìm thấy. Trả về nullptr hoặc xử lý lỗi nếu không tìm thấy.
     */
    Food* getFoodById(string id);
};

#endif