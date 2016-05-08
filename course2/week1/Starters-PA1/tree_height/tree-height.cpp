#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class TreeHeight {
  int n;
  int root;
  vector<int> parent;
  vector<vector<int> > children;

public:
  void read() {
    std::cin >> n;
    parent.resize(n);
    for (int i = 0; i < n; i++)
      std::cin >> parent[i];
    children.resize(n, vector<int>(0));    //init vector of vectors
    root = -1;     // indicates root not detected
    // populate adjacency lists
    for (int i = 0; i < n; ++i) {
        if (parent[i] == -1) {
            root = i;
        } else {
            children[parent[i]].push_back(i);
        }
    }
    std::cout << "children.size() = " << children.size() << std::endl;
 }

  int compute_height() {
    // Replace this code with a faster implementation
    int maxHeight = 0;
    for (int vertex = 0; vertex < n; vertex++) {
      int height = 0;
      for (int i = vertex; i != -1; i = parent[i])
        height++;
      maxHeight = std::max(maxHeight, height);
    }
    return maxHeight;
  }

  // compute height recursively depth-first from top of tree
  int compute_height_recursive() {
      //std::cout << "test line 1" << std::endl;
      int maxHeight = compute_height_recursive(root);
      return maxHeight;
  }

  int compute_height_recursive(int node) {
      //std::cout << "test line 2" << std::endl;
      //std::cout << "children.size() = " << children.size() << std::endl;
      std::cout << "children[node].size() = " << children[node].size() << std::endl;
      int maxHeight = 1;
      //std::cout << "maxHeight = " << maxHeight << std::endl;
      for (int i = 0; i < children[node].size(); ++i) {
          //std::cout << "test line 3" << std::endl;
          int h = 1 + compute_height_recursive(children[node][i]);
          if (h > maxHeight)
              maxHeight = h;
      }

      return maxHeight;
  }

};

int main() {
  std::ios_base::sync_with_stdio(0);
  TreeHeight tree;
  tree.read();
  std::cout << "naive height =\t" << tree.compute_height() << std::endl;
  std::cout << "recursive height =\t" << tree.compute_height_recursive() << std::endl;
}
