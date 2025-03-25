#ifndef SHA3_H
#define SHA3_H

#include <string>

class SHA3 {
public:
    static std::string hash(const std::string& input);
};
void sha3(const uint8_t* data, size_t length, uint8_t* hash);

#endif // SHA3_H

