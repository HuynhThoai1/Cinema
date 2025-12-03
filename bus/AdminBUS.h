#ifndef _ADMIN_BUS_H_
#define _ADMIN_BUS_H_

#include <vector>
#include <string>
#include <iostream>
#include "../dal/UserDAL.h"
#include "../dto/User.h"

class AdminBUS {
private:
    UserDAL userDal;    // Gọi xuống tầng dự liệu
    vector<User*> users;
public:
    AdminBUS();
    ~AdminBUS();

    void loadUsers();
    vector<User*> getAllUsers();
    // Logic: Đổi role thành "Locked" để họ không đăng nhập được
    bool lockUser(string userId);

    // Logic: Đổi role về "Customer"
    bool unlockUser(string userId);
    
    bool removeUser(string userId);
};

#endif