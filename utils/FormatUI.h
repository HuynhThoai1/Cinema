#ifndef FORMAT_UI_H
#define FORMAT_UI_H

#include <string>
#include <iostream>

// ANSI color macros
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

void clearScreen();
void printHeader(const std::string &title);

#endif // FORMAT_UI_H
