Nhóm N03 - Project Cinema

##Biên dịch & chạy
```Bash
$ g++ -std=c++23 \
  tests/bao_tests/main_test.cpp \
  bus/MovieBUS.cpp bus/ShowtimeBUS.cpp \
  dal/MovieDAL.cpp dal/ShowtimeDAL.cpp \
  dto/Movie.cpp dto/Showtime.cpp \
  -o out/bao_test

```

```Bash
$ ./out/bao_test

```