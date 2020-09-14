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

```cpp
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

## Observing runtime
The starter project contains the above C++ code already written for you. Your first task is going to be to run the code and make some observations about how long it takes the program to run. **Important note: If at any point your program takes more than 5 minutes to run to completion, you can just stop the program and report the runtime as "> 5 mins."**

To start, let's just get familiarized with what the output of running this code looks like. Open the project in Qt Creator and double-click on the main.cpp file. Ignore the cryptic if statement at the beginning of the main function for now - what you should see is a single uncommented call to findPerfects, which is what will get executed when you run the main function. Go ahead and build and run the program as given. Observe the output of the program.

`Q1: How many numbers does the program search through? How many perfect numbers does it find? What are these perfect numbers?`

Now, let's take a deeper dive into one of the core components of CS106B, which is analyzing the behavior of algorithms. What we would like to do is repeatedly run the search for perfect numbers many times with many different search sizes (40000, 80000, 160000, etc.) and observe how long the program takes to run for each search size. While we could do this by manually changing the argument to the **findPerfects** call in **main.cpp** and then re-running the whole program, you could imagine this getting very tedious. Instead, what we want is the ability to run many different time trials at once and get the timing results of all of them back at the same time. In order to do this, we'll have to take a brief detour to talk about the SimpleTest library.

## Using SimpleTest
In CS106B, you will use a unit-test framework called **SimpleTest** to test your code. **Stop here and read our [guide to testing](./testing_and_the_simpletest_framework.md) to introduce yourself to using this framework. In particular, pay attention to the `TIME_OPERATION`, `EXPECT`, `EXPECT_EQUAL`, and `STUDENT_TEST` components**. SimpleTest is somewhat akin to the "doctest" features you may have used in Python for CS106A. If you're not familiar with doctests, don't sweat – the testing guide above has everything you need to know about how testing your code will work in CS106B.

This is mentioned in the testing guide but is worth repeating here: all tests that we have provided in the starter code are labeled using the `PROVIDED_TEST` identifier. When you add tests of your own, make sure to label them using the `STUDENT_TEST` identifier, so that your grader can easily identify which tests you've addded.

## Running time trials
Now, open up the **perfect.cpp** file and scroll to the bottom. Review the existing test cases, with a special focus on the first one, which consists of a number of different calls to **TIME_OPERATION**. This is the secret sauce that will allow us to accomplish our goal from earlier: reproducible calls to the **findPerfects** function with a different count of numbers to search for each function call. Take the following steps to run the existing test cases to see **SimpleTest** in action.

Edit the main function in main.cpp by changing the argument passed to runSimpleTests from NO_TESTS to SELECTED_TESTS. For the rest of this exercise, you will not need to modify any of the code in main.cpp.
Re-build and run the program. When prompted to "Enter your selection," type only the number 3 and hit enter to run the perfect.cpp tests. Notice that a SimpleTest popup window opens in addition to the console window. The results of the tests will appear in both. The given code should pass all the tests, so this shows you what a successful sweep through all the tests looks like.
In particular, pay attention to the output of the first test, both in the graphical popup window and in the console window. You should see the output of multiple runs of the findPerfects function, as well as the amount of time each function call took.
Q2: Fill out the table of timing results in short_answer.txt. To do so, you will need to experiment with uncommenting out some of the lines in the provided test in perfect.cpp. Experiment with larger and larger search sizes until the total runtime exceeds 5 minutes. At that point, feel free to just skip any larger remaining sizes and indicate that the runtime was too long to measure.
Use the data to get a rough idea of the relationship between the argument search size and the amount of time required. It may help to plot these values on a graph, if you have the capability to do so.