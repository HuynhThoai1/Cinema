/**
 * @file Food.h
 * @brief Định nghĩa lớp Food (DTO).
 * @details Đại diện cho một món ăn với các thuộc tính cơ bản: ID, Tên, Giá.
 */

#ifndef FOOD_H
#define FOOD_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @class Food
 * @brief Class đại diện cho đối tượng Món ăn.
 */
class Food {
private:
    string id;          
    string name;      
    int basePrice;      

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
    Food(string id, string name, int price);

    string getId() const;
    string getName() const;
    int getPrice() const;

    /**
     * @brief Hiển thị thông tin món ăn ra màn hình console.
     */
    void display() const;
};

#endif