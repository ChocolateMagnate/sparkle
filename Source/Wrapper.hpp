#pragma once
#include <vector>
#include <string>

namespace sparkle {
    std::vector<const char*> tokeniseByPunctuation(std::string& source);
    std::vector<const char*> tokeniseByPunctuation(const char* source);
    
}