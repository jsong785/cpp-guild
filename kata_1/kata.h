#pragma once

#include <string>
#include <algorithm>

std::string ReverseString(const char *value) 
{
    std::string reversed;
    if(value != nullptr) 
    {
        std::reverse_copy(value, value + strlen(value), std::back_inserter(reversed));
    }
    return reversed;
}

