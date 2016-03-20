#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;

  int m = 1;
  while (true) {
    if (n <= 2*m) {
      summands.push_back(n);
      break;
    }
    else {
      summands.push_back(m);
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
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
