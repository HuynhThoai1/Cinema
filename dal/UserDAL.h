#ifndef _USER_DAL_H
#define _USER_DAL_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../dto/User.h"
#include "../dto/Admin.h"
#include "../dto/Customer.h"

using std::vector, std::string;
using std::istringstream;
using std::cout;

class UserDAL {
public:
    vector<User*>  loadUsers();

    void saveUsers(const vector<User*>& users);

    void addUser(User* user);

};
#endif