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

## 📁 Repository Structure

```
src/
├── 1. Two Sum/
│   ├── main.cpp          # User's personal solution (NEVER modified)
│   ├── optimized.cpp     # Most efficient C++23 solution
│   └── README.md         # Comprehensive documentation
├── 36. Valid Sudoku/
├── 49. Group Anagrams/
├── 128. Longest Consecutive Sequence/
├── 217. Contains Duplicate/
├── 238. Product of Array Except Self/
├── 242. Valid Anagram/
├── 271. Encode and Decode Strings/
├── 347. Top K Frequent Elements/
└── [Future problems will be added here]

docs/                     # Comprehensive learning documentation
├── categories/           # Problem categorization
│   └── arrays-strings.md
├── cpp/                  # C++ programming concepts
│   ├── advanced-concurrency.md
│   ├── advanced-stl.md
│   ├── arrays-vectors.md
│   ├── basic-syntax.md
│   ├── compiler-internals.md
│   ├── concurrency.md
│   ├── control-flow.md
│   ├── custom-stl.md
│   ├── data-types.md
│   ├── design-patterns.md
│   ├── exception-handling.md
│   ├── functions.md
│   ├── fundamentals.md
│   ├── io-operations.md
│   ├── lambda-expressions.md
│   ├── memory-management.md
│   ├── modern-features.md
│   ├── move-semantics.md
│   ├── oop-concepts.md
│   ├── performance-optimization.md
│   ├── smart-pointers.md
│   ├── stl-algorithms.md
│   ├── stl-containers.md
│   ├── strings.md
│   ├── template-metaprogramming.md
│   └── templates.md
├── dsa/                  # Data Structures & Algorithms
│   ├── advanced-dp.md
│   ├── advanced-graphs.md
│   ├── advanced-string-matching.md
│   ├── advanced-trees.md
│   ├── algorithm-design.md
│   ├── basic-algorithms.md
│   ├── basic-data-structures.md
│   ├── basics.md
│   ├── competitive-programming.md
│   ├── complexity-analysis.md
│   ├── core-patterns.md
│   ├── custom-data-structures.md
│   ├── geometric-algorithms.md
│   ├── introduction.md
│   ├── network-flow.md
│   ├── problem-creation.md
│   ├── research-algorithms.md
│   └── string-algorithms.md
├── patterns/             # Algorithm patterns
│   ├── backtracking.md
│   ├── binary-search.md
│   ├── dynamic-programming.md
│   ├── graph-algorithms.md
│   ├── greedy.md
│   ├── sliding-window.md
│   ├── tree-traversal.md
│   └── two-pointers.md
├── LEARNING_ROADMAP.md   # Comprehensive learning path
└── README.md

templates/                # Reusable solution templates
└── optimized_template.cpp # C++23 solution template
```

## 📚 Problems Solved

### 🎯 Array & Hashing (Neetcode Roadmap)
*These 9 problems represent the core Array & Hashing patterns from the Neetcode 150 roadmap*

**Key Patterns Covered:**
- **Hash Map/Set**: Two Sum, Contains Duplicate, Valid Anagram, Group Anagrams
- **Array Manipulation**: Product of Array Except Self, Longest Consecutive Sequence
- **String Processing**: Valid Anagram, Group Anagrams, Encode and Decode Strings
- **Matrix/2D Arrays**: Valid Sudoku
- **Frequency Counting**: Top K Frequent Elements, Valid Anagram, Group Anagrams

### 1. Two Sum
- **Problem**: Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.
- **Difficulty**: Easy
- **C++23 Solution**: [View Optimized Solution](src/1.%20Two%20Sum/optimized.cpp)
- **User Solution**: [View User Solution](src/1.%20Two%20Sum/main.cpp)

### 36. Valid Sudoku
- **Problem**: Determine if a 9x9 Sudoku board is valid.
- **Difficulty**: Medium
- **C++23 Solution**: [View Optimized Solution](src/36.%20Valid%20Sudoku/optimized.cpp)
- **User Solution**: [View User Solution](src/36.%20Valid%20Sudoku/main.cpp)

