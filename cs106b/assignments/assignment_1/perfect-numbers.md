# Perfect numbers
This assignment warmup focuses on giving you practice with C++ expressions, control structures, and functions, as well as testing and debugging your code.

As you work through the exercise, we pose thought questions (in the highlighted yellow boxes) for you to answer. The starter project includes the file **short_answer.txt** (located under "Other Files" in the Qt Project pane) where you will fill in your answers. When answering these questions, we are more interested in seeing your reasoning and thought process than we are the "correct" answer. In fact, some of the questions may not even have a "correct" answer!

## Perfect Numbers
The first part of this exercise will be an exploration of a certain class of numbers called perfect numbers. So before we get started on the coding, we have a little bit of math and a little bit of history to go over!

A perfect number is an integer that is equal to the sum of its proper divisors. A number's proper divisors are all positive numbers that evenly divide it, excluding itself. The first perfect number is 6 because its proper divisors are **1**, **2**, and **3**, and **1 + 2 + 3 = 6**. The next perfect number is **28**, which equals the sum of its proper divisors: **1 + 2 + 4 + 7 + 14**.

Perfect numbers are an interesting case study at the intersection of mathematics, number theory, and history. This class of numbers has intrigued mathematicians going back thousands of years and demonstrates human fascination with the abstract beauty of learning. If you are interested in learning more about perfect numbers, you can check out this [extensive history](https://mathshistory.st-andrews.ac.uk/HistTopics/Perfect_numbers/).

The following exercises will walk you through different algorithms for calculating these beloved numbers!

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
```cpp
/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
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

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}
```

## Observing runtime
The starter project contains the above C++ code already written for you. Your first task is run the given code and make some observations about how long the search takes to run. **Important note: If at any point the program takes more than 5 minutes to run to completion, you can just stop the program and report the runtime as "> 5 mins."**

Open the project in Qt Creator, find the file **main.cpp** file under "Sources and double-click to view its contents. Ignore the cryptic **if** statement at the beginning of the main function for now - what you should see is a single uncommented call to **findPerfects**, which is what will get executed when you run the main function. Build and run the program unchanged. Observe the output of the program.

```
Q1. How many numbers does the program search through? How many perfect numbers does it find? What are these perfect numbers?

A1: The program searches up to 40,000 numbers. It finds 4 pefect numbers. The perfect numbers founds are 6, 28, 496, and 8128.
```

Now, let's take a deeper dive into one of the core components of CS106B, which is analyzing the behavior of algorithms. What we would like to do is run the search several times with different search sizes (20000, 40000, 80000, etc.) and observe how long the program takes to run for each search size. While you could do this by manually editing the argument to the **findPerfects** call in **main.cpp** and re-running the program, repeating this process for many different sizes becomes tedious. It would be more convenient if we could run several time trials in sequence and get the timing results of all in one go. In order to do this, we'll have to take a brief detour to talk about the SimpleTest library.

## Using SimpleTest
In CS106B, you will use a unit-test framework called SimpleTest to test your code. **Stop here and read our [guide to testing](./testing_guide.md) to introduce yourself to using this framework. In particular, pay attention to the STUDENT_TEST, EXPECT, EXPECT_EQUAL, and TIME_OPERATION components**. SimpleTest is somewhat akin to the "doctest" features you may have used in Python for CS106A. If you're not familiar with doctests, don't sweat – the testing guide above has everything you need to know about how testing your code will work in CS106B.

It is mentioned in the testing guide but is worth repeating here: all tests that we have provided in the starter code are labeled using the **PROVIDED_TEST** identifier. When you add tests of your own, make sure to label them using the **STUDENT_TEST** identifier, so that your grader can easily identify which tests you've added.

## Running time trials
Open the **perfect.cpp** file and scroll to the bottom. Review the provided test cases, with a special focus on the first one, which makes several calls to **TIME_OPERATION**. This is the secret sauce that will allow us to accomplish our goal from earlier: timing the operation of **findPerfects** on different input sizes. Follow these steps to run the provided test cases:
* Edit the **main** function in **main.cpp** to change the argument passed to **runSimpleTests** from **NO_TESTS** to **SELECTED_TESTS**. For the rest of this exercise, you will not need to modify any of the code in **main.cpp**.
* Re-build and run the program. When prompted to "Enter your selection," type only the number 3 (this choices selects the tests for the **perfect.cpp** file) and hit enter to run the **perfect.cpp** tests. A SimpleTest popup window opens in addition to the console window. The results of the tests will appear in both. The given code should pass all the tests, so this demonstrates what a successful sweep through all the tests looks like.
* In particular, pay attention to the output of the first test, both in the graphical popup window and in the console window. You should see the output of multiple runs of the **findPerfects** function, as well as the amount of time each function call took.

```
Q2. Record the timing results for findPerfects into a table.

A2: 
Search Size: 20000  Runtime: 1.483 secs
Search Size: 40000  Runtime: 5.792 secs
Search Size: 80000  Runtime: 22.905 secs
Search Size: 160000 Runtime: 93.573 secs
Search Size: 320000 Runtime: > 5 mins.
Search Size: 640000 Runtime: > 5 mins.
```

[Graph](./time_graph.pdf)

* To do so, you will need to experiment with uncommenting out some of the lines in the provided test in **perfect.cpp**. Experiment with larger and larger search sizes until the total runtime exceeds 5 minutes. At that point, feel free to just skip any larger remaining sizes and indicate that the runtime was too long to measure.
Use the data to get a rough idea of the relationship between the argument search size and the amount of time required. It may help to [plot these values on a graph](https://www.desmos.com/calculator), if you have the capability to do so.

What you should notice among the time values in your table is that doubling the size of the search doesn't just cause the time required to also double; it goes up by a factor of 4. Rather than a linear relationship, we've got a quadratic relationship between the search size and the program execution time! Let's investigate why this might be.

