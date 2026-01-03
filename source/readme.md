## LƯU ý: Đăng nhập quyền ADMIN với username: "admin", password: "1"

## Hướng dẫn biên dịch khi Final

Lưu ý: Trong môi trường Linux (Codespaces), file thực thi không có đuôi `.exe`
và được chạy bằng lệnh `./cinema`. Khi biên dịch trên Windows, chương trình sẽ
tạo file `cinema.exe`.

### Bash chạy trên Window
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
    -o out/cinema.exe

cp out/cinema.exe ../release/
cp -r data ../release/
```

Run
```Bash
cd ../release
./cinema.exe
```

### Bash chạy trên Linux (Không có file .exe)
Compile
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
cp -r data ../release/
```

Run
```Bash
cd ../release
./cinema
```