### 49. Group Anagrams
- **Problem**: Given an array of strings `strs`, group the anagrams together.
- **Difficulty**: Medium
- **C++23 Solution**: [View Optimized Solution](src/49.%20Group%20Anagrams/optimized.cpp)
- **User Solution**: [View User Solution](src/49.%20Group%20Anagrams/main.cpp)

### 128. Longest Consecutive Sequence
- **Problem**: Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.
- **Difficulty**: Medium
- **C++23 Solution**: [View Optimized Solution](src/128.%20Longest%20Consecutive%20Sequence/optimized.cpp)
- **User Solution**: [View User Solution](src/128.%20Longest%20Consecutive%20Sequence/main.cpp)

### 217. Contains Duplicate
- **Problem**: Given an integer array `nums`, return `true` if any value appears at least twice in the array, and return `false` if every element is distinct.
- **Difficulty**: Easy
- **C++23 Solution**: [View Optimized Solution](src/217.%20Contains%20Duplicate/optimized.cpp)
- **User Solution**: [View User Solution](src/217.%20Contains%20Duplicate/main.cpp)

### 238. Product of Array Except Self
- **Problem**: Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` except `nums[i]`.
- **Difficulty**: Medium
- **C++23 Solution**: [View Optimized Solution](src/238.%20Product%20of%20Array%20Except%20Self/optimized.cpp)
- **User Solution**: [View User Solution](src/238.%20Product%20of%20Array%20Except%20Self/main.cpp)

### 242. Valid Anagram
- **Problem**: Given two strings `s` and `t`, return `true` if `t` is an anagram of `s`, and `false` otherwise.
- **Difficulty**: Easy
- **C++23 Solution**: [View Optimized Solution](src/242.%20Valid%20Anagram/optimized.cpp)
- **User Solution**: [View User Solution](src/242.%20Valid%20Anagram/main.cpp)

### 271. Encode and Decode Strings
- **Problem**: Design an algorithm to encode a list of strings to a string and decode the string back to the original list of strings.
- **Difficulty**: Medium
- **C++23 Solution**: [View Optimized Solution](src/271.%20Encode%20and%20Decode%20Strings/optimized.cpp)
- **User Solution**: [View User Solution](src/271.%20Encode%20and%20Decode%20Strings/main.cpp)

### 347. Top K Frequent Elements
- **Problem**: Given an integer array `nums` and an integer `k`, return the `k` most frequent elements.
- **Difficulty**: Medium
- **C++23 Solution**: [View Optimized Solution](src/347.%20Top%20K%20Frequent%20Elements/optimized.cpp)
- **User Solution**: [View User Solution](src/347.%20Top%20K%20Frequent%20Elements/main.cpp)

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

## 🎯 Learning Goals

This repository helps me:
- **Master DSA concepts** through systematic problem-solving
- **Master C++ programming** using modern features and best practices
- **Build comprehensive knowledge** of algorithms and data structures
- **Achieve mastery** in both C++ and DSA
- **Learn from different approaches** to the same problem
- **Write high-quality, efficient code** using appropriate C++ features

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

### Current Status
- **Total Problems**: 9
- **Array & Hashing (Neetcode)**: 9/9 ✅ **COMPLETED**
- **Easy**: 3 (Two Sum, Contains Duplicate, Valid Anagram)
- **Medium**: 6 (Valid Sudoku, Group Anagrams, Longest Consecutive Sequence, Product of Array Except Self, Encode and Decode Strings, Top K Frequent Elements)
- **Hard**: 0

### C++23 Features Used
- **STL Containers**: std::unordered_map, std::unordered_set, std::priority_queue, std::vector
- **STL Algorithms**: std::sort, std::transform, std::accumulate, std::ranges
- **Modern C++**: std::ranges, std::views, std::format, auto keyword, structured bindings

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
