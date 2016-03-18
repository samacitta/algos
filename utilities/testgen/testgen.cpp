/** Generates various random files used for testing by other programs.
 *
 * 2016-03-17 - ktr.
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

#include "nrand.h"

using std::vector;

using namespace std;

// Creates a vector of the specified size containing random values
// ranging from [0, n)


int main()
{
    std::cout << "RAND_MAX = " << RAND_MAX << "\n";

    srand(time(NULL));    // set a random seed for rand()

    int numvals;
    int maxval;

    std::cout << "Enter number of desired values: ";
    std::cin >> numvals;

    std::cout << "Enter an integer maximum for values: ";
    std::cin >> maxval;

    // create a vector of random values
    vector<int> randomVals(numvals);
    for (int i = 0; i < numvals; ++i) {
        randomVals[i] = nrand(maxval);
    }

    // write vector values to a text file
    for (vector<int>::const_iterator iter = randomVals.begin();
          iter != randomVals.end(); ++iter) {
        std::cout << *iter << std::endl;
    }



    return 0;
}

