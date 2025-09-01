# 🚀 C++ Strings: Complete Guide

## 📚 Overview

Strings are fundamental for text processing in C++. C++ provides both C-style character arrays and the modern `std::string` class. Understanding both approaches and their trade-offs is essential for effective programming.

## 🎯 Key Concepts

### String Types in C++
- **C-style strings**: Null-terminated character arrays
- **std::string**: Modern C++ string class with automatic memory management
- **String literals**: Compile-time string constants

## 🔧 C-Style Strings

### Basic Declaration
```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    // Character array (C-style string)
    char str1[] = "Hello";
    char str2[10] = "World";
    char str3[20];  // Uninitialized
    
    // String literal
    const char* str4 = "Hello World";
    
    // Character by character initialization
    char str5[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    
    return 0;
}
```

### String Operations
```cpp
int main() {
    char str1[20] = "Hello";
    char str2[20] = "World";
    
    // String length
    cout << "Length: " << strlen(str1) << endl;  // 5
    
    // String copy
    strcpy(str1, str2);  // str1 becomes "World"
    
    // String concatenation
    strcat(str1, "!");
    cout << "Result: " << str1 << endl;  // "World!"
    
    // String comparison
    if (strcmp(str1, "World!") == 0) {
        cout << "Strings are equal" << endl;
    }
    
    return 0;
}
```

### Common C String Functions
```cpp
int main() {
    char str[100] = "Hello World";
    
    // Length
    size_t len = strlen(str);
    
    // Copy
    char dest[100];
    strcpy(dest, str);
    
    // Copy with length limit
    strncpy(dest, str, 5);  // Copy only 5 characters
    dest[5] = '\0';  // Ensure null termination
    
    // Concatenate
    strcat(dest, "!!!");
    
    // Compare
    int result = strcmp(str, dest);
    if (result < 0) cout << "str < dest" << endl;
    else if (result > 0) cout << "str > dest" << endl;
    else cout << "str == dest" << endl;
    
    // Find character
    char* found = strchr(str, 'o');  // Find first 'o'
    if (found) {
        cout << "Found 'o' at: " << (found - str) << endl;
    }
    
    // Find substring
    char* substr = strstr(str, "World");
    if (substr) {
        cout << "Found 'World' at: " << (substr - str) << endl;
    }
    
    return 0;
}
```

## 🚀 Modern C++ Strings (std::string)

### Basic String Operations
```cpp
#include <string>
#include <iostream>
using namespace std;

int main() {
    // String declaration
    string str1 = "Hello";
    string str2("World");
    string str3(5, 'x');  // 5 copies of 'x'
    
    // String assignment
    str1 = "New Hello";
    str1.assign("Another Hello");
    
    // String concatenation
    string result = str1 + " " + str2;
    str1 += " " + str2;
    
    // String comparison
    if (str1 == str2) {
        cout << "Strings are equal" << endl;
    }
    
    if (str1 < str2) {
        cout << "str1 comes before str2" << endl;
    }
    
    return 0;
}
```

### String Access and Iteration
```cpp
int main() {
    string str = "Hello World";
    
    // Access individual characters
    char first = str[0];        // 'H'
    char last = str.at(str.length() - 1);  // 'd'
    
    // String properties
    cout << "Length: " << str.length() << endl;
    cout << "Size: " << str.size() << endl;
    cout << "Empty: " << str.empty() << endl;
    cout << "Capacity: " << str.capacity() << endl;
    
    // Iterating through string
    for (size_t i = 0; i < str.length(); i++) {
        cout << str[i] << " ";
    }
    cout << endl;
    
    // Range-based for loop
    for (char c : str) {
        cout << c << " ";
    }
    cout << endl;
    
    // Iterator-based loop
    for (auto it = str.begin(); it != str.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    return 0;
}
```

### String Modifications
```cpp
int main() {
    string str = "Hello World";
    
    // Insert
    str.insert(5, " Beautiful ");  // "Hello Beautiful World"
    
    // Replace
    str.replace(6, 9, "Amazing");  // "Hello Amazing World"
    
    // Erase
    str.erase(6, 7);  // "Hello World"
    
    // Append
    str.append("!!!");
    str.push_back('!');  // Add single character
    
    // Resize
    str.resize(15, '*');  // Resize to 15, fill with '*'
    
    // Clear
    str.clear();
    
    return 0;
}
```

