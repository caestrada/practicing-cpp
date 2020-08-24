#include <iostream>

void basicRecursion(int max, int current) {
  // Base Case
  if (current > max) return;

  std::cout << current << std::endl;

  // Recursive Case
  basicRecursion(max, current+1);
}

int main() {
  basicRecursion(5, 1);
  return 0;
}
