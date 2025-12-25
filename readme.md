# CINEMA N3

## Bash chạy toàn bộ chương trình
``` Bash
$ g++ -std=c++23 utils/*.cpp ui/*.cpp dal/*.cpp dto/*.cpp bus/*.cpp -o out/cinema_app
```

``` Bash
$ out/cinema_app
```
## Bash chạy toàn bộ chương trình khi đang ở trong ui(tạm thời dùng lệnh này)
```Bash
$ g++ -std=c++23 *.cpp ../dal/*.cpp ../dto/*.cpp ../bus/*.cpp ../utils/*.cpp -o ../out/cinema_app 

$ ../out/cinema_app
```
TODO:
-Chỉnh lại FoodUI, RevenueUI theo giao diện đồng bộ chung( tham khảo các file UI khác)
