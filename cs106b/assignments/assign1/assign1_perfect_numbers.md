# Assign1: Perfect numbers

This part of the assignment focuses on giving you practice with C++ expressions, control structures, and functions, as well as testing and debugging your code.

In addition, to writing code and tests in the **perfect.cpp** file, you will also be filling in answers to short answer questions in short_answer.txt (located under the "Other Files -> src" in the Qt Project View) as you work through this exercise. Make sure to answer all the questions (each one is `highlighted`, and labeled Q1, Q2, etc.). When filling out the short answer questions, we are more interested in seeing your reasoning and thought process than we are the "correct" answer. In fact, some of the questions may not even have a "correct" answer!

## Perfect Numbers

The first part of this exercise will be an exploration of a certain class of numbers called `perfect numbers`. So before we get started on the coding, we have a little bit of math and a little bit of history to go over!

A `perfect number` is an integer that is equal to the sum of its proper divisors. A number's proper divisors are all positive numbers that evenly divide it, excluding itself. The first perfect number is 6 because its proper divisors are **1**, **2**, and **3**, and **1 + 2 + 3 = 6**. The next perfect number is **28**, which equals the sum of its proper divisors: **1 + 2 + 4 + 7 + 14**.

Perfect numbers are a very interesting case study at the intersection of mathematics, number theory, history, and human fascination. While the exact origin of their study cannot be pinpointed, this class of numbers has fascinated mathematicians going back thousands of years and is perhaps one of the original examples of ongoing human fascination with the beauty of learning. The quote below shows just a taste of some of the philosophical reverence that has been afforded to perfect numbers throughout history. If you are interested in learning more about perfect numbers, you can check out this [extensive history](https://mathshistory.st-andrews.ac.uk/HistTopics/Perfect_numbers/).

## An Exhaustive Algorithm

One way to find perfect numbers is by using an "exhaustive" algorithm. In this general class of algorithms, you try all possible options ("exhausting" all options) in order to find the desired solution or information that you're looking for. For the specific task of finding perfect numbers, this means checking every integer starting from 1 and counting upwards and checking to see if each one along the way is a perfect number. Testing to see whether or not a number is perfect involves looping over all possible divisors that the number might have, verifying when you've found a divisor, and keeping track of the sum of these valid divisors. If, at the end of the process, the sum and the original number are equal, then you've found a perfect number! These two components combined together define the exhaustive algorithm for finding perfect numbers.

Here is some Python code that performs an exhaustive search for perfect numbers:
```python
def divisor_sum(n):
    total = 0
    for divisor in range(1, n):
        if n % divisor == 0:
            total += divisor
    return total

def is_perfect(n):
    return n != 0 and n == divisor_sum(n)

def find_perfects(stop):
    for num in range(1, stop):
        if is_perfect(num):
            print("Found perfect number: ", num)
        if num % 10000 == 0: print('.', end='',flush=True) # progress bar
    print("Done searching up to ", stop)

```

The same code is now expressed below in C++. If your CS106A was taught in Python, comparing and contrasting these two may be a helpful way to start adapting to the language differences. If instead your prior course/experience was with Java/Javascript, just sit back and enjoy how C++ already seems familiar to what you know!
``cpp
/* This function takes in a number n and calculates the sum
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
 * sum of its proper divisors is equal to itself.
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
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush;
    }
    cout << "Done searching up to " << stop << endl;
}
```