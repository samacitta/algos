
#include <iostream>
#include "krrand.h"
#include <vector>

int main() {
    unsigned seed = 0;
    int n = 100;
    auto getRandInt = createUniformRandGenInt(seed, n);
    for(int n=0; n<10; ++n)
        std::cout << getRandInt() << ' ';
    std::cout << '\n';

    int left = 0;
    int right = 1;
    auto getRandDouble = createUniformRandGenDouble(seed, left, right);
    for(int n=0; n<10; ++n)
        std::cout << getRandDouble() << ' ';
    std::cout << '\n';

    n = 10;
    std::vector<int> myvector = permutedInts(n);
    // print out content:
    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}
