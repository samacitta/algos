#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using std::vector;

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

/* dynamic programming implementation */
vector<int> kr_optimal_sequence(int n) {
  vector<int> min_vals(n+1, 0);    // min values for each 1<=i<=n
  vector<int> preds(n+1, 0);       // predecessor index for each min value

  for (size_t i = 2; i <= n; ++i) {
    int pred = -1;
    int minimum = INT_MAX;
    int temp, temp_ndx;
    if (i % 3 == 0) {
      temp_ndx = i / 3;
      temp = min_vals[temp_ndx] + 1;
      if (temp < minimum) {
        minimum = temp;
        pred = temp_ndx;
      }
    }
    if (i % 2 == 0) {
      temp_ndx = i / 2;
      //std::cout << "temp_ndx = " << temp_ndx << "\n";
      temp = min_vals[temp_ndx] + 1;
      //std::cout << "temp = " << temp << "\n";
      if (temp < minimum) {
        minimum = temp;
        pred = temp_ndx;
      }
    }
    temp_ndx = i-1;
    temp = min_vals[temp_ndx] + 1;
    if (temp < minimum) {
        minimum = temp;
        pred = temp_ndx;
    }

    // store the determined minimum and predecessor for this value of n
    //std::cout << i << ": " << minimum << "\n";
    min_vals[i] = minimum;
    preds[i] = pred;

  }

  // for testing...
  std::cout << "min # of ops = " << min_vals[n] << "\n";

  // work backwards to construct the optimal sequence
  vector<int> result;
  int p = n;
  result.push_back(n);
  while (p > 1) {
    p = preds[p];
    result.push_back(p);
  }
  reverse(result.begin(), result.end());

  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = kr_optimal_sequence(n);
  std::cout << "min # of ops = " << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
