<<<<<<< HEAD
```Bash
$ g++ main.cpp dto/*.cpp dal/*.cpp bus/*.cpp ui/FoodUI.cpp ui/RevenueUI.cpp -o app
./app
```
```
g++ -std=c++23 -I../../dto -I../../dal -I../../bus -I../../ui -I../../utils \
main.cpp \
../../dto/Food.cpp ../../dto/Revenue.cpp \
../../dal/FoodDAL.cpp ../../dal/RevenueDAL.cpp \
../../bus/FoodBUS.cpp ../../bus/RevenueBUS.cpp \
../../ui/FoodUI.cpp ../../ui/RevenueUI.cpp \
-o ../../out/thai_test
```