### String Searching
```cpp
int main() {
    string str = "Hello World Hello";
    
    // Find first occurrence
    size_t pos1 = str.find("Hello");
    if (pos1 != string::npos) {
        cout << "First 'Hello' at: " << pos1 << endl;
    }
    
    // Find last occurrence
    size_t pos2 = str.rfind("Hello");
    if (pos2 != string::npos) {
        cout << "Last 'Hello' at: " << pos2 << endl;
    }
    
    // Find first occurrence of any character
    size_t pos3 = str.find_first_of("aeiou");
    if (pos3 != string::npos) {
        cout << "First vowel at: " << pos3 << endl;
    }
    
    // Find first occurrence not of any character
    size_t pos4 = str.find_first_not_of("aeiou");
    if (pos4 != string::npos) {
        cout << "First non-vowel at: " << pos4 << endl;
    }
    
    // Substring
    string sub = str.substr(6, 5);  // "World"
    
    return 0;
}
```

## 🔄 String Conversion

### String to Number
```cpp
#include <string>
#include <iostream>
using namespace std;

int main() {
    string str1 = "42";
    string str2 = "3.14";
    
    // String to integer
    int num1 = stoi(str1);
    long num2 = stol(str1);
    
    // String to floating point
    float num3 = stof(str2);
    double num4 = stod(str2);
    
    // With base specification
    int hex = stoi("1A", nullptr, 16);  // 26
    
    // Error handling
    try {
        int invalid = stoi("not a number");
    } catch (const invalid_argument& e) {
        cout << "Invalid argument: " << e.what() << endl;
    } catch (const out_of_range& e) {
        cout << "Out of range: " << e.what() << endl;
    }
    
    return 0;
}
```

### Number to String
```cpp
int main() {
    int num1 = 42;
    double num2 = 3.14;
    
    // Number to string
    string str1 = to_string(num1);
    string str2 = to_string(num2);
    
    // With formatting (C++20)
    // string str3 = format("Number: {}", num1);
    
    cout << "String 1: " << str1 << endl;
    cout << "String 2: " << str2 << endl;
    
    return 0;
}
```

## 🎭 String Formatting

### Basic Formatting
```cpp
int main() {
    string name = "Alice";
    int age = 25;
    double height = 1.75;
    
    // String concatenation
    string info = "Name: " + name + ", Age: " + to_string(age);
    
    // Using stringstream for complex formatting
    #include <sstream>
    stringstream ss;
    ss << "Name: " << name << ", Age: " << age << ", Height: " << height;
    string formatted = ss.str();
    
    // C++20 format (if available)
    // string formatted = format("Name: {}, Age: {}, Height: {:.2f}", name, age, height);
    
    cout << formatted << endl;
    
    return 0;
}
```

## 🔧 String Utilities

### String Manipulation
```cpp
#include <algorithm>
#include <cctype>

int main() {
    string str = "  Hello World  ";
    
    // Trim whitespace
    str.erase(0, str.find_first_not_of(" \t\n\r"));
    str.erase(str.find_last_not_of(" \t\n\r") + 1);
    
    // Convert to uppercase
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    
    // Convert to lowercase
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    
    // Reverse string
    reverse(str.begin(), str.end());
    
    // Sort characters
    sort(str.begin(), str.end());
    
    // Remove duplicates (requires sorted string)
    str.erase(unique(str.begin(), str.end()), str.end());
    
    return 0;
}
```

### String Splitting
```cpp
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

int main() {
    string text = "apple,banana,cherry,date";
    vector<string> fruits = split(text, ',');
    
    for (const string& fruit : fruits) {
        cout << fruit << endl;
    }
    
    return 0;
}
```

## 🎯 Performance Considerations

### String vs C-String Performance
```cpp
#include <chrono>

void benchmark() {
    const int iterations = 100000;
    
    // C-string concatenation
    auto start = chrono::high_resolution_clock::now();
    char result[1000] = "";
    for (int i = 0; i < iterations; i++) {
        strcat(result, "test");
    }
    auto end = chrono::high_resolution_clock::now();
    auto c_time = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // std::string concatenation
    start = chrono::high_resolution_clock::now();
    string str_result;
    for (int i = 0; i < iterations; i++) {
        str_result += "test";
    }
    end = chrono::high_resolution_clock::now();
    auto str_time = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "C-string time: " << c_time.count() << " μs" << endl;
    cout << "std::string time: " << str_time.count() << " μs" << endl;
}
```

