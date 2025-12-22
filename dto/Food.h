/**
 * @file Food.h
 * @brief Định nghĩa lớp đối tượng Món ăn (Data Transfer Object).
 */

#ifndef FOOD_H
#define FOOD_H

#include <string>
#include <iostream>
#include <iomanip>

/**
 * @class Food
 * @brief Lớp đại diện cho một món ăn hoặc đồ uống trong rạp phim.
 * @details Chứa các thuộc tính cơ bản như ID, tên món và giá bán.
 */
class Food {
private:
    std::string id;         ///< Mã định danh món ăn (Ví dụ: F01)
    std::string name;       ///< Tên món ăn
    int basePrice;          ///< Giá bán cơ bản (VND)

public:
    /**
     * @brief Constructor mặc định.
     */
    Food();

    /**
     * @brief Constructor đầy đủ tham số.
     * @param id Mã món ăn.
     * @param name Tên món ăn.
     * @param price Giá bán.
     */
    Food(std::string id, std::string name, int price);

    /** @brief Lấy mã món ăn. @return std::string ID món ăn. */
    std::string getId() const;

    /** @brief Lấy tên món ăn. @return std::string Tên món. */
    std::string getName() const;

    /** @brief Lấy giá bán. @return int Giá bán. */
    int getPrice() const;

    /**
     * @brief Hiển thị thông tin món ăn ra màn hình console.
     */
    void display() const;
};

#endif