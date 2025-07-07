#include "utils.h"
#include <cassert>

std::vector<std::string> split(std::string& str, char del)
{
    std::vector<std::string> res;

    const char* start = str.c_str();
    const char* end   = start;

    while (*end) {
        if (*end == del) {
            res.emplace_back(start, end);
            start = end + 1;
        }
        ++end;
    }

    res.emplace_back(start, end);
    return res;
}

SQUARE str_to_square(std::string& str){
    if (str == "-") return SQUARE::none;

    assert(str.size() == 2);

    // add row
    int res = (str[1] - 48 - 1) * 8;

    // add column
    res += 8 - str[0] - 97;

    return (SQUARE) res;
}

std::string square_to_str(SQUARE sqr){
    if (sqr == SQUARE::none) return "-";

}
