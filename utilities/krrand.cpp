/*
krrand.cpp:  Miscellaneous utility functions involving random number generation
             and random number functionality.
last update: 2016-05-21
*/

#include <cstdlib>       // std::rand
#include <stdexcept>
#include <ctime>

//#include <iostream>    // for debugging only

#include <chrono>
#include <random>
#include <functional>
#include <algorithm>     // std::random_shuffle
#include <vector>

using std::rand;
using std::domain_error;

/* Return a random integer in the range [0, n)
   Use this function instead of the standard library's rand() due to the
   inherent limitations/probs with the standard library function.  Refer
   to the discussion on pg. 135 of "Accelerated C++".
   2016-03-17 - ktr
*/
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
std::function<int()> createUniformRandGenInt(unsigned seed, int n) {
    if (seed == 0u) {
        seed = time(NULL);
        //std::cout << "seed = " << seed << "\n";
    }
    std::mt19937 generator(seed);   // mt19937 is a standard mersenne_twister_engine
    std::uniform_int_distribution<int> distribution(0, n-1);
    std::function<int()> getRand = std::bind(distribution, generator);
    return getRand;
}

/* Create and return an real-valued random number generator
   params:  an unsigned seed value "seed",
            an integer "left" indicating starting value of desired range
            an integer "right" indicating ending value (exclusive) of desired range
   returns: a generator function that produces random real values in interval [left, right)
*/
std::function<double()> createUniformRandGenDouble(unsigned seed, int left, int right) {
    if (seed == 0u) {
        seed = time(NULL);
        //std::cout << "seed = " << seed << "\n";
    }
    std::mt19937 generator(seed);   // mt19937 is a standard mersenne_twister_engine
    std::uniform_real_distribution<double> distribution(left, right);
    std::function<double()> getRand = std::bind(distribution, generator);
    return getRand;
}

// create a vector of unique, randomly permuted integers in range [0, n)
std::vector<int> permutedInts(const int n) {
    std::vector<int> myvector(n);
    // init vector with integers from 0 to n-1
    for (int i=0; i<n; ++i)
        myvector[i] = i;
    // randomly permute elements of vector using nrand() as the RNG
    std::random_shuffle(myvector.begin(), myvector.end(), nrand);
    return myvector;
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
