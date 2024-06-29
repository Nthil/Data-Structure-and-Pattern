#include "Combination.h"

Combination::Combination(size_t aN, size_t aK) : fN(aN), fK(aK) {}

size_t Combination::getN() const {
    return fN;
}

size_t Combination::getK() const {
    return fK;
}

unsigned long long Combination::operator()() const {
    if (fK > fN) {
        return 0ull;
    }

    unsigned long long result = 1;
    size_t smaller = (fK < fN - fK) ? fK : fN - fK;
    size_t f = fN;

    for (size_t i = 1; i <= smaller; i++) {
        result *= f--;
        result /= i;
    }

    return result;
}
