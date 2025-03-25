#include "miner.h"
#include "crypto/sha3.h"
#include "blockchain.h"

bool Miner::solvePuzzle() {
    // 🔹 Generowanie macierzy LWE (Proof of Quantum - PoQ)
    std::vector<std::vector<int>> A = PuzzleGenerator::generateMatrix();
    std::vector<int> b = PuzzleGenerator::generateVector();

    // 🔹 Rozwiązywanie problemu LWE
    LWESolver solver(A, b);
    std::vector<int> solution = solver.solve();  // Preferowane int zamiast double

    // 🔹 Hashujemy rozwiązanie SHA-3
    crypto::hash solution_hash;
    std::string hashInput = PuzzleGenerator::serializeSolution(solution);
    sha3((const uint8_t*)hashInput.data(), hashInput.size(), (uint8_t*)&solution_hash);

    // 🔹 Weryfikacja PoQ na blockchainie
    if (!Blockchain::verifyPuzzle(A, b, solution)) {
        MERROR("❌ LWE solution is incorrect!");
        return false;
    }

    // 🔹 Tworzenie podpisu Falcon dla bloku
    std::string falcon_signature = Falcon::signMessage(hashInput, privateKey);
    
    // ✅ Zwracamy true, jeśli wszystko poszło dobrze
    return true;
}

