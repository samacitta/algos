// used for the main() function/
#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>
#include <ctime>

#include "nrand.h"

using std::vector;

using namespace std;

int main()
{
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
