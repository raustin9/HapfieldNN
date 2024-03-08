#include "hopfield.h"

#include <cstdio>
#include <stdexcept>

namespace hopfield {

    /// [private]
    /// @brief Constructor 
    hopfield::hopfield() : m_method("hebbian"), m_weights(0) {
        
    }


    /// [private]
    /// @brief Sigma compare function for node in network
    i32 hopfield::_sigma(f64 h) {
        return h < 0 ? -1 : 1;
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

    /// @brief Imprint a pattern of length m_n to the netowrk
    /// @param pattern The pattern to imprint
    /// @returns Whether it was successful
    bool hopfield::imprint_patterns(const std::vector<std::vector<i32>>& patterns) {
        m_patterns_remembered = patterns;
        if (patterns[0].size() != m_n) {
            char msg[50];
            std::sprintf(msg, "Expected %u dimension of pattern. Got %lu", m_n, patterns[0].size());
            throw std::runtime_error(msg);
        }

        f64 coefficient = 1.F / m_n;

        // Calculate the weight matrix
        for (u64 i = 0; i < m_n; i++) {
            for (u64 j = 0; j < m_n; j++) {
                f64 num = 0;
                for (u64 k = 0; k < patterns.size(); k++) {
                    num += patterns[k][i] * patterns[k][j];
                }
                m_weights[i][j] = num * coefficient;
            }
        }

        // Make sure diagonals are 0
        for (u64 i = 0; i < m_weights.size(); i++) {
            m_weights[i][i] = 0.F;
        }

        // Make sure it is reflected
        for (u64 i = 0; i < m_n; i++) {
            for (u64 j = 0; j < m_n; j++) {
                if (m_weights[j][i] != m_weights[i][j]) {
                    return false;
                }
            }
        }


        return true; 
    }


    /// @brief Test all inputs to see if any are unstable
    bool hopfield::test_all() {
        for (const auto& pattern : m_patterns_remembered) {
            for (u64 i = 0; i < m_n; i++) {
                f64 h_i = 0;
                for (u64 j = 0; j < m_n; j++) {
                    h_i += m_weights[i][j] * pattern[j];
                }
                f64 s_prime = _sigma(h_i);
                if (s_prime != pattern[i]) {
                    return false;
                }
            }
        }

        return true;
    }


    /// @brief Print the weight matrix of the netowrk
    void hopfield::print_weights() {
        for (const auto& row : m_weights) {
            for (const auto& item : row) {
                std::printf("%.3lf ", item);
            }
            std::printf("\n");
        }
    }


    /// @brief Print each of the patterns the netowrk is remembering
    void hopfield::print_patterns() {
        std::size_t i = 0;
        for (const auto& pattern : m_patterns_remembered) {
            std::printf("Pattern %lu:", i);
            for (const auto& item : pattern) {
                std::printf(" %d", item);
            }
            std::printf("\n");
            i++;
        }
    }


    /// @brief Clear the network
    void hopfield::clear() {
        m_weights.clear();
        m_network.clear();
        m_patterns_remembered.clear();
        m_n = 0;
    }
}
