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
            P = std::stoi(argv[i]);
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

    // Run each experiment
    for (u64 i = 0; i < num_experiments; i++) {
        // Create random vectors of bipolar {-1,1} values
        std::vector<std::vector<i32> > patterns;
        for (std::size_t x = 0; x < P; x++) {
            std::vector<i32> v;
            for (std::size_t y = 0; y < neuron_count; y++) {
                v.push_back(core::rng());
            }
            patterns.push_back(v);
        }


        std::vector<u32> stable_count;
        stable_count.resize(P);

        for (u64 x = 0; x < patterns.size(); x++) {
            for (u64 y = 0; y <= x; y++) {
                std::vector<std::vector<i32> > p;
                for (u64 k = 0; k <= y; k++) {
                    p.push_back(patterns[k]);
                }


                // std::printf("p size: %lu\np[0] size: %lu\n", p.size(), p[0].size());

                hopfield::hopfield hf = hopfield::hopfield::create_new(neuron_count);
                hf.imprint_patterns(p);
                if (hf.test_all()) {
                    stable_count[y]++;
                }
            }
        }

        for (const auto& item : stable_count) {
            std::printf("%3u ", item);
        }
        std::printf("\n");
    }

    return 0; 
}
