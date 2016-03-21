#ifndef GUARD_nrand_h
#define GUARD_nrand_h

#include <random>

int nrand(int n);
std::function<int()> createUniformRandGen(unsigned seed, int n);

#endif // GUARD_nrand_h
