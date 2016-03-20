/* Pairwise Distinct Summands:  Represent a given positive integer n as a sum
       of as many pairwise distinct positive integers as possible.
   version 2:  storeage optimization - Instead of storing and returning vector
       of all of the summands, just store the final two summands as we know
       that the correct answer is the sum of 1 to the final value for m plus
       the final value for n.
*/

#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;

  int m = 1;
  while (true) {
    if (n <= 2*m) {
      summands.push_back(m-1);
      summands.push_back(n);
      break;
    }
    else {
      //summands.push_back(m);
      n -= m;
      ++m;
    }
  }

  return summands;
}

int main() {
  int n;
  std::cout << "Enter an integer:\n";
  std::cin >>  n;
  vector<int> summands = optimal_summands(n);
  std::cout << "optimal # of summands = " << summands[0] + 1 << "\n";
  std::cout << "summands = ";
  for (int i = 1; i <= summands[0]; ++i) {
    std::cout << i << " ";
  }
  std::cout << summands[1] << "\n";

  return 0;
}
