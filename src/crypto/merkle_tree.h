#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <vector>
#include <array>
#include "sha3.h"

class MerkleTree {
public:
    MerkleTree(const std::vector<std::vector<uint8_t>>& leaves);
    
    std::array<uint8_t, 32> getRootHash() const;
    bool verifyProof(const std::vector<uint8_t>& leaf, const std::vector<std::array<uint8_t, 32>>& proof, const std::array<uint8_t, 32>& root) const;

private:
    std::vector<std::array<uint8_t, 32>> tree;
    std::array<uint8_t, 32> computeHash(const std::vector<uint8_t>& data);
};

#endif // MERKLE_TREE_H

