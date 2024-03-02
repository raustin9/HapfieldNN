#pragma once
#include "defines.h"

#include <string>
#include <vector>

namespace hopfield {

class hopfield {
    public:
        static hopfield create_new(u32 neuron_count); // builder function
        ~hopfield();


        bool imprint(const std::string& pattern);
        bool imprint(const std::vector<i32>& pattern, u32 k);
        std::string get_output();

        void clear();

    private:
    hopfield();
    u32 m_memorized;
    u32 m_n;
    std::string m_method;
    std::vector<i32> m_input;
    std::vector<std::vector<f64> > m_weights;
    std::vector<std::vector<i8> > m_network;
};

}
