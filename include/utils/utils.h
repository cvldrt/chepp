#pragma once

#include "board/enums.h"
#include <string>
#include <vector>

std::vector<std::string> split(std::string& str, char del);

SQUARE str_to_square(std::string& str);

std::string square_to_str(SQUARE sqr);
