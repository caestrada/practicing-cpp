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
```
Q3. Does it take the same amount of effort to compute isPerfect on the number 10 as it does on the number 1000? Why or why not? Does it take the same amount of work for findPerfects to search the range of numbers from 1-1000 as it does to search the numbers from 1000-2000? Why or why not?
```

One of the downsides of the exhaustive algorithm as written is that its performance starts to get really bad, really quickly! In particular, the first four perfect numbers are found pretty quickly (**6, 28, 496, 8128**), but that fifth one is quite a ways off – in the neighborhood of 33 million. Working up to that number by exhaustive search is going to take l-o-o-ng time.

```
Q4. Extrapolate from the data you gathered and make a prediction: how long will it take findPerfects to reach the fifth perfect number?
```
This is your first exposure to algorithmic analysis, a topic we will explore in much greater detail throughout the course, starting next week!

As a fun aside, if you have access to a Python environment, you can attempt similarly-sized searches using the Python version of the program to see just how much slower an interpreted language (Python) is compared to a compiled language (C++). Check out the Python vs C++ Showdown we've posted to the Ed discussion forum.

## Digging deeper into testing
Having completed these observations about performance, we move on to testing the code, which is one of the most important skills that we hope you will come out of this class with. Designing good tests and writing solid, well-tested code are skills that will serve you well for the rest of your computer science journey!

Complete the following exercises, which will help you start to develop your testing chops by exploring and writing tests on some of the functions that we've provided for you:

* Since all perfect numbers must be positive, there should be no such thing as a negative perfect number; thus isPerfect should return false for any negative numbers. Will you need to make a special case for this or does the code already handle it? Let's investigate…
    * Look at the code and make a prediction about what happens is isPerfect is given a negative input.
    * Add a new STUDENT_TEST case that calls isPerfect on a few different negative inputs. The expected result of isPerfect for such inputs should be false.
    * Run these test cases to confirm that the code behaves as expected. Now that you have added your own tests, selecting the perfect.cpp tests from the main menu is now numbered choice 4.
* Introduce a bug into divisorSum (e.g. erroneously initialize total to 1 instead of 0). Rebuild and run the tests again. This should let you see how test failures are reported.
```
Q5. Do any of the tests still pass even with this broken function? Why or why not?

```
* Be sure to undo the bug and restore divisorSum to a correct state.
* Add another STUDENT_TEST of your own but deliberately make the test case expect something erroneous (e.g. isPerfect(5) returns true). Run this test case. What happens?
```
Q6. Can the test framework detect that the test case is "bogus", in the sense that the premise of the test case itself is off-base?
```
* (Refer to our testing guide for a longer explanation of bogus tests) This example serves as a reminder to take care in constructing your test cases! The pass/fail result of a bogus test an be misleading or inverted. Be sure to remove that bogus test so it won't further confuse you. On this assignment, and all future ones, your goal is a clean green record for all tests.

## Streamlining and more testing
As you observed earlier, it is chore for an exhaustive search to reach the fifth perfect number. However, there is a neat little optimization you can apply that can significantly streamline the job. The function divisorSum runs a loop from 1 to N to find divisors, but in fact, this is quite wasteful. We truly only need to examine divisors up to the square root of N. Along the way, we can work out what the corresponding pairwise factor for a given divisor is without having to explicitly loop all the way up to the other factor. In other words, we can take advantage of the fact that each divisor that is less than the square root is paired up with a divisor that is greater than the square root. Take a moment to carefully think about why this is true and how you would rearrange the code to capitalize on this observation.

Now, implement the following function prototype that has been provided in the starter code.

long smarterSum(long n)

You may find it helpful to use the provided divisorSum implementation as a starting point (that is, you may choose to copy-paste the existing code and make tweaks to it). Be careful: there are some subtle edge cases that you may have to handle in the adapted version that were not an issue in the original.

The C++ library function sqrt can be used to compute a square root.

After adding new code to your program, your next step is to thoroughly test that code and confirm it is bug-free. Only then should you move on to the next task. Let's write some tests for the smarterSum function.

Because you already have the vetted function divisorSum at your disposal, a neat testing strategy here is to use EXPECT_EQUAL to confirm that the result from divisorSum(n) is equal to the result from smarterSum(n). Rather than pick a random value for n, brainstorm about why certain values might be good candidates. As an example, try picking a number like n=25 (which has an square root that is an integer value) to ensure there is no off-by-one issue on the stopping condition of your new loop. You must add at least 3 new student tests of your own (again, remember to label them as STUDENT_TEST) for smarterSum.

```
Q7. Describe the testing strategy your used for your test cases to confirm smarterSum is working correctly.
```
Once you have confirmed that smarterSum operates equivalently to divisorSum, implement the following two functions, which should take advantage of your new smarterSum function:

bool isPerfectSmarter(long n)

void findPerfectsSmarter(long stop)

The code for these two functions is very similar to the provided isPerfect and findPerfects functions, just using your new, streamlined divisor summation algorithm. Again, you may copy-paste the existing implementations, and make small tweaks as necessary.

Now let's run time trials to see just how much better our new algorithm is!

