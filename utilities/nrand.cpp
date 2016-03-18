/* Return a random integer in the range [0, n)
   Use this function instead of the standard library's rand() due to the
   inherent limitations/probs with the standard library function.  Refer
   to the discussion on pg. 135 of "Accelerated C++".
   2016-03-17 - ktr
*/

#include <cstdlib>
#include <stdexcept>
#include <ctime>

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
