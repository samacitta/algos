/** Generates various random files used for testing by other programs.
 *
 * 2016-03-17 - ktr.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <random>           //
#include <functional>       // std::bind

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
    unsigned seed = time(NULL);
    std::mt19937 generator(seed);   // mt19937 is a standard mersenne_twister_engine
    std::uniform_int_distribution<int> distribution(0, maxval-1);
    auto getRand = std::bind(distribution, generator);

    for (int i = 0; i < numvals; ++i) {
        //randomVals[i] = nrand(maxval);
        randomVals[i] = getRand();
    }

    // write vector values to a text file
    ofstream myfile;
    // replace content of file if it already exists
    myfile.open("randints.txt", ios::trunc);
    // first line is number of values in file
    myfile << randomVals.size() << "\n";
    for (vector<int>::const_iterator iter = randomVals.begin();
          iter != randomVals.end(); ++iter) {
        myfile << *iter << " ";
    }
    myfile.close();
    return 0;
}

