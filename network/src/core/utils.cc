#include "utils.h"

namespace core {

i32 rng() {
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::discrete_distribution<i32> n({1, 1});

    return n(gen) == 0 ? -1 : 1;
}

}
