#include <iostream>

int get_change(int n) {
  int coin_ctr = 0;
  while (n > 0) {
    if (n >= 10) {
      n-=10;
    } else if (n >= 5) {
      n-=5;
    } else {
      n-=1;
    }
    ++coin_ctr;
  }
  return coin_ctr;
}

int main() {
  int n;
  std::cin >> n;
  std::cout << get_change(n) << '\n';
}
