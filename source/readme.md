# CINEMA N3

## Bash chạy toàn bộ chương trình khi đang ở trong ui(tạm thời dùng lệnh này)
```Bash
$ g++ -std=c++23 *.cpp ../dal/*.cpp ../dto/*.cpp ../bus/*.cpp ../utils/*.cpp -o ../out/cinema_app 

$ ../out/cinema_app
```

## LƯU ý: Đăng nhập quyền ADMIN với username: "admin", password: "1"

## Hướng dẫn biên dịch

```bash
cd source

g++ ui/main.cpp \
   ui/*.cpp \
   bus/*.cpp \
   dal/*.cpp \
   dto/*.cpp \
   utils/*.cpp \
   -o out/cinema

cp out/cinema ../release/
cp -r data ../release/
```

## Hướng dẫn chạy
```Bash
cd release
./cinema
```

