#include <iostream>
#include <cstdlib>
#include <vector>

#include "defines.h"
#include "core/utils.h"

int main() {
    constexpr u32 P = 50; // Number of vectors we want to encode

    // create the 50 patterns
    std::vector<std::vector<i32> > patterns;
    patterns.resize(P);
    
    // Create 50 random vectors of length 100 of bipolar {-1,1} values
    for (std::size_t x = 0; x < P; x++) {
        std::vector<i32> v;
        for (std::size_t i = 0; i < 100; i++) {
            // If the number generated was 0 then make it -1. Otherwise keep it
            v.push_back(core::rng());
        }
        patterns.push_back(v);
    }

    

//    for (const auto& p : patterns) {
//        for (const auto& i : p) {
//            std::cout << i << " ";
//        }
//        std::cout << "\n";
//    }

    std::cout << "Pattern Count: " << patterns.size() << "\n";

    return 0; 
}
