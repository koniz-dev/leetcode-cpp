# LeetCode C++ Solutions Repository

A collection of LeetCode algorithm problem solutions implemented in **modern C++**. This repository serves as a **learning platform** to help me become a **master of C++ and DSA** through systematic problem-solving.

## 🎯 Purpose

This repository is designed for:
- **Learning and mastering DSA concepts** through practical problem-solving
- **Improving C++ programming skills** using modern features when beneficial
- **Building comprehensive knowledge** of algorithms and data structures
- **Systematic learning** to become a C++ and DSA master

## 🚀 Modern C++ Features

This repository uses modern C++ features to write clean, efficient, and maintainable solutions:
- **Modern algorithms** - Range-based algorithms and efficient data processing
- **Smart containers** - Appropriate data structures for each problem
- **Error handling** - Robust and safe code practices
- **Advanced concepts** - Templates, concepts, and compile-time features
- **Performance optimization** - Move semantics, perfect forwarding, and efficient code


## 📚 Problems Solved

### 🎯 Array & Hashing
**Key Patterns:**
- **Hash Map/Set**: Two Sum, Contains Duplicate, Valid Anagram, Group Anagrams
- **Array Manipulation**: Product of Array Except Self, Longest Consecutive Sequence
- **String Processing**: Valid Anagram, Group Anagrams, Encode and Decode Strings
- **Matrix/2D Arrays**: Valid Sudoku
- **Frequency Counting**: Top K Frequent Elements, Valid Anagram, Group Anagrams

**Problems:**
- **[1. Two Sum](src/1.%20Two%20Sum/)** - Easy
- **[36. Valid Sudoku](src/36.%20Valid%20Sudoku/)** - Medium  
- **[49. Group Anagrams](src/49.%20Group%20Anagrams/)** - Medium
- **[128. Longest Consecutive Sequence](src/128.%20Longest%20Consecutive%20Sequence/)** - Medium
- **[217. Contains Duplicate](src/217.%20Contains%20Duplicate/)** - Easy
- **[238. Product of Array Except Self](src/238.%20Product%20of%20Array%20Except%20Self/)** - Medium
- **[242. Valid Anagram](src/242.%20Valid%20Anagram/)** - Easy
- **[271. Encode and Decode Strings](src/271.%20Encode%20and%20Decode%20Strings/)** - Medium
- **[347. Top K Frequent Elements](src/347.%20Top%20K%20Frequent%20Elements/)** - Medium

### 🎯 Two Pointers
**Key Patterns:**
- **Opposite Direction**: Valid Palindrome, Container With Most Water
- **Same Direction**: Two Sum II - Input Array Is Sorted, 3Sum
- **Prefix/Suffix Arrays**: Trapping Rain Water
- **Greedy + Two Pointers**: Container With Most Water
- **Sorting + Two Pointers**: 3Sum

**Problems:**
- **[11. Container With Most Water](src/11.%20Container%20With%20Most%20Water/)** - Medium
- **[15. 3Sum](src/15.%203Sum/)** - Medium
- **[42. Trapping Rain Water](src/42.%20Trapping%20Rain%20Water/)** - Hard
- **[125. Valid Palindrome](src/125.%20Valid%20Palindrome/)** - Easy
- **[167. Two Sum II - Input Array Is Sorted](src/167.%20Two%20Sum%20II%20-%20Input%20Array%20Is%20Sorted/)** - Easy

## 🛠️ Development Setup

### Simple Compilation
For basic testing, you can compile individual solutions:

```bash
# Navigate to problem directory
cd "src/1. Two Sum"

# Compile with C++23
g++ -std=c++23 -O2 main.cpp -o solution
# or
clang++ -std=c++23 -O2 main.cpp -o solution

# Run
./solution
```

### Compiler Requirements
- **GCC**: Version 13+ with `-std=c++23`
- **Clang**: Version 17+ with `-std=c++23`
- **MSVC**: Version 19.35+ with `/std:c++23`

## 📝 Contributing

1. Fork the repository
2. Create a new branch for your solution
3. Add your solution in the appropriate problem directory
4. Follow the existing naming convention: `Problem Number. Problem Name/`
5. Submit a pull request

### Solution Guidelines

- **Use C++23 standard** - Leverage modern features when beneficial
- **Write clear, readable code** with proper comments
- **Include problem description** in comments
- **Follow C++23 best practices** - RAII, smart pointers, constexpr
- **Test solutions** with multiple test cases
- **Include time and space complexity analysis**
- **Document C++23 features used** in your solution

## 🧠 Learning Approach

### Comprehensive Documentation System
- **Problem-Specific Learning**: Each problem includes detailed README with multiple approaches
- **C++ Mastery**: Extensive C++ documentation covering fundamentals to advanced topics
- **DSA Foundation**: Complete data structures and algorithms reference
- **Pattern Recognition**: Common algorithmic patterns and when to use them
- **Progressive Learning**: Structured roadmap from basics to advanced concepts

### Knowledge Building Strategy
- **Theory + Practice**: Combine conceptual understanding with hands-on coding
- **Multiple Solutions**: Learn different approaches to the same problem
- **Modern C++**: Use latest C++23 features for efficient and clean code
- **Systematic Progress**: Track learning through comprehensive documentation
- **Mastery Focus**: Deep understanding over quick solutions

## 📊 Progress Tracking

### Quick Stats
- **Total Problems**: 14
- **Categories**: Array & Hashing, Two Pointers
- **Easy**: 5 | **Medium**: 8 | **Hard**: 1

### C++23 Features Used
- **STL Containers**: std::unordered_map, std::unordered_set, std::priority_queue, std::vector, std::string
- **STL Algorithms**: std::sort, std::transform, std::accumulate, std::ranges, std::is_sorted, std::max_element
- **Modern C++**: std::ranges, std::views, std::format, auto keyword, structured bindings, constexpr
- **Two Pointers**: Efficient array traversal, sliding window techniques, greedy algorithms

## 📖 Learning Resources

### Repository Documentation
- **[Learning Roadmap](docs/LEARNING_ROADMAP.md)** - Comprehensive learning path for C++ and DSA mastery
- **[C++ Documentation](docs/cpp/)** - Complete C++ programming concepts and modern features
- **[DSA Documentation](docs/dsa/)** - Data structures and algorithms fundamentals to advanced topics
- **[Algorithm Patterns](docs/patterns/)** - Common algorithmic patterns and techniques
- **[Problem Categories](docs/categories/)** - Problems organized by topic and difficulty

### External Resources
- [LeetCode Official Website](https://leetcode.com/)
- [Neetcode 150 Roadmap](https://neetcode.io/roadmap)
- [C++23 Reference](https://en.cppreference.com/w/cpp/23)
- [C++23 Standard](https://isocpp.org/std/the-standard)
- [std::ranges Documentation](https://en.cppreference.com/w/cpp/ranges)
- [std::views Documentation](https://en.cppreference.com/w/cpp/ranges#Range_adaptors)
- [Algorithm Visualization](https://visualgo.net/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Modern C++ Features](https://github.com/AnthonyCalandra/modern-cpp-features)

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 🤝 Acknowledgments

- **ISO C++ Committee** for C++23 standard
- **LeetCode** for providing excellent algorithmic problems
- **The C++ community** for continuous improvements to the language
- **All contributors** who help improve this repository

---

**Happy Learning! 🚀✨**

*This repository is designed for comprehensive learning and mastery building, focusing on DSA concepts and modern C++ programming.*
