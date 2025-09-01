# 🟢 C++ Control Flow

## 📚 Overview
Control flow statements determine the order in which program statements are executed. They allow you to make decisions, repeat code, and control program execution flow.

---

## 🔀 Decision Making

### If Statement
The most basic decision-making structure.

```cpp
if (condition) {
    // Code to execute if condition is true
}
```

**Example:**
```cpp
int age = 18;
if (age >= 18) {
    cout << "You are an adult." << endl;
}
```

### If-Else Statement
Execute different code based on a condition.

```cpp
if (condition) {
    // Code if condition is true
} else {
    // Code if condition is false
}
```

**Example:**
```cpp
int score = 85;
if (score >= 90) {
    cout << "Grade: A" << endl;
} else {
    cout << "Grade: B or lower" << endl;
}
```

### If-Else If-Else Chain
Handle multiple conditions in sequence.

```cpp
if (condition1) {
    // Code if condition1 is true
} else if (condition2) {
    // Code if condition2 is true
} else if (condition3) {
    // Code if condition3 is true
} else {
    // Code if all conditions are false
}
```

**Example:**
```cpp
int score = 85;
if (score >= 90) {
    cout << "Grade: A" << endl;
} else if (score >= 80) {
    cout << "Grade: B" << endl;
} else if (score >= 70) {
    cout << "Grade: C" << endl;
} else if (score >= 60) {
    cout << "Grade: D" << endl;
} else {
    cout << "Grade: F" << endl;
}
```

### Nested If Statements
If statements inside other if statements.

```cpp
int age = 25;
bool hasLicense = true;

if (age >= 18) {
    if (hasLicense) {
        cout << "You can drive." << endl;
    } else {
        cout << "You need a license to drive." << endl;
    }
} else {
    cout << "You are too young to drive." << endl;
}
```

---

## 🔄 Loops

### While Loop
Execute code while a condition is true.

```cpp
while (condition) {
    // Code to repeat
    // Update condition to avoid infinite loop
}
```

**Example:**
```cpp
int count = 1;
while (count <= 5) {
    cout << "Count: " << count << endl;
    count++;  // Important: update the condition
}
```

**Output:**
```
Count: 1
Count: 2
Count: 3
Count: 4
Count: 5
```

### Do-While Loop
Execute code at least once, then check condition.

```cpp
do {
    // Code to repeat
    // Update condition
} while (condition);
```

**Example:**
```cpp
int number;
do {
    cout << "Enter a positive number: ";
    cin >> number;
} while (number <= 0);

cout << "You entered: " << number << endl;
```

### For Loop
Most common loop with initialization, condition, and update.

```cpp
for (initialization; condition; update) {
    // Code to repeat
}
```

**Example:**
```cpp
for (int i = 0; i < 5; i++) {
    cout << "Iteration " << i << endl;
}
```

**Output:**
```
Iteration 0
Iteration 1
Iteration 2
Iteration 3
Iteration 4
```

### Range-Based For Loop (C++11)
Iterate over containers easily.

```cpp
vector<int> numbers = {1, 2, 3, 4, 5};

// By value (copy)
for (int num : numbers) {
    cout << num << " ";
}

// By reference (no copy)
for (int& num : numbers) {
    num *= 2;  // Modify original values
}

// By const reference (read-only)
for (const int& num : numbers) {
    cout << num << " ";
}
```

---

## 🔀 Switch Statement
Alternative to long if-else chains for multiple discrete values.

```cpp
switch (expression) {
    case value1:
        // Code for value1
        break;
    case value2:
        // Code for value2
        break;
    case value3:
        // Code for value3
        break;
    default:
        // Code if no case matches
        break;
}
```

**Example:**
```cpp
int day = 3;
switch (day) {
    case 1:
        cout << "Monday" << endl;
        break;
    case 2:
        cout << "Tuesday" << endl;
        break;
    case 3:
        cout << "Wednesday" << endl;
        break;
    case 4:
        cout << "Thursday" << endl;
        break;
    case 5:
        cout << "Friday" << endl;
        break;
    case 6:
    case 7:
        cout << "Weekend" << endl;
        break;
    default:
        cout << "Invalid day" << endl;
        break;
}
```

**Important Notes:**
- `break` is crucial to prevent fall-through
- Multiple cases can share the same code
- `default` handles unmatched values

---

## 🚫 Loop Control Statements

### Break Statement
Exit a loop immediately.

```cpp
for (int i = 1; i <= 10; i++) {
    if (i == 5) {
        break;  // Exit loop when i equals 5
    }
    cout << i << " ";
}
cout << "Loop ended." << endl;

// Output: 1 2 3 4 Loop ended.
```

### Continue Statement
Skip current iteration and continue with next.

```cpp
for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
        continue;  // Skip even numbers
    }
    cout << i << " ";
}

// Output: 1 3 5 7 9
```

### Nested Loops with Break/Continue
```cpp
for (int i = 1; i <= 3; i++) {
    cout << "Outer loop iteration " << i << endl;
    
    for (int j = 1; j <= 5; j++) {
        if (j == 3) {
            continue;  // Skip j = 3
        }
        if (j == 5) {
            break;     // Exit inner loop when j = 5
        }
        cout << "  Inner loop: j = " << j << endl;
    }
}
```

