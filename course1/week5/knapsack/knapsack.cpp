#include <iostream>
#include <vector>

using std::vector;

int** malloc2d(int r, int c);

int** optimal_weight(int W, const vector<int> &items) {
  //write your code here
  size_t N = items.size();
  int** A = malloc2d(N+1, W+1);     // declare dp value array

  // init first row and first column of A to 0's
  for (int i = 0; i < N+1; i++) {
      A[i][0] = 0;
  }
  for (int j = 0; j < W+1; j++) {
      A[0][j] = 0;
  }

  // build dp array
  for (int i = 1; i < N+1; i++) {
      int v = items[i-1], w = items[i-1];
      for (int j = 0; j < W+1; j++) {
          if (j-w < 0)
              A[i][j] = A[i-1][j];
          else
              A[i][j] = std::max(A[i-1][j], A[i-1][j-w] + v);
      }
  }

  /*
  int current_weight = 0;
  for (size_t i = 0; i < w.size(); ++i) {
    if (current_weight + w[i] <= W) {
      current_weight += w[i];
    }
  }
  */
  return A;
}

/*  Dynamically allocate the memory for a 2-dimensional array as an
    array of arrays
*/
int** malloc2d(int r, int c) {
    int **t = new int*[r];
    for (int i = 0; i < r; i++)
        t[i] = new int[c];
    return t;
}

void krtest() {
    int** arr = malloc2d(5, 5);
    arr[1][2] = 10;
    arr[0][4] = 20;
}

int main() {

  //krtest();

  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }

  // get DP result matrix
  int** resultMatrix = optimal_weight(W, w);
  std::cout << "optimal weight = " << resultMatrix[n][W] << '\n';

  // reconstruct list of selected items
  vector<int> selected_items;
  int j = W;
  for (int i = n; i > 0; i--) {
    int temp = w[i-1];
    if ((j-temp >= 0) && resultMatrix[i-1][j-temp]+temp >= resultMatrix[i-1][j]) {
        selected_items.push_back(i-1);
        j -= temp;
    }
  }
  // print list of selected items
  for (int item : selected_items) {
      std::cout << item << " ";
  }
  std::cout << '\n';
}
