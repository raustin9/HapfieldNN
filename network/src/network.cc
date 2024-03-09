#include <cstring>
#include <cstdlib>
#include <vector>
#include <mutex>
#include <thread>

#include "defines.h"
#include "core/utils.h"
#include "hopfield/hopfield.h"

std::mutex lock;

void test_network(i64 P, i64 neuron_count) {
    std::vector<f32> stable_count;
    std::vector<f32> stable_probabilities;
    std::vector<f32> unstable_probabilities;
    
    // Create random vectors of bipolar {-1,1} values
    std::vector<std::vector<i32> > patterns;
    for (std::size_t x = 0; x < P; x++) {
        std::vector<i32> v;
        for (std::size_t y = 0; y < neuron_count; y++) {
            v.push_back(core::rng());
        }
        patterns.push_back(v);
    }

    stable_count.resize(P);

    // Enumerate over the patterns
    for (u64 x = 0; x < patterns.size(); x++) {
        hopfield::hopfield hf = hopfield::hopfield::create_new(neuron_count);
        std::vector<std::vector<i32> > p;
        for (u64 y = 0; y <= x; y++) {
            p.push_back(patterns[y]);
        }
        hf.imprint_patterns(p);
        for (u64 y = 0; y <= x; y++) {
            if (hf.test_at(y)) {
                stable_count[x]++;
            }
        }
    }

    // Calculate stable probabilities
    for (u64 index = 0; index < stable_count.size(); index++) {
        f32 item = stable_count[index];
        f32 prob = item / (index + 1);
        stable_probabilities.push_back(prob);
        unstable_probabilities.push_back(1.F - prob);
    }

    lock.lock();
    // Print stable counts
    std::printf("[");
    for (const auto& s : stable_count) printf("%.0f, ", s);
    std::printf("]\n");
    
    // Print stable probabilities
    std::printf("[");
    for (const auto& s : stable_probabilities) printf("%f, ", s);
    std::printf("]\n");

    // Print unstable probabilities
    std::printf("[");
    for (const auto& s : unstable_probabilities) printf("%f, ", s);
    std::printf("]\n");
    lock.unlock();
}

int main(i32 argc, char** argv) {
    i64 P = 50;
    i64 neuron_count = 100;
    i64 num_experiments = 5;
    for (i32 i = 0; i < argc; i++) {
        if (std::strcmp(argv[i], "-P") == 0) {
            i++;
            P = std::stoi(argv[i]);
        } else if (std::strcmp(argv[i], "-N") == 0) {
            i++;
            neuron_count = std::atoi(argv[i]);
        } else if (std::strcmp(argv[i], "--num-experiments") == 0) {
            i++;
            num_experiments = std::atoi(argv[i]);
        }
    }

    std::vector<std::thread> jobs;

    // Run each experiment
    for (u64 i = 0; i < num_experiments; i++) {
        jobs.push_back(std::thread(test_network, P, neuron_count));
    }

    for (u64 i = 0; i < jobs.size(); i++) {
        jobs[i].join();
    }

    return 0; 
}