### Memory Management
```cpp
int main() {
    string str;
    
    // Reserve capacity to avoid reallocation
    str.reserve(1000);
    
    // Add characters (no reallocation until capacity exceeded)
    for (int i = 0; i < 1000; i++) {
        str += 'a';
    }
    
    // Shrink to fit
    str.shrink_to_fit();
    
    return 0;
}
```

## 📝 Best Practices

### 1. Choose the Right String Type
```cpp
// Use C-strings when:
// - Working with C libraries
// - Maximum performance is critical
// - Memory is very limited

// Use std::string when:
// - Writing modern C++ code
// - Need automatic memory management
// - Want rich string operations
```

### 2. Efficient String Operations
```cpp
// Good: Reserve capacity
string result;
result.reserve(1000);
for (int i = 0; i < 1000; i++) {
    result += "item";
}

// Bad: Frequent reallocation
string result;
for (int i = 0; i < 1000; i++) {
    result += "item";  // May cause multiple reallocations
}
```

### 3. Safe String Access
```cpp
// Good: Check bounds
if (index < str.length()) {
    char c = str[index];
}

// Good: Use .at() for bounds checking
try {
    char c = str.at(index);
} catch (const out_of_range& e) {
    cout << "Index out of range" << endl;
}
```

### 4. String Comparison
```cpp
// Good: Use == for std::string
if (str1 == str2) { /* ... */ }

// Good: Use strcmp for C-strings
if (strcmp(cstr1, cstr2) == 0) { /* ... */ }

// Bad: Don't compare C-strings with ==
if (cstr1 == cstr2) { /* This compares pointers! */ }
```

## 🚀 Advanced Techniques

### Regular Expressions (C++11+)
```cpp
#include <regex>

int main() {
    string text = "Email: john@example.com, Phone: 123-456-7890";
    
    // Email pattern
    regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    
    // Find all emails
    sregex_iterator it(text.begin(), text.end(), email_pattern);
    sregex_iterator end;
    
    for (; it != end; ++it) {
        cout << "Found email: " << it->str() << endl;
    }
    
    // Replace pattern
    string result = regex_replace(text, email_pattern, "[EMAIL]");
    cout << "Result: " << result << endl;
    
    return 0;
}
```

### String Views (C++17+)
```cpp
#include <string_view>

void processString(string_view str) {
    // No copying, just view into existing string
    cout << "Processing: " << str << endl;
    
    // Can use most string operations
    if (str.starts_with("Hello")) {
        cout << "Starts with Hello" << endl;
    }
}

int main() {
    string str = "Hello World";
    processString(str);
    processString("Another string");  // Works with string literals
    
    return 0;
}
```

## 🎯 Practice Problems

### Problem 1: Check Palindrome
```cpp
bool isPalindrome(const string& str) {
    int left = 0, right = str.length() - 1;
    while (left < right) {
        if (str[left] != str[right]) return false;
        left++;
        right--;
    }
    return true;
}
```

### Problem 2: Find Longest Common Prefix
```cpp
string longestCommonPrefix(const vector<string>& strs) {
    if (strs.empty()) return "";
    
    string prefix = strs[0];
    for (const string& str : strs) {
        while (str.find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.length() - 1);
            if (prefix.empty()) return "";
        }
    }
    return prefix;
}
```

### Problem 3: Valid Parentheses
```cpp
bool isValidParentheses(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            if ((c == ')' && st.top() != '(') ||
                (c == '}' && st.top() != '{') ||
                (c == ']' && st.top() != '[')) {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}
```

## 📚 Summary

Key takeaways:
- **C-strings**: Fast, memory-efficient, but manual management
- **std::string**: Safe, feature-rich, automatic memory management
- **Choose wisely** based on performance vs. safety requirements
- **Use modern C++ features** when available
- **Handle errors** properly with bounds checking
- **Optimize performance** with reserve() and efficient operations

Master both approaches to write efficient, safe C++ code!

---

## 🔗 Related Topics
- [Data Types](data-types.md)
- [Arrays & Vectors](arrays-vectors.md)
- [STL Containers](stl-containers.md)
- [STL Algorithms](stl-algorithms.md)