---

## 🎯 Common Patterns

### Pattern 1: Input Validation
```cpp
int getValidAge() {
    int age;
    while (true) {
        cout << "Enter your age (1-120): ";
        cin >> age;
        
        if (age >= 1 && age <= 120) {
            return age;
        }
        cout << "Invalid age. Please try again." << endl;
    }
}
```

### Pattern 2: Menu System
```cpp
void showMenu() {
    cout << "=== Calculator Menu ===" << endl;
    cout << "1. Addition" << endl;
    cout << "2. Subtraction" << endl;
    cout << "3. Multiplication" << endl;
    cout << "4. Division" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

void calculator() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Addition selected" << endl;
                break;
            case 2:
                cout << "Subtraction selected" << endl;
                break;
            case 3:
                cout << "Multiplication selected" << endl;
                break;
            case 4:
                cout << "Division selected" << endl;
                break;
            case 5:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Try again." << endl;
        }
    } while (choice != 5);
}
```

### Pattern 3: Countdown Timer
```cpp
void countdown(int seconds) {
    for (int i = seconds; i > 0; i--) {
        cout << "Time remaining: " << i << " seconds" << endl;
        
        // Simulate time passing (in real app, use sleep)
        for (int j = 0; j < 100000000; j++) {
            // Busy wait
        }
    }
    cout << "Time's up!" << endl;
}
```

---

## 🚨 Common Pitfalls

### Pitfall 1: Infinite Loops
```cpp
// BAD: Missing update
int i = 0;
while (i < 5) {
    cout << i << endl;
    // i++;  // Missing! Creates infinite loop
}

// GOOD: Proper update
int i = 0;
while (i < 5) {
    cout << i << endl;
    i++;  // Update condition
}
```

### Pitfall 2: Missing Break in Switch
```cpp
// BAD: Missing break causes fall-through
int day = 1;
switch (day) {
    case 1:
        cout << "Monday" << endl;
        // Missing break!
    case 2:
        cout << "Tuesday" << endl;
        break;
}

// Output: Monday Tuesday (unexpected!)

// GOOD: Proper break statements
int day = 1;
switch (day) {
    case 1:
        cout << "Monday" << endl;
        break;  // Prevents fall-through
    case 2:
        cout << "Tuesday" << endl;
        break;
}
```

### Pitfall 3: Off-by-One Errors
```cpp
// BAD: Off-by-one error
for (int i = 0; i <= 5; i++) {  // Runs 6 times (0,1,2,3,4,5)
    cout << i << " ";
}

// GOOD: Correct bounds
for (int i = 0; i < 5; i++) {   // Runs 5 times (0,1,2,3,4)
    cout << i << " ";
}
```

---

## 🧪 Practice Examples

### Example 1: Number Guessing Game
```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));  // Seed random number generator
    int secretNumber = rand() % 100 + 1;  // 1 to 100
    int guess;
    int attempts = 0;
    
    cout << "=== Number Guessing Game ===" << endl;
    cout << "I'm thinking of a number between 1 and 100." << endl;
    
    do {
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++;
        
        if (guess < secretNumber) {
            cout << "Too low! Try again." << endl;
        } else if (guess > secretNumber) {
            cout << "Too high! Try again." << endl;
        } else {
            cout << "Congratulations! You guessed it in " << attempts << " attempts!" << endl;
        }
    } while (guess != secretNumber);
    
    return 0;
}
```

### Example 2: Multiplication Table Generator
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter a number for multiplication table: ";
    cin >> n;
    
    cout << "Multiplication table for " << n << ":" << endl;
    cout << "================================" << endl;
    
    for (int i = 1; i <= 10; i++) {
        cout << n << " × " << i << " = " << (n * i) << endl;
    }
    
    return 0;
}
```

### Example 3: Prime Number Checker
```cpp
#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int number;
    cout << "Enter a number to check if it's prime: ";
    cin >> number;
    
    if (isPrime(number)) {
        cout << number << " is a prime number." << endl;
    } else {
        cout << number << " is not a prime number." << endl;
    }
    
    return 0;
}
```

---

## 📚 What's Next?

After mastering control flow, explore:
1. **Functions** - Organizing code into reusable blocks
2. **Arrays & Vectors** - Working with collections of data
3. **Strings** - Text manipulation and processing
4. **Object-Oriented Programming** - Classes and objects

---

## 🔗 Related Topics
- [Basic Syntax & Structure](basic-syntax.md)
- [Data Types & Variables](data-types.md)
- [Functions](functions.md)
- [Arrays & Vectors](arrays-vectors.md)

---

## 💡 Key Takeaways

1. **Use appropriate control structures** for different scenarios
2. **Always update loop conditions** to avoid infinite loops
3. **Include break statements** in switch cases to prevent fall-through
4. **Test edge cases** and boundary conditions
5. **Keep loops simple** and readable

---

*"The best programs are written for people to read, and only incidentally for machines to execute." - Harold Abelson*
