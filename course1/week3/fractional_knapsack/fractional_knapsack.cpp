#include <iostream>
#include <vector>
#include <algorithm>   // to get declaration for sort, min

using std::vector;    using std::min;

struct item {
  int weight;
  int value;
  double unit_value;
};

// comparator for item structure sort - uses ">" to cause reverse sort
bool compare(const item& x, const item& y) {
  return x.unit_value > y.unit_value;
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {

  // create a vector of items including unit_value so that we can sort items
  // by their unit_values - get_optimal value becomes O(nlogn)
  vector<int>::size_type n = weights.size();
  vector<item> items(n);
  for (vector<int>::size_type i=0; i<n; ++i) {
    item temp;
    temp.weight = weights[i];
    temp.value = values[i];
    temp.unit_value = (double)values[i] / weights[i];
    items[i] = temp;
  }
  // sort items by descending unit_value
  sort(items.begin(), items.end(), compare);

  // fill knapsack
  double total_value = 0.0;
  vector<int>::size_type item_ptr = 0;
  while (capacity > 0) {
    int amount = min(items[item_ptr].weight , capacity);
    total_value += amount * items[item_ptr].unit_value;
    capacity -= amount;
    ++item_ptr;
  }

  return total_value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
