# Testing and the SimpleTest framework
## Why testing?
Anybody that writes code for some purpose (whether as a researcher, a software engineer, or in any other profession) will get to the point where others are relying on their code. Bugs in software can be [dangerous or even deadly](https://www.pingdom.com/blog/10-historical-software-bugs-with-extreme-consequences/). Additionally, users do not enjoy using software that is buggy and crashes and fixing bugs once the software is in production is very costly. Most importantly, **good engineers take pride in building things that work well and are robust**.

The key to writing working software is developing good tests. In this course we follow an approach called test-driven development. As you write code, you will also write companion tests. These tests are used to verify that the code you just finished writing works as intended.

This strategy is sometimes called "test-as-you-go". You work in small steps, being sure to test thoroughly, and only move on after you having confirmed the correctness and fixed all issues. The beauty of this approach is that each step is relatively straightforward and easy to debug. Imagine the opposite approach: you write hundreds of lines of code, the code does not work, and now you need to figure out which one of those hundreds of lines of code isn't working as expected! That is the sort of frustration that we want to help you all avoid as you continue to develop your skills as programmers.

## SimpleTest
For CS106B, we provide a unit-test framework called **SimpleTest** that you will use to test your code. This framework was pioneered by our ace colleague Keith Schwarz. **SimpleTest** provides a simple, clean approach to writing and running test cases.

Here is an example of how you might see the **SimpleTest** framework used in the starter code of an assignment.
```cpp
// reversed(str) returns copy of str with characters in reverse order.
string reversed(string s)
{
    string result;
    for (int i = s.length() - 1; i >= 0; i--) {
        result += s[i];
    }
    return result;
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Demonstrate different SimpleTest use cases") {
    EXPECT_EQUAL(reversed("but"), "tub");
    EXPECT_EQUAL(reversed("stanford"), "drofnats");
}
```
When we provide tests for you in the starter code, each test case is wrapped in the special macro **PROVIDED_TEST**. The string argument in parentheses describes the purpose of the test and the code block that follows (enclosed in curly braces) defines the actual test behavior.

When you add your own test cases, you will wrap your test code blocks in the **STUDENT_TEST** macro instead. The **STUDENT_TEST** functionality and structure is exactly the same as **PROVIDED_TEST**, it simply distinguishes the tests you've written yourself from those we provide for the benefit of your grader. You will see many examples of this in the following sections.

### EXPECT_EQUAL
Within the code block, the test macro most commonly used is **EXPECT_EQUAL** which confirms the two arguments are equal. A typical use case for **EXPECT_EQUAL** is to take a value produced by your code, e.g. the return value from a call to one of your functions, and confirm that value matches to the expected outcome. For example, in the above code, **EXPECT_EQUAL** is used to compare the result of the call **reversed("but")** to the string **"tub"**. If the two are indeed equal, the test passes. If they do not match, the test is reported as a failure.

For example, after adding your own tests (using the **STUDENT_TEST** identifier as previously mentioned) to the above file, it could look something like this:
```cpp
// reversed(str) returns copy of str with characters in reverse order.
string reversed(string s)
{
    string result;
    for (int i = s.length() - 1; i >= 0; i--) {
        result += s[i];
    }
    return result;
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Demonstrate different SimpleTest use cases") {
    EXPECT_EQUAL(reversed("but"), "tub");
    EXPECT_EQUAL(reversed("stanford"), "drofnats");
}

STUDENT_TEST("my added cases not covered by the provided tests") {
    EXPECT_EQUAL(reversed("racecar"), "racecar");
    EXPECT_EQUAL(reversed(""), "");
    EXPECT_EQUAL(reversed("123456789"), "987654321");
}
```
`
Important note: You should never modify the provided tests – these are the same tests that will be used for grading, so it is not in your best interest to modify them. If you want to test different scenarios, always add new tests using the STUDENT_TEST macro.
`
### EXPECT
Another test macro that is regularly used is the **EXPECT** which confirms the truth of a single expression. If the expression evaluates to true, the test passes. If false, it reports a test failure. For example, if you added the **isPalindrome** function to the above program, you could add a test case that uses **EXPECT** to confirm the correct result from **isPalindrome**, as shown below.
```cpp
// reversed(str) returns copy of str with characters in reverse order.
string reversed(string s) {
    string result;
    for (int i = s.length() - 1; i >= 0; i--) {
        result += s[i];
    }
    return result;
}

bool isPalindrome(string s) {
    return s == reversed(s);
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Demonstrate different SimpleTest use case") {
    EXPECT_EQUAL(reversed("but"), "tub");
    EXPECT_EQUAL(reversed("stanford"), "drofnats");
}

STUDENT_TEST("test additional cases not covered by the provided tests") {
    EXPECT_EQUAL(reversed("racecar"), "racecar");
    EXPECT_EQUAL(reversed(""), "");
    EXPECT_EQUAL(reversed("123456789"), "987654321");
}

STUDENT_TEST("test my isPalindrome function") {
    EXPECT(isPalindrome("racecar"));
    EXPECT(!isPalindrome("stanford"));
}
```
When would you use **EXPECT** instead of **EXPECT_EQUAL**? **EXPECT_EQUAL** which is appropriate for any situation in which you have two values that can be compared for equality (two numbers, two strings, two Vectors, etc.). **EXPECT** allows you to express a wider variety of conditions beyond simple equality. For example, you could confirm the truth of a complex set of conditions by passing a compound expression such as **EXPECT(x > y && y != z || y == 0);**

### EXPECT_ERROR
You pass an expression to **EXPECT_ERROR** and it evaluates the expression and observes whether it calls the **error()** function to report an error. If an error is raised, this causes the test to pass. If not, it causes the test to fail and reports that the expression failed to trigger an error. **EXPECT_ERROR** is used in the specific situation of confirming expected handling of errors within your code.

### EXPECT_NO_ERROR
This macro is exactly the opposite of **EXPECT_ERROR**. With this macro, you pass it an expression, and if the expression successfully runs to completion without running an error, then the test passes. However, if evaluating the expression calls the error() function somewhere along the way, the error causes the test case to report failure. **EXPECT_NO_ERROR** is used in specific situations where you want to confirm that functions behave properly on correct input.

### TIME_OPERATION
**SimpleTest** also has support for simple execution timing.

To time an operation, evaluate the expression within the macro **TIME_OPERATION(size, expression)**, as shown below:
```cpp
STUDENT_TEST("Time operation vector sort on tiny input")
{
    Vector<int> v = {3, 7, 2, 45, 2, 6, 3, 56, 12};
    TIME_OPERATION(v.size(), v.sort());
}
```
The first argument to **TIME_OPERATION** is the input size; this is used to label this timing result to distinguish from other results. The second argument is the expression to evaluate. **TIME_OPERATION** will start a new timer, evaluate the expression, stop the timer, and report the elapsed time.

You can have more than one use of **TIME_OPERATION** within a test case. Each operation is individually evaluated and timed. Below demonstrates use of **TIME_OPERATION** in a loop to time sorting successively larger vectors.
```cpp
STUDENT_TEST("Time operation vector sort over a range of input sizes")
{
    for (int size = 50000; size < 1000000; size *= 2) {
        Vector<int> v;
        for (int i = 0; i < size; i++) {
            v.add(randomInteger(1, 1000)); // fill vector with random values
        }
        TIME_OPERATION(v.size(), v.sort());
    }
}
```
Here are the test results for running the test cases above:
![testing_guide](./testing_guide.md)



