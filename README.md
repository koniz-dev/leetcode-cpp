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
├── 217. Contains Duplicate/
│   ├── main.cpp
│   ├── optimized.cpp
│   └── README.md
└── [Future problems will be added here]

docs/                     # Documentation and templates
├── coding-standards.md   # Coding style and standards
├── optimized-checklist.md # Checklist for solution quality
├── documentation-guide.md # How to document solutions
├── cpp-features.md       # Modern C++ features reference
├── containers.md         # STL containers reference
├── algorithms.md         # Algorithm patterns reference
└── primitive-types.md    # Basic data types reference

templates/                # Reusable solution templates
└── optimized_template.cpp # C++23 solution template
```

## 📚 Problems Solved

### 1. Two Sum
- **Problem**: Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.
- **Difficulty**: Easy
- **C++23 Solution**: [View Optimized Solution](src/1.%20Two%20Sum/optimized.cpp)
- **User Solution**: [View User Solution](src/1.%20Two%20Sum/main.cpp)

### 217. Contains Duplicate
- **Problem**: Given an integer array `nums`, return `true` if any value appears at least twice in the array, and return `false` if every element is distinct.
- **Difficulty**: Easy
- **C++23 Solution**: [View Optimized Solution](src/217.%20Contains%20Duplicate/optimized.cpp)
- **User Solution**: [View User Solution](src/217.%20Contains%20Duplicate/main.cpp)

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

## 📊 Progress Tracking

- **Total Problems**: 2
- **Easy**: 2
- **Medium**: 0
- **Hard**: 0
- **C++23 Features Used**: std::ranges, std::views, std::format

## 🔗 Useful Resources

- [LeetCode Official Website](https://leetcode.com/)
- [C++23 Reference](https://en.cppreference.com/w/cpp/23)
- [C++23 Standard](https://isocpp.org/std/the-standard)
- [std::ranges Documentation](https://en.cppreference.com/w/cpp/ranges)
- [std::views Documentation](https://en.cppreference.com/w/cpp/ranges#Range_adaptors)
- [Algorithm Visualization](https://visualgo.net/)

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
