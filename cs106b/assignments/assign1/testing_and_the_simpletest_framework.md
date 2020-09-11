# Testing and the SimpleTest framework
## Why testing?
Anybody that writes code for some purpose (whether as a researcher, a software engineer, or in any other profession) will get to the point where others are relying on their code. Bugs in software can be dangerous or even deadly. Additionally, users do not enjoy using software that is buggy and crashes and fixing bugs once the software is in production is very costly. Most importantly, **good engineers take pride in building things that work well and are robust**.

The key to writing working software is developing good tests. In this course we follow an approach called test-driven development. As you write code, you will also write companion tests. These tests are used to verify that the code you just finished writing works as intended.

This strategy is sometimes called "test-as-you-go". You work in small steps, being sure to test thoroughly, and only move on after you having confirmed the correctness and fixed all issues. The beauty of this approach is that each step is relatively straightforward and easy to debug. Imagine the opposite approach: you write hundreds of lines of code, the code does not work, and now you need to figure out which one of those hundreds of lines of code isn't working as expected! That is the sort of frustration that we want to help you all avoid as you continue to develop your skills as programmers.

## SimpleTest
For CS106B, we provide a unit-test framework called **SimpleTest** that you will use to test your code. This framework was pioneered by our ace colleague Keith Schwarz. **SimpleTest** provides a simple, clean approach to writing and running test cases.

Here is an example of how you might see the **SimpleTest** framework used in the starter code of an assignment.

```c++
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

PROVIDED_TEST("Demonstrate different SimpleTest use case") {
    EXPECT_EQUAL(reversed("but"), "tub");
    EXPECT_EQUAL(reversed("stanford"), "drofnats");
}
```

When we provide tests for you in the starter code, each test case is wrapped in the special macro **PROVIDED_TEST**. The string argument in parentheses describes the purpose of the test and the code block that follows (enclosed in curly braces) defines the actual test behavior.

When you add your own test cases, you will wrap your test code blocks in the **STUDENT_TEST** macro instead. The **STUDENT_TEST** functionality and structure is exactly the same as **PROVIDED_TEST**, it simply distinguishes the tests you've written yourself from those we provide for the benefit of your grader. You will see many examples of this in the following sections.

