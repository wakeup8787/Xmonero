#ifndef LWE_GENERATOR_H
#define LWE_GENERATOR_H

#pragma once
#include "crypto/hash.h"
#include <vector>

class LWEGenerator {
    public:
        LWEGenerator(uint64_t block_hash, uint64_t difficulty_hash, int cpu_power);
        
        void generate_problem();
        std::vector<std::vector<int>> get_puzzles() const;
        crypto::hash get_merkle_root() const;
        int get_puzzle_count() const;  // Nowa funkcja zwracająca liczbę puzzli

        static constexpr int RNG_MIN = -10;  // Minimalna wartość losowa dla macierzy A i wektora b
        static constexpr int RNG_MAX = 10;  // Maksymalna wartość losowa dla macierzy A i wektora b
        static constexpr int ERROR_MIN = -2;  // Minimalna wartość błędu w wektorze e
        static constexpr int ERROR_MAX = 2;  // Maksymalna wartość błędu w wektorze e
        static constexpr int BASE_MATRIX_SIZE = 16;  // Bazowy rozmiar macierzy A
        static constexpr int BASE_PUZZLES = 4;  // Bazowa liczba puzzli
        static constexpr int CPU_POWER_DIVISOR = 200;  // Współczynnik skalowania puzzli względem mocy CPU
        static constexpr int MAX_PUZZLES = 16;  // Maksymalna liczba puzzli
    
    private:
        uint64_t block_hash;
        uint64_t difficulty_hash;
        int cpu_power;  // Moc CPU górnika
    
        std::vector<std::vector<int>> A;
        std::vector<int> b;
        std::vector<int> e;
        
        std::vector<std::vector<int>> puzzles;
        crypto::hash merkle_root;
    
        void adjust_difficulty();  // Nowa funkcja dynamicznego skalowania puzzli
        void split_into_puzzles();
        void build_merkle_tree();
        void apply_wavelet_transform(); 
    };

    #endif // LWE_GENERATOR_H