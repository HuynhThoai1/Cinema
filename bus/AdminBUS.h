/**
 * @file AdminBUS.h
 * @brief Tầng nghiệp vụ dành riêng cho chức năng quản trị tài khoản.
 */

#ifndef _ADMIN_BUS_H_
#define _ADMIN_BUS_H_

#include <vector>
#include <string>
#include <iostream>
#include "../dal/UserDAL.h"
#include "../dto/User.h"

class AdminBUS {
private:
    UserDAL userDal;    ///< Đối tượng DAL
    vector<User*> users;///< Danh sách user để quản lý
public:
    AdminBUS();
    ~AdminBUS();

    /**
     * @brief Tải lại danh sách user mới nhất từ file.
     */
    void loadUsers();

    /**
     * @brief Lấy danh sách toàn bộ người dùng.
     * @return vector<User*> Danh sách user.
     */
    vector<User*> getAllUsers();

    /**
     * @brief Khóa tài khoản người dùng.
     * @param userId ID người dùng cần khóa.
     * @return true nếu khóa thành công.
     * @note Thay đổi role thành "Locked". Không thể khóa Admin.
     */
    bool lockUser(string userId);

    /**
     * @brief Mở khóa tài khoản.
     * @param userId ID người dùng cần mở.
     * @return true nếu mở khóa thành công.
     * @note Thay đổi role từ "Locked" về "Customer".
     */
    bool unlockUser(string userId);
    
    /**
     * @brief Xóa tài khoản khỏi hệ thống.
     * @param userId ID người dùng cần xóa.
     * @return true nếu xóa thành công.
     * @warning Hành động này xóa vĩnh viễn dữ liệu trong file.
     */
    bool removeUser(string userId);
};

#endif