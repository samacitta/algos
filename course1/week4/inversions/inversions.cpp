/* inversions.cpp - Compute the number of inversions of the elements of an
       Mergesort.

    2016-03-19 - ktr.
*/

#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

long long krmerge(vector<int> &a, vector<int> &aux, size_t left, size_t mid, size_t right) {
    long long inversions = 0;

    // copy to aux
    for (size_t k = left; k <= right; ++k) {
        aux[k] = a[k];
    }

    // merge back to a
    size_t i = left, j = mid+1;
    for (size_t k = left; k <= right; ++k) {
        if      (i > mid)           a[k] = aux[j++];
        else if (j > right)         a[k] = aux[i++];
        else if (aux[j] < aux[i]) { a[k] = aux[j++]; inversions += (mid - i + 1); }
        else                        a[k] = aux[i++];
    }
    return inversions;
}

long long get_number_of_inversions(vector<int> &a, vector<int> &aux, size_t left, size_t right) {
  long long inversions = 0;
  if (right <= left) return inversions;
  size_t mid = left + (right - left) / 2;
  inversions += get_number_of_inversions(a, aux, left, mid);
  inversions += get_number_of_inversions(a, aux, mid+1, right);
  inversions += krmerge(a, aux, left, mid, right);
  return inversions;
}

long long bruteCount(vector<int> &a) {
  long long inversions = 0;
  for (size_t i = 0; i < a.size(); ++i) {
      for (size_t j = i+1; j < a.size(); ++j) {
        if (a[j] < a[i]) inversions++;
      }
  }
  return inversions;
}

int main() {
  int n;
  std::ifstream myfile;
  myfile.open("randints.txt");
  //std::cin >> n;
  myfile >> n;
  vector<int> a(n);
  vector<int> a_copy(n);
  for (size_t i = 0; i < a.size(); i++) {
    //std::cin >> a[i];
    myfile >> a[i];
    a_copy[i] = a[i];
  }

  vector<int> aux(a.size());
  long long inversions = get_number_of_inversions(a, aux, 0, a.size()-1);
  std::cout << "# of inversions = " << inversions << '\n';

  long long brute_inversions = bruteCount(a_copy);
  std::cout << "# of inversions via brute force = " << brute_inversions << "\n";

  // print sorted array
  for (vector<int>::const_iterator iter = a.begin();
          iter != a.end(); ++iter) {
        std::cout << *iter << " ";
  }
  std::cout << "\n";
}
