#ifndef GUARD_nrand_h
#define GUARD_nrand_h

#include <random>

int nrand(int n);
auto createRandGen(unsigned seed, int n);
int bigRand(std::mt19937, int n);

#endif // GUARD_nrand_h
