#include "hash.h"

string hashPassword(const std::string& password) {
    std::string hashed;
    const int prime = 31;

    for (size_t i = 0; i < password.length(); ++i) {
        char c = password[i];
        // Простейшее хеширование: XOR + смещение + примитивная "солянка"
        char hashedChar = (c ^ prime) + (i % 7);
        hashed += hashedChar;
    }

    return hashed;
}