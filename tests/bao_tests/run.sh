#!/usr/bin/env bash
set -euo pipefail

# Run from anywhere: move to Cinema root
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT_DIR"

echo "[bao_tests] Compiling..."
g++ -std=c++23 -O2 -Wall -Wextra -pedantic \
  tests/bao_tests/main_test.cpp \
  bus/MovieBUS.cpp bus/ShowtimeBUS.cpp \
  dal/MovieDAL.cpp dal/ShowtimeDAL.cpp dal/DALUtils.cpp \
  dto/Movie.cpp dto/Showtime.cpp \
  -o tests/bao_tests/main_test

echo "[bao_tests] Running..."
./tests/bao_tests/main_test
echo "[bao_tests] Done."
