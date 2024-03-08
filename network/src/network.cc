#include <cstring>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "defines.h"
#include "core/utils.h"
#include "hopfield/hopfield.h"

int main(i32 argc, char** argv) {
    i64 P = -1;
    i64 neuron_count = -1;
    i64 num_experiments = -1;
    for (i32 i = 0; i < argc; i++) {
        if (std::strcmp(argv[i], "-P") == 0) {
            // Number of patterns to encode 
            i++;
            P = std::atoi(argv[i]);
            std::printf("P:  %ld\n", P);
        } else if (std::strcmp(argv[i], "-N") == 0) {
            // Number of neurons for the networ 
            i++;
            neuron_count = std::atoi(argv[i]);
            std::printf("NC: %ld\n", neuron_count);
        } else if (std::strcmp(argv[i], "--num-experiments") == 0) {
            // Number of experiments we want to run
            i++;
            num_experiments = std::atoi(argv[i]);
            std::printf("NE: %ld\n", num_experiments);
        } 
    }


    hopfield::hopfield hf = hopfield::hopfield::create_new(neuron_count); // create 100x100 hfnn

    // Create 50 random vectors of length 100 of bipolar {-1,1} values
    std::vector<std::vector<i32> > patterns; // the 50 bipolar vectors to imprint
    for (std::size_t x = 0; x < P; x++) {
        std::vector<i32> v;
        for (std::size_t i = 0; i < neuron_count; i++) {
            v.push_back(core::rng());
        }
        patterns.push_back(v);
    }
    std::cout << "Pattern Count: " << patterns.size() << "\n";
    std::cout << "Pattern Dimension: " << patterns[0].size() << "\n";


    // Imprint the patterns to the network
    if (!hf.imprint_patterns(patterns)){
        std::printf("Invalid pattern\n");
    }

    if (!hf.test_all()) {
        std::printf("UNSTABLE\n");
    } else {
        std::printf("SUCCESS\n");
    }
    // hf.print_weights();
    // hf.print_patterns();

    return 0; 
}
