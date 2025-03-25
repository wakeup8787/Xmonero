#include "lwe_generator.h"
#include "crypto/merkle_tree.h"
#include "crypto/random.h"
#include "giant_steps.h"
#include <cmath>
#include <stdexcept>

// Stałe konfiguracyjne
constexpr int RNG_MIN = -10;
constexpr int RNG_MAX = 10;
constexpr int ERROR_MIN = -2;
constexpr int ERROR_MAX = 2;
constexpr int BASE_MATRIX_SIZE = 16;
constexpr int CPU_POWER_DIVISOR = 100;

LWEGenerator::LWEGenerator(uint64_t block_hash, uint64_t difficulty_hash, int cpu_power) 
    : block_hash(block_hash), difficulty_hash(difficulty_hash), cpu_power(cpu_power) {}

void LWEGenerator::generate_problem() {
    adjust_difficulty();

    // Dynamiczne dostosowanie rozmiaru macierzy do mocy CPU
    const int MATRIX_SIZE = BASE_MATRIX_SIZE + (cpu_power / CPU_POWER_DIVISOR);
    A.resize(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE));
    b.resize(MATRIX_SIZE);
    e.resize(MATRIX_SIZE);

    Random rng(block_hash ^ difficulty_hash);

    // Generowanie macierzy A, wektora b i błędu e
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            A[i][j] = rng.next_int(RNG_MIN, RNG_MAX);
        }
        b[i] = rng.next_int(RNG_MIN, RNG_MAX);
        e[i] = rng.next_int(ERROR_MIN, ERROR_MAX);
    }

    apply_wavelet_transform(); // Kodowanie falowe przed podziałem na puzzle
    split_into_puzzles();
    build_merkle_tree();
}

void LWEGenerator::apply_wavelet_transform() {
    int N = A.size();
    if (N % 2 != 0) {
        throw std::runtime_error("Matrix columns must be even for wavelet transform.");
    }

    // Zastosowanie transformacji falowej
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j += 2) {
            int a = A[i][j];
            int b = A[i][j + 1];
            A[i][j] = (a + b) / 2;
            A[i][j + 1] = a - b;
        }
    }
}

void LWEGenerator::split_into_puzzles() {
    if (puzzles.empty()) {
        puzzles.resize(BASE_MATRIX_SIZE); // Domyślna liczba puzzli
    }

    if (A.size() % puzzles.size() != 0) {
        throw std::runtime_error("Matrix size is not divisible by the number of puzzles.");
    }

    int puzzle_size = A.size() / puzzles.size();
    for (int i = 0; i < puzzles.size(); i++) {
        std::vector<int> puzzle;
        puzzle.reserve(puzzle_size * (A[0].size() + 2)); // Rezerwacja pamięci dla puzzli
        for (int j = 0; j < puzzle_size; j++) {
            puzzle.insert(puzzle.end(), A[i * puzzle_size + j].begin(), A[i * puzzle_size + j].end());
            puzzle.push_back(b[i * puzzle_size + j]);
            puzzle.push_back(e[i * puzzle_size + j]);
        }
        puzzles[i] = puzzle;
    }
}

void LWEGenerator::build_merkle_tree() {
    if (puzzles.empty()) {
        throw std::runtime_error("Cannot build Merkle tree: no puzzles available.");
    }

    std::vector<crypto::hash> puzzle_hashes;
    for (const auto& puzzle : puzzles) {
        puzzle_hashes.push_back(crypto::cn_fast_hash(puzzle.data(), puzzle.size() * sizeof(int)));
    }
    merkle_root = MerkleTree::compute_root(puzzle_hashes);
}

int LWEGenerator::get_puzzle_count() const {
    return puzzles.size();
}

std::vector<std::vector<int>> LWEGenerator::get_puzzles() const {
    return puzzles;
}

crypto::hash LWEGenerator::get_merkle_root() const {
    return merkle_root;
}