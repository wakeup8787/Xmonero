#include "sha3.h"

void sha3(const uint8_t* data, size_t length, uint8_t* hash) {
    SHA3 hasher;  // Tworzymy instancję klasy SHA3
    hasher.hash(data, length, hash);  // Używamy jej metody hash()
}

