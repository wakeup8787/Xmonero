#include "falcon.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "falcon-512.h"  // Właściwa biblioteka Falcon PQC

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> Falcon::generateKeyPair() {
    uint8_t sk[FALCON_SIG_PADDED_SIZE(512)];
    uint8_t pk[FALCON_PUBKEY_SIZE(512)];

    // Generowanie kluczy Falcon-512
    if (falcon_keygen_make(pk, sk, 512) != 0) {
        throw std::runtime_error("Falcon key generation failed!");
    }

    return {std::vector<uint8_t>(pk, pk + sizeof(pk)), 
            std::vector<uint8_t>(sk, sk + sizeof(sk))};
}

std::vector<uint8_t> Falcon::signMessage(const std::string& message, const std::vector<uint8_t>& privateKey) {
    uint8_t signature[FALCON_SIG_PADDED_SIZE(512)];
    size_t sig_len = sizeof(signature);

    if (falcon_sign_dyn(signature, &sig_len, 
                        reinterpret_cast<const uint8_t*>(message.c_str()), message.size(), 
                        privateKey.data(), privateKey.size(), 512) != 0) {
        throw std::runtime_error("Falcon signing failed!");
    }

    return std::vector<uint8_t>(signature, signature + sig_len);
}

bool Falcon::verifySignature(const std::string& message, const std::vector<uint8_t>& signature, const std::vector<uint8_t>& publicKey) {
    return falcon_verify_dyn(signature.data(), signature.size(), 
                             reinterpret_cast<const uint8_t*>(message.c_str()), message.size(), 
                             publicKey.data(), publicKey.size(), 512) == 0;
}

