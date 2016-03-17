#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_freq(vector<int>& a, int start, int end, int element) {
  int count = 0;
  for (int i = start; i <= end; i++) {
    if (a[i] == element) ++count;
  }
  return count;
}

int get_majority_element(vector<int> &a, int left, int right) {
  int n = right-left+1;   // length of sub-vector
  if (n == 0) return -1;
  if (n == 1) return a[left];

  int k = n / 2;
  int elem_left = get_majority_element(a, left, left+k-1);
  int elem_right = get_majority_element(a, left+k, right);

  if (elem_left == elem_right)
    return elem_left;

  int left_count = get_freq(a, left, right, elem_left);
  int right_count = get_freq(a, left, right, elem_right);
  if (left_count > k)    // should be k+1?
    return elem_left;
  else if (right_count > k)   //should be k+1?
    return elem_right;
  else
    return -1;

}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()-1) != -1) << '\n';
}
