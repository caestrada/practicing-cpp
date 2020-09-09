#include <iostream>

/* This function takes in a number n anc calculates the sum
 * of all proper divisors of n, excluding itself.
 * 
 * Note: `long` is a C++ type that allows for a larger range of values than the
 * `int` type. It is a variant of the int type, and for all intents and purposes,
 * you can treat it like you would an int.
 */
long divisorSum(long n) {
  long total = 0;
  for (long divisor = 1; divisor < n; divisor++) {
    if (n % divisor == 0) {
      total += divisor;
    }
  }
  return total;
}

/* This function is provided a number n and returns a boolean
 * (true/false) value representing whether or not the number is
 * perfect. A perfect number is a non-zero positive number whose
 * Sum of its proper divisors is equal itself.
 */
bool isPerfect (long n) {
  return (n != 0) && (n == divisorSum(n));
}

/* This function performs an exhaustive search for perfect numbers.
 * It takes as input a number called `stop` and searches for perfect
 * numbers between 1 and `stop`. Any perfect numbers that are found will
 * be printed out to the console.
 */
void findPerfects(long stop) {
  for (long num = 1; num < stop; num++) {
    if (isPerfect(num)) {
      std::cout << "Found perfect number: " << num << std::endl;
    }
    if (num % 10000 == 0) std::cout << "." << std::flush;
  }
  std::cout << "Done searching up to " << stop << std::endl;
}

int main() {
  findPerfects(100000);

  return 0;
}
