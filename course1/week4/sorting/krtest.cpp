/* Return a random integer in the range [0, n)
   Use this function instead of the standard library's rand() due to the
   inherent limitations/probs with the standard library function.  Refer
   to the discussion on pg. 135 of "Accelerated C++".
   2016-03-17 - ktr
*/

#include <cstdlib>
#include <stdexcept>
#include <ctime>

// used for the main() function
#include <iostream>
#include <vector>
#include <limits>

using std::rand;
using std::domain_error;

// used for the main() function
using std::vector;

int nrand(int n) {
    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");

    const int bucket_size = RAND_MAX / n;
    int r;

    do r = rand() / bucket_size;
    while (r >= n);

    return r;
}

int main() {

    srand(time(NULL));    // set a random seed for rand()

    int n;
    int t;
    std::cout << "Enter a value for n: ";
    std::cin >> n;

    std::cout << "Enter number of trials to run: ";
    std::cin >> t;

    vector<int> counts(n, 0);
    for (int i = 0; i < t; ++i) {
        int x = nrand(n);
        counts[x]++;
    }

    int maxval = -1;
    int minval = std::numeric_limits<int>::max();
    for (int i = 0; i < n; ++i) {
        if (counts[i] > maxval)
            maxval = counts[i];
        if (counts[i] < minval)
            minval = counts[i];
    }

    std::cout << "Max count = " << maxval << "\n";
    std::cout << "Min count = " << minval << "\n";

    return 0;
}
