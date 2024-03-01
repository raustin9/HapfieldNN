#include <iostream>
#include <cstdlib>
#include <map>
#include <random>
#include <time.h>
#include <vector>
#include "defines.h"

int main() {
    // srand(time(0));

    // create the 50 patterns
    std::vector<std::vector<i32> > patterns;
    patterns.resize(50);
    
    // Create 50 random vectors of length 100 of bipolar {-1,1} values
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::discrete_distribution<i32> n({1, 1});
    std::map<i32, i32> m;

    for (i32 i = 0; i < 100; i++) {
    
    }

//    for (int i = 0; i < 10000; i++) {
//        patters
//        ++m[n(gen)];
//    }
//
//    for (const auto& [num, count] : m) {
//        std::cout << num << " generated " << count << " times\n";
//    }


    return 0; 
}
