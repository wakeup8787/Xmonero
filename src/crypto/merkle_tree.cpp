#include "merkle_tree.h"

MerkleTree::MerkleTree(const std::vector<std::vector<uint8_t>>& leaves) {
    if (leaves.empty()) return;

    std::vector<std::array<uint8_t, 32>> hashes;
    for (const auto& leaf : leaves) {
        hashes.push_back(computeHash(leaf));
    }

    while (hashes.size() > 1) {
        std::vector<std::array<uint8_t, 32>> newLevel;
        for (size_t i = 0; i < hashes.size(); i += 2) {
            if (i + 1 < hashes.size()) {
                std::vector<uint8_t> combined(hashes[i].begin(), hashes[i].end());
                combined.insert(combined.end(), hashes[i + 1].begin(), hashes[i + 1].end());
                newLevel.push_back(computeHash(combined));
            } else {
                newLevel.push_back(hashes[i]);
            }
        }
        hashes = newLevel;
    }
    
    tree = hashes;
}

std::array<uint8_t, 32> MerkleTree::getRootHash() const {
    return tree.empty() ? std::array<uint8_t, 32>{} : tree.front();
}

bool MerkleTree::verifyProof(const std::vector<uint8_t>& leaf, const std::vector<std::array<uint8_t, 32>>& proof, const std::array<uint8_t, 32>& root) const {
    std::array<uint8_t, 32> hash = computeHash(leaf);
    for (const auto& sibling : proof) {
        std::vector<uint8_t> combined(hash.begin(), hash.end());
        combined.insert(combined.end(), sibling.begin(), sibling.end());
        hash = computeHash(combined);
    }
    return hash == root;
}

std::array<uint8_t, 32> MerkleTree::computeHash(const std::vector<uint8_t>& data) {
    return SHA3::sha3_256(data);
}

