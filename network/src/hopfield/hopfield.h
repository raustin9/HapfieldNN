#pragma once
#include "defines.h"

#include <string>
#include <vector>

namespace hopfield {

class hopfield {
    public:
        ~hopfield();

        static hopfield create_new(u32 neuron_count);
        bool imprint_patterns(const std::vector<std::vector<i32> >& pattern);
        void print_weights();
        void print_patterns();
        void clear();
        bool test_all();
        bool test_at(u64 index);
        std::string get_output();

    private:
        hopfield();
        i32 _sigma(f64 h);
        u32 m_n;
        std::string m_method;
        std::vector<std::vector<f64> > m_weights;
        std::vector<std::vector<i32> > m_network;
        std::vector<std::vector<i32> > m_patterns_remembered;
};

}
