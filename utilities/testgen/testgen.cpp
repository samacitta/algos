/** Generates various random files used for testing by other programs.
 *
 * 2016-05-05 - ktr.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>

#include <random>           //
#include <functional>       // std::bind
#include <algorithm>    // std::random_shuffle

//#include "nrand.h"    // not needed at this time - ktr

using std::vector;

using namespace std;

// Creates a vector of the specified size containing random values
// ranging from [0, n)
vector<int> createRandInts() {
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

    return randomVals;
}

// create a vector of sequential integers in range [0, n) and then create a random
// permutation of these integers
vector<int> createShuffledInts() {
    int numvals;
    std::cout << "Enter number of desired values: ";
    std::cin >> numvals;
    vector<int> values(numvals);

    // populate vector with values in range [0, n)
    for (int i = 0; i < values.size(); ++i) {
        values[i] = i;
    }

    // shuffle the int values
    std::random_shuffle ( values.begin(), values.end() );

    return values;
}

void writeDataToFile(vector<int>& values, string filename) {
    // write vector values to a text file
    ofstream myfile;
    // replace content of file if it already exists
    myfile.open(filename, ios::trunc);
    // first line is number of values in file
    myfile << values.size() << "\n";
    for (vector<int>::const_iterator iter = values.begin();
          iter != values.end(); ++iter) {
        myfile << *iter << " ";
    }
    myfile.close();

    cout << values.size() << " integers written to file: " << filename << endl;
}

int main()
{
    // read in the string that determines which function to run
    string functionFlag;
    cout << "Enter function identifier: " << endl;
    cin >> functionFlag;

    // for valid functionFlag, run appropriate function
    if (functionFlag == "1") {
        // create a vector of random values
        vector<int> randints = createRandInts();
        // write vector of values to a file
        string filename = "random_ints.txt";
        writeDataToFile(randints, filename);
    } else if (functionFlag == "2") {
        // create a random permutation of integer values in the range [0,n)

        vector<int> permutedInts = createShuffledInts();
        string filename = "permuted_ints.txt";
        writeDataToFile(permutedInts, filename);
    } else {
        cout << "Invalid function identifier, program aborted..." << std::endl;
    }

    return 0;
}

