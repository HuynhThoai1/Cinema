/**
 * @file Food.h
 * @brief Khai báo lớp Food (DTO) đại diện cho một món ăn.
 * @details File này định nghĩa cấu trúc dữ liệu của một món ăn bao gồm ID, tên và giá,
 * cùng các phương thức hiển thị và truy xuất dữ liệu.
 */

#ifndef FOOD_H
#define FOOD_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @class Food
 * @brief Lớp đại diện cho đối tượng Món ăn trong hệ thống.
 * * Lớp này lưu trữ thông tin chi tiết về món ăn và cung cấp
 * các phương thức để khởi tạo và truy xuất các thông tin đó.
 */
class Food {
private:
    /**
     * @brief Mã định danh duy nhất của món ăn (ví dụ: F001).
     */
    string id;

    /**
     * @brief Tên gọi của món ăn.
     */
    string name;

    /**
     * @brief Giá bán cơ bản của món ăn (kiểu số nguyên).
     */
    int basePrice;

public:
    /**
     * @brief Constructor mặc định.
     * * Khởi tạo một đối tượng Food rỗng hoặc với các giá trị mặc định.
     */
    Food();

    /**
     * @brief Constructor có tham số.
     * * Khởi tạo đối tượng Food với đầy đủ thông tin.
     * * @param id Mã món ăn.
     * @param name Tên món ăn.
     * @param price Giá món ăn.
     */
    Food(string id, string name, int price);

    /**
     * @brief Lấy mã món ăn.
     * * @return string Mã định danh (ID) hiện tại.
     */
    string getId() const;

    /**
     * @brief Lấy tên món ăn.
     * * @return string Tên của món ăn.
     */
    string getName() const;

    /**
     * @brief Lấy giá món ăn.
     * * @return int Giá bán hiện tại.
     */
    int getPrice() const;

    /**
     * @brief Hiển thị thông tin chi tiết món ăn.
     * * In ra màn hình (console) thông tin ID, tên và giá theo định dạng,
     * thường sử dụng setw để căn chỉnh cột cho đẹp.
     */
    void display() const;
};

#endif