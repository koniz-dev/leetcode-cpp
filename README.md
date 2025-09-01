# LeetCode C++23 Solutions Repository

A collection of LeetCode algorithm problem solutions implemented in **C++23** (ISO/IEC 14882:2023). This repository serves as a **learning resource and knowledge base** for modern C++ programming and algorithmic problem-solving.

## 🎯 Purpose

This repository is designed for:
- **Learning modern C++23 features** through practical examples
- **Storing algorithmic knowledge** and solution approaches
- **Reference material** for C++23 best practices
- **Personal study notes** and problem-solving techniques

## 🚀 C++23 Features Covered

This repository demonstrates modern C++23 features including:
- **std::ranges** - Modern range-based algorithms
- **std::views** - Lazy evaluation and composition
- **std::format** - Type-safe string formatting
- **std::expected** - Error handling without exceptions
- **Concepts** - Compile-time requirements checking
- **Structured Bindings** - Clean syntax for multiple values
- **constexpr improvements** - Better compile-time computation

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

docs/                     # C++23 knowledge base
├── coding-standards.md   # C++23 coding standards
├── optimized-checklist.md # Solution quality checklist
├── documentation-guide.md # How to document solutions
├── cpp-features.md       # Modern C++23 features guide
├── containers.md         # STL containers reference
├── algorithms.md         # Algorithm patterns
└── primitive-types.md    # Basic data types

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

This repository aims to:
- **Master C++23 features** and modern programming techniques
- **Improve algorithmic thinking** with contemporary C++
- **Practice modern C++ programming** best practices
- **Build comprehensive collection** of C++23 problem solutions
- **Share knowledge** with the C++ community

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

**Happy Learning with C++23! 🚀✨**

*This repository is designed as a knowledge base and learning resource. Focus on understanding the concepts and modern C++ techniques rather than complex build systems.*
