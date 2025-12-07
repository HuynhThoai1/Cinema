Nhóm N03 - Project Cinema

##Biên dịch & chạy
```Bash
$ g++ -std=c++23 \
    -I../../dto -I../../dal -I../../bus \
    main_test.cpp \
    ../../dal/MovieDAL.cpp \
    ../../dal/ShowtimeDAL.cpp \
    ../../bus/MovieBUS.cpp \
    -o ../../out/bao_test
```

```Bash
$ ../../out/bao_test
```