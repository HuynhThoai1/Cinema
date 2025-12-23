Nhóm N03 - Project Cinema

##Biên dịch & chạy
```Bash
$ g++ -std=c++23 \
dto/Movie.cpp dto/Showtime.cpp \
dal/MovieDAL.cpp dal/ShowtimeDAL.cpp \
bus/MovieBUS.cpp bus/ShowtimeBUS.cpp \
utils/InputUtils.cpp \
ui/MovieUI.cpp ui/ShowtimeUI.cpp \
tests/bao_tests/main_test.cpp \
-o out/bao_test

```

```Bash
$ ./out/bao_test
```