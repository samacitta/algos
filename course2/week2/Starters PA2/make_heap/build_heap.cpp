#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>        // for ceil

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  // compute index of parent of item w/ index i
  int parent(const int i) {
    return std::ceil(i/2.0) - 1;
  }

  // return index of left child node
  int leftChild(int i) {
      return 2*i + 1;
  }

  // return index of right child node
  int rightChild(int i) {
      return 2*i + 2;
  }

  // move element at index i up to its proper place in the heap
  void siftUp(int i) {
      while (i > 0 && data_[parent(i)] > data_[i]) {
          swap(data_[parent(i)], data_[i]);
          swaps_.push_back(make_pair(parent(i), i));
          i = parent(i);
      }
  }

  // move element at index i down to its proper place in the heap
  void siftDown(int i) {
      int minIndex = i;
      int left = leftChild(i);
      if (left < data_.size() && data_[left] < data_[minIndex])
          minIndex = left;
      int right = rightChild(i);
      if (right < data_.size() && data_[right] < data_[minIndex])
          minIndex = right;
      if (i != minIndex) {
          swap(data_[i], data_[minIndex]);
          swaps_.push_back(make_pair(i, minIndex));
          siftDown(minIndex);
      }
  }

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void naiveGenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }

  // construct the heap using O(n*log n) # of swaps
  void efficientGenerateSwaps() {
    swaps_.clear();

    for (int i = std::floor(data_.size()/2.0)-1; i >= 0; --i) {
        siftDown(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    //naiveGenerateSwaps();
    efficientGenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
