#include "hopfield.h"

#include <cmath>
#include <sstream>

namespace hopfield {

    /// @brief Constructor [private]
    hopfield::hopfield() : m_memorized(0), m_method("hebbian"), m_input(0), m_weights(0) {
        
    }
    
    /// @brief Destructor
    hopfield::~hopfield() {

    }

    /// @brief Create a new hopfield network
    /// @param size The size*size dimension that we want our network to be
    hopfield hopfield::create_new(const u32 size) {
        hopfield hf = hopfield();

        hf.m_n = size;
        hf.m_weights.resize(size);
        for (auto& weight : hf.m_weights) {
            weight.resize(size, 0);
        }
        hf.m_network.resize(size);



        return hf;
    }

    bool hopfield::imprint(const std::string& pattern) {
        std::stringstream ss(pattern); 
        i32 i = 0;
        for (; ss >> i;) {
            m_input.push_back(i);
        }

        return true;
    }

    bool hopfield::imprint(const std::vector<i32>& pattern) {
        std::vector<std::vector<i32> > input;
        input.resize(m_n);
        for (auto& in : input) {
            in.resize(m_n);
        }
        for (i32 i = 0; i < m_n; i++) {
            for (i32 j = 0; j < m_n; j++) {
                input[i][j] = pattern[i*m_n + j];
            }
        }

        // Calculate the weights

        return true; 
    }



}
