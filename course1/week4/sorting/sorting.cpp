#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>     // for rand()

using std::vector;
using std::swap;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int m = partition2(a, l, r);

  randomized_quick_sort(a, l, m - 1);
  randomized_quick_sort(a, m + 1, r);
}

void ThreeWayQuicksort(vector<int> &a, int lo, int hi) {
    if (lo >= hi) {
        return;
    }

    // random pivot selection
    int k = lo + rand() % (hi - lo + 1);
    swap(a[lo], a[k]);

    // 3-way partition
    int lt = lo, gt = hi;
    int v = a[lo];
    int i = lo;
    while (i <= gt) {
        if      (a[i] < v) swap(a[lt++], a[i++]);
        else if (a[i] > v) swap(a[i], a[gt--]);
        else               i++;
    }

    // recursive sort calls
    ThreeWayQuicksort(a, lo, lt - 1);
    ThreeWayQuicksort(a, gt + 1, hi);
}

int main() {

  std::ifstream myfile;
  myfile.open("randints.txt");
  int n;
  myfile >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    myfile >> a[i];
  }
  //randomized_quick_sort(a, 0, a.size() - 1);
  ThreeWayQuicksort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
