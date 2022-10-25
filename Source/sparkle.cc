#include <string>
#include <vector>
#include <iostream>

#include "spakle.hpp"

namespace sparkle {
    /// @brief The helper function to print the sequence of values.
    template<typename T>
    void printChain(std::vector<T>& chain){
        for (auto item : chain) std::cout << item << "\n";
    }
}