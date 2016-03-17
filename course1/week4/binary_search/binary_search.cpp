#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

// declare overloaded function
int binary_search(const vector<int> &a, int left, int right, int search_key);

int binary_search(const vector<int> &a, int search_key) {
  int left = 0, right = (int)a.size();
  return binary_search(a, left, right, search_key);
}

int binary_search(const vector<int> &a, int left, int right, int search_key) {
  // base case
  if (left > right) return -1;

  int mid = (left + right)/2;
  int index;
  if (search_key == a[mid])
    index = mid;
  else if (search_key < a[mid])
    index = binary_search(a, left, mid-1, search_key);
  else
    index = binary_search(a, mid+1, right, search_key);

  return index;
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cout << "Enter size of input vector: ";
  std::cin >> n;
  vector<int> a(n);
  std::cout << "Enter input vector:\n";
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cout << "Enter # of search values: ";
  std::cin >> m;
  vector<int> b(m);
  std::cout << "Enter search values:\n";
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    //std::cout << linear_search(a, b[i]) << ' ';
    std::cout << binary_search(a, b[i]) << ' ';
  }
}
