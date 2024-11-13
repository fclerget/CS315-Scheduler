#pragma once

#ifndef ASCII_H
#define ASCII_H

#include <iostream>
#include <string>

// ANSI Color Codes for Console Output
const std::string COLOR_WHITE = "\033[0m";          // New frame boundary
const std::string COLOR_GREEN = "\033[32m";         // Running task
const std::string COLOR_RED = "\033[31m";           // Preempted task
const std::string COLOR_GRAY = "\033[90m";          // No task
const std::string COLOR_BLUE = "\033[34m";          // Task created
const std::string COLOR_TURQUOISE = "\033[36m";     // Task created and executed 
const std::string COLOR_YELLOW = "\033[33m";        // Task created but preempted
const std::string COLOR_ORANGE = "\033[38;5;208m";  // Time unit "run" without task

// Function to set color using ANSI codes
void setColor(const std::string& colorCode);

#endif // ASCII_H