Important note: As before, if at any point your program takes more than 5 minutes to run to completion, you can just stop the program and report the runtime as "> 5 mins."

* Add a STUDENT_TEST that uses TIME_OPERATION to measure findPerfectsSmarter on a sequence of increasing sizes.
```
Q8. Record your timing results for findPerfectsSmarter into a table.
```
(You may have to use larger sizes than before to get results that are measurable, because this version is so much faster.)

```
Q9. Make a prediction: how long will findPerfectsSmarter take to reach the fifth perfect number?
```
Our previous algorithm grew at the rate N^2, while this new version is N√N, since we only have to inspect √N divisors for every number along the way. If you plot runtimes on the same graph as before, you will see that they grow much less steeply than the runtimes from our previous experiment.

## Mersenne Primes and Euclid
Back to story time for a little bit: last year, there was a rare finding of a new Mersenne prime. A prime number is one whose only divisors are 1 and the number itself. A Mersenne prime is a prime number that is one less than a power of two. In other words, it takes the form 2^n - 1 for some integer n. For example, the prime number 31 can be expressed as 2^5 - 1, and thus is a Mersenne prime.

Mersenne primes are quite elusive, the one just found is only the 51st known and has almost 25 million digits! Verifying that the found number was indeed prime required almost two weeks of non-stop computing. The quest to find further Mersenne primes is driven by the Great Internet Mersenne Prime Search (GIMPS), a cooperative, distributed effort that taps into the spare cycles of a vast community of volunteer machines. Besides being hard to find, Mersenne primes are of great interest because they are some of the largest known prime numbers and because they show up in interesting ways in games like the Tower of Hanoi and the wheat and chessboard problem.

Back in 400 BCE, Euclid discovered an intriguing relationship between perfect numbers and the Mersenne primes. Specifically, if 2^k - 1 is prime, then 2^(k-1)*(2^k - 1) is a perfect number. Those of you enrolled in CS103 will appreciate this lovely proof of the Euclid-Euler theorem. This relationship will allow us to calculate perfect numbers using a much more efficient approach. The final task of the warmup is to implement this blazingly-fast algorithm and bask in the glory of having beaten the pants off exhaustive search.

## Turbo-charging with Euclid
Now that your computer is good and tired, it's time to take a more elegant approach to this problem. Over two thousand years ago, that clever guy Euclid discovered an intriguing pattern in the perfect numbers and was able to prove that if 2^k - 1 is prime then 2^(k-1) multiplied by (2^k - 1) is a perfect number.

Implement the function prototype:

long findNthPerfectEuclid(long n)

This function uses Euclid's method (described below) to find the nth perfect number:

Start by setting k = 1.
Calculate m = 2^k - 1 (use the C++ library function pow to compute exponential)
Determine whether m is prime or composite. (a simple isPrime helper that uses an exhaustive loop is just fine)
If m is prime, then calculate 2^(k-1) * (2^k - 1). This is the associated perfect number.
Increment k and repeat until you have found the nth perfect number.
The call findNthPerfectEuclid(n) should return the nth perfect number. What will be your testing strategy to verify that this function returns the correct result? You may find this table of perfect numbers to be helpful. One possibility is a test case that confirms each number is perfect according to your earlier function, e.g. EXPECT(isPerfect(findNthPerfectEuclid(n))).

Note: Your function can assume that all inputs (values of n) will be positive (that is, greater than 0). In particular, this means that you don't have to worry about negative values of n or the case where n is zero.

Add at least 4 new student test cases of your own to verify that your findNthPerfectEuclid is correct.

```
Q10. Explain how you chose your specific test cases and why they lead you to be confident findNthPerfectEuclid is working correctly.
```
A call to findNthPerfectEuclid(5) will near instantaneously find the fifth perfect number. Woah! Quite an improvement over the exhaustive algorithm, eh? This version is so lightning fast that it will quickly reach values that are too large to fit in a long. How many perfect numbers can you find before you overflow (an overflow is characterized by the large number you're incrementing suddenly becoming unexpectedly negative…)? This value may vary from system to system, so just keep an eye out for when things start to go south. As a point of comparison, back in 400 BC, Euler worked out the first eight perfect numbers himself — not too shabby for a guy with no electronics!

Concluding Thoughts
Hooray for algorithms! One of the themes for CS106B is to explore the tradeoffs between algorithm choices, especially as it relates to program efficiency. The differences between the exhaustive search and Euclid's approach is striking. Although there are tweaks (such as the square root trick) that will improve each algorithm relative to itself, the biggest bang for the buck comes from starting with a better overall approach. This result foreshadows many of the interesting things to come this quarter.

As a finishing touch on this portion of the assignment, add to the comments in perfect.cpp to share with your section leader a little something about yourself and to offer an interesting tidbit you learned in doing this exercise (be it something about C++, algorithms, number theory, how spunky your computer is, or something else exciting!).

Before moving on to the second part of the assignment, confirm that you have completed all tasks from the warmup. You should have answers to questions 1 to 10 in short_answer.txt. You should have implemented the following functions in perfect.cpp

* smarterSum
* isPerfectSmarter
* findPerfectsSmarter
* findNthPerfectEuclid

as well as added the requisite number of tests for each of these functions.

