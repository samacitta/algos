#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::vector;

struct Item {
  int coord;
  char desc;
  int ref_ndx;
};

// comparator for Item structure sort - uses ">" to cause reverse sort
bool compare(const Item& x, const Item& y) {
    if (x.coord == y.coord)
        return x.desc < y.desc;
    else
        return x.coord < y.coord;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {

  // create a vector of items
  size_t itemCount = starts.size() +ends.size() + points.size();
  vector<Item> items(itemCount);
  //std::cout << "items size = " << items.size() << "\n";

  // create items corresponding to points
  for (size_t i = 0; i < points.size(); ++i) {
    Item point;
    point.coord = points[i];
    point.desc = 'p';
    point.ref_ndx = i;
    items[i] = point;
    //std::cout << "items[i] = " << items[i].coord << " " << items[i].desc
    //          << " " << items[i].ref_ndx << "\n";

  }

  // create items corresponding to segments - 2 each
  size_t items_ndx = points.size();
  for (size_t i = 0; i < starts.size(); ++i) {
    Item segStart, segEnd;
    segStart.coord = starts[i];
    segStart.desc = 'l';
    segStart.ref_ndx = i;
    items[items_ndx++] = segStart;
    segEnd.coord = ends[i];
    segEnd.desc = 'r';
    segEnd.ref_ndx = i;
    items[items_ndx++] = segEnd;
  }

  // sort items vector
  sort(items.begin(), items.end(), compare);

  // determine how many segments contain each point
  vector<int> counts(points.size());
  int numOpenSegs = 0;
  for (size_t i = 0; i < items.size(); ++i) {
    if (items[i].desc == 'l')
        numOpenSegs++;
    else if (items[i].desc == 'r')
        numOpenSegs--;
    else {      // items[i].desc == 'p'
        // write count for a given point to the index location in cnt vector
        // which matches the point's location in the original points vector -
        // doing it this way to meet assignment output format requirements
        counts[items[i].ref_ndx] = numOpenSegs;
    }
  }

  return counts;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  std::ifstream myfile;
  myfile.open("small_test3.txt");

  // n = # of segments, m = # of points
  int n, m;
  myfile >> n >> m;

  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    myfile >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    myfile >> points[i];
  }
  //use fast_count_segments
  //vector<int> cnt = naive_count_segments(starts, ends, points);
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
