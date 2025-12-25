/**
 * @file FoodDAL.h
 * @brief Lớp truy cập dữ liệu cho Món ăn.
 */

#ifndef FOOD_DAL_H
#define FOOD_DAL_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../dto/Food.h"

/**
 * @class FoodDAL
 * @brief Quản lý việc Đọc/Ghi dữ liệu món ăn từ file văn bản.
 */
class FoodDAL {
private:
    std::vector<Food> listFood; ///< Cache danh sách món ăn trong bộ nhớ
    const std::string FILE_NAME = "../data/FoodandDrink.txt"; ///< Đường dẫn file dữ liệu

public:
    /**
     * @brief Đọc dữ liệu từ file vào bộ nhớ.
     * @details Mở file text, phân tích từng dòng và lưu vào vector listFood.
     */
    void loadFoods();

    /**
     * @brief Ghi lại toàn bộ danh sách hiện tại xuống file.
     */
    void saveFoods();

    /**
     * @brief Thêm món ăn mới và lưu ngay vào file.
     * @param food Đối tượng món ăn cần thêm.
     */
    void addFood(const Food& food);

    /**
     * @brief Lấy danh sách món ăn đang có.
     * @return std::vector<Food> Danh sách món ăn.
     */
    std::vector<Food> getList() const;

    /**
     * @brief Tìm món ăn theo ID.
     * @param id Mã món cần tìm.
     * @return Food* Con trỏ đến món ăn tìm thấy (hoặc nullptr nếu không thấy).
     */
    Food* getFoodById(std::string id);

    /**
     * @brief Cập nhật thông tin món ăn theo ID.
     * @param id Mã món cần cập nhật.
     * @param newName Tên mới.
     * @param newPrice Giá mới.
     * @return true nếu cập nhật thành công, ngược lại false.
     */
    bool updateFood(std::string id, std::string newName, int newPrice);

    /**
     * @brief Xóa món ăn theo ID.
     * @param id Mã món cần xóa.
     * @return true nếu xóa thành công, ngược lại false.
     */
    bool deleteFood(std::string id);
};

#endif