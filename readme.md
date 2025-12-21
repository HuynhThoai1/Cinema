Họ và tên: **Cái Hoàng Thái**
Mã số sinh viên: **24120439**

##Biên dịch
```Bash
$ g++ main.cpp dto/*.cpp dal/*.cpp bus/*.cpp ui/FoodUI.cpp ui/RevenueUI.cpp -o app
./app
```
```
$ g++ -std=c++23 \
-I. -Idto -Idal -Ibus -Iui \
thai_test/main.cpp \
dto/Food.cpp dto/Revenue.cpp \
dal/FoodDAL.cpp dal/RevenueDAL.cpp dal/DALUtils.cpp \
bus/FoodBUS.cpp bus/RevenueBUS.cpp bus/BUSUtils.cpp \
ui/FoodUI.cpp ui/RevenueUI.cpp \
-o out/thai_test


$ ./out/thai_test
```

