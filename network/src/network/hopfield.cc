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
    hopfield hopfield::create_new(const u32 neuron_count) {
        hopfield hf = hopfield();

        hf.m_n = neuron_count;
        hf.m_weights.resize(neuron_count);
        for (auto& weight : hf.m_weights) {
            weight.resize(neuron_count, 0);
        }
        hf.m_network.resize(neuron_count);

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

    bool hopfield::imprint(const std::vector<i32>& pattern, u32 k) {
        f64 coefficient = 1.F / m_n;

        // Calculate the weights
        for (i32 i = 0; i < m_n; i++) {
            for (i32 j = 0; j < m_n; j++) {
                m_weights[i][j] = coefficient * pattern[i] * pattern[j];
            }
        }

        for (std::size_t i = 0; i < m_weights.size(); i++) {
            m_weights[i][i] = 0.F;
        }
        

        return true; 
    }



}
