#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

// comparator for segment structure sort - sort by the 'end' point of each interval
bool compare(const Segment& x, const Segment& y) {
  return x.end < y.end;
}

vector<int> optimal_points(vector<Segment> &segments) {
  // sort segments by the 'end' variable
  sort(segments.begin(), segments.end(), compare);


  vector<int> points;
  int maxval = std::numeric_limits<int>::min();
  for (auto &seg : segments) {
     if (seg.start > maxval) {
       maxval = seg.end;
       points.push_back(seg.end);
     }
  }

  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << "optimal # of points: " << points.size() << "\n" << "points: ";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
