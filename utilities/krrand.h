#ifndef GUARD_krrand_h
#define GUARD_krrand_h

#include <random>
#include <functional>

int nrand(int n);
std::function<int()> createUniformRandGenInt(unsigned seed, int n);
std::function<double()> createUniformRandGenDouble(unsigned seed, int left, int right);
std::vector<int> permutedInts(const int n);

#endif // GUARD_krrand_h
