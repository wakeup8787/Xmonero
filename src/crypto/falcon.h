#ifndef FALCON_H
#define FALCON_H

#include <vector>
#include <string>

class Falcon {
public:
    static std::pair<std::vector<uint8_t>, std::vector<uint8_t>> generateKeyPair();
    static std::vector<uint8_t> signMessage(const std::string& message, const std::vector<uint8_t>& privateKey);
    static bool verifySignature(const std::string& message, const std::vector<uint8_t>& signature, const std::vector<uint8_t>& publicKey);
};

#endif // FALCON_H

