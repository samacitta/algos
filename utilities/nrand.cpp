/* Return a random integer in the range [0, n)
   Use this function instead of the standard library's rand() due to the
   inherent limitations/probs with the standard library function.  Refer
   to the discussion on pg. 135 of "Accelerated C++".
   2016-03-17 - ktr
*/

#include <cstdlib>
#include <stdexcept>
#include <ctime>

#include <iostream>    // for debugging only

#include <chrono>
#include <random>
#include <functional>

using std::rand;
using std::domain_error;

int nrand(int n) {
    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");

    const int bucket_size = RAND_MAX / n;
    int r;

    do r = rand() / bucket_size;
    while (r >= n);

    return r;
}

/* Create and return an integer random number generator
   params:  an unsigned seed value "seed",
            an integer "n" defining the distribution range
   returns: a generator function that produces random values between 0 and
            n-1
*/
std::function<int()> createUniformRandGen(unsigned seed, int n) {
    if (seed == 0u) {
        seed = time(NULL);
        std::cout << "seed = " << seed << "\n";
    }
    std::mt19937 generator(seed);   // mt19937 is a standard mersenne_twister_engine
    std::uniform_int_distribution<int> distribution(0, n-1);
    std::function<int()> getRand = std::bind(distribution, generator);
    return getRand;
}
/*
int main() {
    unsigned seed = 0;
    int n = 100;
    auto getRand = createRandGen(seed, n);

    for(int n=0; n<10; ++n)
        std::cout << getRand() << ' ';
    std::cout << '\n';

    return 0;
}
*/
