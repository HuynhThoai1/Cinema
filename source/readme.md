# CINEMA N3

## Bash chạy toàn bộ chương trình khi đang ở trong ui (tạm thời dùng lệnh này)
```Bash
$ g++ -std=c++23 *.cpp ../dal/*.cpp ../dto/*.cpp ../bus/*.cpp ../utils/*.cpp -o ../out/cinema_app 

$ ../out/cinema_app
```

## LƯU ý: Đăng nhập quyền ADMIN với username: "admin", password: "1"

## Hướng dẫn biên dịch khi Final chạy ở Source 

```bash
cd source

g++ -std=c++23 \
    -Ibus \
    -Idal \
    -Idto \
    -Iui \
    -Iutils \
    ui/*.cpp \
    bus/*.cpp \
    dal/*.cpp \
    dto/*.cpp \
    utils/*.cpp \
    -o out/cinema

cp out/cinema ../release/
cp out/cinema ../release/
```

## Hướng dẫn chạy
```Bash
cd ../release
./cinema
```

Lưu ý: Trong môi trường Linux (Codespaces), file thực thi không có đuôi `.exe`
và được chạy bằng lệnh `./cinema`. Khi biên dịch trên Windows, chương trình sẽ
tạo file `cinema.exe` và có thể chạy trực tiếp bằng cách nhấn đúp.