#pragma once

#ifndef ASCII_H
#define ASCII_H

#include <iostream>
#include <string>

// ANSI Color Codes for Console Output
const std::string COLOR_WHITE = "\033[0m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_RED = "\033[31m";
const std::string COLOR_GRAY = "\033[90m";
const std::string COLOR_BLUE = "\033[34m";
const std::string COLOR_TURQUOISE = "\033[36m";
const std::string COLOR_YELLOW = "\033[33m";
const std::string COLOR_DARK_GREEN = "\033[32;2m";

// Function to set color using ANSI codes
void setColor(const std::string& colorCode);

#endif // ASCII_H