# 🎯 Problem Creation

## 📚 Overview

Problem creation is the art of designing interesting, educational, and challenging computational problems. This guide covers how to create problems that test different skills, from basic algorithmic thinking to advanced problem-solving techniques.

## 🎯 Problem Design Principles

### Educational Value
- **Target specific concepts** and algorithms
- **Progressive difficulty** from basic to advanced
- **Multiple solution approaches** to encourage creativity
- **Real-world applications** when possible

### Technical Quality
- **Clear problem statements** with unambiguous requirements
- **Well-defined constraints** and edge cases
- **Efficient solutions** exist within given constraints
- **Proper test cases** covering various scenarios

### Engagement
- **Interesting problem scenarios** that capture attention
- **Multiple difficulty levels** for different skill sets
- **Creative twists** on classic problems
- **Competitive elements** when appropriate

## 🔧 Problem Structure Framework

### Problem Statement Template
```cpp
// Problem creation template
struct ProblemTemplate {
    std::string title;
    std::string description;
    std::string input_format;
    std::string output_format;
    std::vector<std::string> constraints;
    std::vector<std::string> examples;
    std::vector<std::string> notes;
    
    // Difficulty classification
    enum Difficulty {
        EASY,
        MEDIUM,
        HARD,
        EXPERT
    } difficulty;
    
    // Problem category
    enum Category {
        ARRAYS,
        STRINGS,
        TREES,
        GRAPHS,
        DYNAMIC_PROGRAMMING,
        GREEDY,
        MATH,
        GEOMETRY,
        STRINGS,
        OTHER
    } category;
    
    // Expected solution characteristics
    struct SolutionProfile {
        std::string time_complexity;
        std::string space_complexity;
        std::vector<std::string> key_algorithms;
        std::vector<std::string> key_data_structures;
    } solution_profile;
};

// Example problem creation
ProblemTemplate create_sample_problem() {
    ProblemTemplate problem;
    
    problem.title = "Maximum Subarray Sum";
    problem.description = "Given an array of integers, find the contiguous subarray with the largest sum.";
    problem.input_format = "First line contains N (1 ≤ N ≤ 10^5), the size of array.\nSecond line contains N integers separated by spaces.";
    problem.output_format = "Print a single integer representing the maximum subarray sum.";
    problem.constraints = {
        "1 ≤ N ≤ 10^5",
        "-10^4 ≤ A[i] ≤ 10^4",
        "Array may contain negative numbers"
    };
    problem.examples = {
        "Input:\n5\n-2 1 -3 4 -1\n\nOutput:\n4\n\nExplanation: The subarray [4] has the largest sum of 4.",
        "Input:\n3\n-1 -2 -3\n\nOutput:\n-1\n\nExplanation: The subarray [-1] has the largest sum of -1."
    };
    problem.notes = {
        "Consider the case when all numbers are negative",
        "The solution should handle empty subarrays if allowed"
    };
    problem.difficulty = ProblemTemplate::MEDIUM;
    problem.category = ProblemTemplate::ARRAYS;
    
    problem.solution_profile.time_complexity = "O(n)";
    problem.solution_profile.space_complexity = "O(1)";
    problem.solution_profile.key_algorithms = {"Kadane's Algorithm", "Dynamic Programming"};
    problem.solution_profile.key_data_structures = {"Array"};
    
    return problem;
}
```

### Constraint Design
```cpp
// Constraint design helper
class ConstraintDesigner {
public:
    struct ConstraintSet {
        size_t min_n, max_n;
        int min_value, max_value;
        bool allow_negative;
        bool allow_duplicates;
        bool require_stable_sort;
        std::string memory_limit;
        std::string time_limit;
        std::vector<std::string> special_constraints;
    };
    
    // Design constraints for different difficulty levels
    static ConstraintSet design_constraints(ProblemTemplate::Difficulty difficulty) {
        ConstraintSet constraints;
        
        switch (difficulty) {
            case ProblemTemplate::EASY:
                constraints.min_n = 1;
                constraints.max_n = 100;
                constraints.min_value = -1000;
                constraints.max_value = 1000;
                constraints.allow_negative = false;
                constraints.allow_duplicates = true;
                constraints.memory_limit = "256 MB";
                constraints.time_limit = "1 second";
                break;
                
            case ProblemTemplate::MEDIUM:
                constraints.min_n = 1;
                constraints.max_n = 10000;
                constraints.min_value = -100000;
                constraints.max_value = 100000;
                constraints.allow_negative = true;
                constraints.allow_duplicates = true;
                constraints.memory_limit = "256 MB";
                constraints.time_limit = "2 seconds";
                break;
                
            case ProblemTemplate::HARD:
                constraints.min_n = 1;
                constraints.max_n = 100000;
                constraints.min_value = -1000000000;
                constraints.max_value = 1000000000;
                constraints.allow_negative = true;
                constraints.allow_duplicates = true;
                constraints.memory_limit = "512 MB";
                constraints.time_limit = "5 seconds";
                break;
                
            case ProblemTemplate::EXPERT:
                constraints.min_n = 1;
                constraints.max_n = 1000000;
                constraints.min_value = -1000000000;
                constraints.max_value = 1000000000;
                constraints.allow_negative = true;
                constraints.allow_duplicates = true;
                constraints.memory_limit = "1 GB";
                constraints.time_limit = "10 seconds";
                break;
        }
        
        return constraints;
    }
    
    // Validate that constraints allow efficient solutions
    static bool validate_constraints(const ConstraintSet& constraints, 
                                   const std::string& expected_complexity) {
        // Check if constraints are reasonable for the expected solution
        if (expected_complexity.find("O(n)") != std::string::npos) {
            return constraints.max_n <= 1000000;  // O(n) should handle 10^6
        } else if (expected_complexity.find("O(n log n)") != std::string::npos) {
            return constraints.max_n <= 100000;   // O(n log n) should handle 10^5
        } else if (expected_complexity.find("O(n^2)") != std::string::npos) {
            return constraints.max_n <= 10000;    // O(n^2) should handle 10^4
        }
        
        return true;
    }
};
```

## 🚀 Problem Generation Techniques

### Problem Variation Generator
```cpp
// Generate variations of classic problems
class ProblemVariationGenerator {
public:
    // Generate array problem variations
    static std::vector<ProblemTemplate> generate_array_variations() {
        std::vector<ProblemTemplate> variations;
        
        // Variation 1: Find maximum subarray sum
        ProblemTemplate max_subarray = create_max_subarray_problem();
        variations.push_back(max_subarray);
        
        // Variation 2: Find minimum subarray sum
        ProblemTemplate min_subarray = create_min_subarray_problem();
        variations.push_back(min_subarray);
        
        // Variation 3: Find subarray with given sum
        ProblemTemplate target_sum = create_target_sum_problem();
        variations.push_back(target_sum);
        
        // Variation 4: Find longest subarray with given property
        ProblemTemplate longest_subarray = create_longest_subarray_problem();
        variations.push_back(longest_subarray);
        
        return variations;
    }
    
    // Generate tree problem variations
    static std::vector<ProblemTemplate> generate_tree_variations() {
        std::vector<ProblemTemplate> variations;
        
        // Variation 1: Find diameter of tree
        ProblemTemplate diameter = create_tree_diameter_problem();
        variations.push_back(diameter);
        
        // Variation 2: Find longest path in tree
        ProblemTemplate longest_path = create_longest_path_problem();
        variations.push_back(longest_path);
        
        // Variation 3: Find nodes at given distance
        ProblemTemplate distance_nodes = create_distance_nodes_problem();
        variations.push_back(distance_nodes);
        
        return variations;
    }
    
private:
    static ProblemTemplate create_max_subarray_problem() {
        ProblemTemplate problem;
        problem.title = "Maximum Subarray Sum";
        problem.description = "Find the contiguous subarray with the largest sum.";
        problem.difficulty = ProblemTemplate::MEDIUM;
        problem.category = ProblemTemplate::ARRAYS;
        return problem;
    }
    
    static ProblemTemplate create_min_subarray_problem() {
        ProblemTemplate problem;
        problem.title = "Minimum Subarray Sum";
        problem.description = "Find the contiguous subarray with the smallest sum.";
        problem.difficulty = ProblemTemplate::MEDIUM;
        problem.category = ProblemTemplate::ARRAYS;
        return problem;
    }
    
    static ProblemTemplate create_target_sum_problem() {
        ProblemTemplate problem;
        problem.title = "Subarray with Target Sum";
        problem.description = "Find a contiguous subarray that sums to a given target value.";
        problem.difficulty = ProblemTemplate::MEDIUM;
        problem.category = ProblemTemplate::ARRAYS;
        return problem;
    }
    
    static ProblemTemplate create_longest_subarray_problem() {
        ProblemTemplate problem;
        problem.title = "Longest Subarray with Property";
        problem.description = "Find the longest contiguous subarray that satisfies a given property.";
        problem.difficulty = ProblemTemplate::HARD;
        problem.category = ProblemTemplate::ARRAYS;
        return problem;
    }
    
    static ProblemTemplate create_tree_diameter_problem() {
        ProblemTemplate problem;
        problem.title = "Tree Diameter";
        problem.description = "Find the diameter of a tree (longest path between any two nodes).";
        problem.difficulty = ProblemTemplate::MEDIUM;
        problem.category = ProblemTemplate::TREES;
        return problem;
    }
    
    static ProblemTemplate create_longest_path_problem() {
        ProblemTemplate problem;
        problem.title = "Longest Path in Tree";
        problem.description = "Find the longest path in a tree with given constraints.";
        problem.difficulty = ProblemTemplate::HARD;
        problem.category = ProblemTemplate::TREES;
        return problem;
    }
    
    static ProblemTemplate create_distance_nodes_problem() {
        ProblemTemplate problem;
        problem.title = "Nodes at Given Distance";
        problem.description = "Find all nodes at a given distance from a source node.";
        problem.difficulty = ProblemTemplate::MEDIUM;
        problem.category = ProblemTemplate::TREES;
        return problem;
    }
};
```

### Test Case Generator
```cpp
// Generate comprehensive test cases
class TestCaseGenerator {
public:
    // Generate test cases for array problems
    static std::vector<std::pair<std::string, std::string>> generate_array_test_cases() {
        std::vector<std::pair<std::string, std::string>> test_cases;
        
        // Test case 1: Small positive array
        test_cases.emplace_back(
            "5\n1 2 3 4 5",
            "15"
        );
        
        // Test case 2: Array with negative numbers
        test_cases.emplace_back(
            "5\n-2 1 -3 4 -1",
            "4"
        );
        
        // Test case 3: All negative numbers
        test_cases.emplace_back(
            "3\n-1 -2 -3",
            "-1"
        );
        
        // Test case 4: Single element
        test_cases.emplace_back(
            "1\n42",
            "42"
        );
        
        // Test case 5: Large array
        std::string large_input = "100000\n";
        std::string large_output = "100000\n";
        for (int i = 0; i < 100000; ++i) {
            large_input += "1 ";
        }
        test_cases.emplace_back(large_input, large_output);
        
        return test_cases;
    }
    
    // Generate edge case test cases
    static std::vector<std::pair<std::string, std::string>> generate_edge_cases() {
        std::vector<std::pair<std::string, std::string>> edge_cases;
        
        // Edge case 1: Empty array (if allowed)
        edge_cases.emplace_back("0\n", "0");
        
        // Edge case 2: Maximum values
        edge_cases.emplace_back("3\n1000000000 1000000000 1000000000", "3000000000");
        
        // Edge case 3: Minimum values
        edge_cases.emplace_back("3\n-1000000000 -1000000000 -1000000000", "-1000000000");
        
        // Edge case 4: Alternating positive and negative
        edge_cases.emplace_back("6\n1 -1 1 -1 1 -1", "1");
        
        return edge_cases;
    }
    
    // Generate random test cases
    static std::vector<std::pair<std::string, std::string>> generate_random_test_cases(
        size_t num_cases, size_t min_size, size_t max_size, 
        int min_value, int max_value) {
        
        std::vector<std::pair<std::string, std::string>> random_cases;
        std::random_device rd;
        std::mt19937 gen(rd());
        
        for (size_t i = 0; i < num_cases; ++i) {
            std::uniform_int_distribution<size_t> size_dist(min_size, max_size);
            std::uniform_int_distribution<int> value_dist(min_value, max_value);
            
            size_t size = size_dist(gen);
            std::vector<int> array;
            
            for (size_t j = 0; j < size; ++j) {
                array.push_back(value_dist(gen));
            }
            
            std::string input = std::to_string(size) + "\n";
            for (int val : array) {
                input += std::to_string(val) + " ";
            }
            
            // Calculate expected output (this would depend on the specific problem)
            std::string output = calculate_expected_output(array);
            
            random_cases.emplace_back(input, output);
        }
        
        return random_cases;
    }
    
private:
    static std::string calculate_expected_output(const std::vector<int>& array) {
        // This is a placeholder - actual implementation would depend on the problem
        if (array.empty()) return "0";
        
        int max_sum = array[0];
        int current_sum = array[0];
        
        for (size_t i = 1; i < array.size(); ++i) {
            current_sum = std::max(array[i], current_sum + array[i]);
            max_sum = std::max(max_sum, current_sum);
        }
        
        return std::to_string(max_sum);
    }
};
```

## 🔍 Problem Validation

### Solution Validator
```cpp
// Validate that problems have efficient solutions
class ProblemValidator {
public:
    struct ValidationResult {
        bool is_valid;
        std::vector<std::string> issues;
        std::vector<std::string> suggestions;
    };
    
    // Validate problem constraints
    static ValidationResult validate_constraints(const ProblemTemplate& problem) {
        ValidationResult result;
        result.is_valid = true;
        
        // Check if constraints are reasonable
        if (problem.constraints.empty()) {
            result.issues.push_back("No constraints specified");
            result.is_valid = false;
        }
        
        // Check if time complexity is achievable
        if (!validate_time_complexity(problem)) {
            result.issues.push_back("Time complexity constraints may be too strict");
            result.suggestions.push_back("Consider relaxing time limits or adjusting problem size");
        }
        
        // Check if memory constraints are reasonable
        if (!validate_memory_constraints(problem)) {
            result.issues.push_back("Memory constraints may be too strict");
            result.suggestions.push_back("Consider increasing memory limits");
        }
        
        return result;
    }
    
    // Validate test cases
    static ValidationResult validate_test_cases(const ProblemTemplate& problem,
                                              const std::vector<std::pair<std::string, std::string>>& test_cases) {
        ValidationResult result;
        result.is_valid = true;
        
        if (test_cases.empty()) {
            result.issues.push_back("No test cases provided");
            result.is_valid = false;
        }
        
        // Check test case coverage
        if (!check_test_case_coverage(problem, test_cases)) {
            result.issues.push_back("Test cases may not cover all scenarios");
            result.suggestions.push_back("Add edge cases and boundary conditions");
        }
        
        // Validate test case format
        for (const auto& test_case : test_cases) {
            if (!validate_test_case_format(problem, test_case)) {
                result.issues.push_back("Test case format is invalid");
                result.is_valid = false;
            }
        }
        
        return result;
    }
    
    // Validate problem statement clarity
    static ValidationResult validate_problem_statement(const ProblemTemplate& problem) {
        ValidationResult result;
        result.is_valid = true;
        
        if (problem.description.empty()) {
            result.issues.push_back("Problem description is missing");
            result.is_valid = false;
        }
        
        if (problem.input_format.empty()) {
            result.issues.push_back("Input format is missing");
            result.is_valid = false;
        }
        
        if (problem.output_format.empty()) {
            result.issues.push_back("Output format is missing");
            result.is_valid = false;
        }
        
        if (problem.examples.empty()) {
            result.issues.push_back("No examples provided");
            result.suggestions.push_back("Add examples to clarify the problem");
        }
        
        return result;
    }
    
private:
    static bool validate_time_complexity(const ProblemTemplate& problem) {
        // Simplified validation - in practice, this would be more sophisticated
        return true;
    }
    
    static bool validate_memory_constraints(const ProblemTemplate& problem) {
        // Simplified validation - in practice, this would be more sophisticated
        return true;
    }
    
    static bool check_test_case_coverage(const ProblemTemplate& problem,
                                       const std::vector<std::pair<std::string, std::string>>& test_cases) {
        // Check if test cases cover various scenarios
        bool has_small_input = false;
        bool has_large_input = false;
        bool has_edge_cases = false;
        
        for (const auto& test_case : test_cases) {
            size_t size = estimate_input_size(test_case.first);
            if (size <= 10) has_small_input = true;
            if (size >= 1000) has_large_input = true;
            if (is_edge_case(test_case)) has_edge_cases = true;
        }
        
        return has_small_input && has_large_input && has_edge_cases;
    }
    
    static bool validate_test_case_format(const ProblemTemplate& problem,
                                        const std::pair<std::string, std::string>& test_case) {
        // Validate that test case follows the specified format
        // This is a simplified implementation
        return !test_case.first.empty() && !test_case.second.empty();
    }
    
    static size_t estimate_input_size(const std::string& input) {
        // Estimate the size of input data
        // This is a simplified implementation
        return input.length();
    }
    
    static bool is_edge_case(const std::pair<std::string, std::string>& test_case) {
        // Determine if this is an edge case
        // This is a simplified implementation
        return test_case.first.find("0") != std::string::npos ||
               test_case.first.find("-") != std::string::npos;
    }
};
```

## 🎨 Creative Problem Design

### Problem Combination Generator
```cpp
// Combine multiple concepts into single problems
class ProblemCombinationGenerator {
public:
    // Combine array and graph concepts
    static ProblemTemplate create_array_graph_problem() {
        ProblemTemplate problem;
        problem.title = "Array to Graph Conversion";
        problem.description = "Convert an array into a graph and solve a graph problem on it.";
        problem.difficulty = ProblemTemplate::HARD;
        problem.category = ProblemTemplate::GRAPHS;
        
        problem.solution_profile.key_algorithms = {"Graph Construction", "BFS/DFS", "Array Processing"};
        problem.solution_profile.key_data_structures = {"Graph", "Array", "Queue/Stack"};
        
        return problem;
    }
    
    // Combine dynamic programming and geometry
    static ProblemTemplate create_dp_geometry_problem() {
        ProblemTemplate problem;
        problem.title = "Geometric Dynamic Programming";
        problem.description = "Solve a geometric problem using dynamic programming techniques.";
        problem.difficulty = ProblemTemplate::EXPERT;
        problem.category = ProblemTemplate::GEOMETRY;
        
        problem.solution_profile.key_algorithms = {"Dynamic Programming", "Geometric Algorithms"};
        problem.solution_profile.key_data_structures = {"DP Table", "Geometric Objects"};
        
        return problem;
    }
    
    // Combine string algorithms with mathematical concepts
    static ProblemTemplate create_string_math_problem() {
        ProblemTemplate problem;
        problem.title = "String Mathematical Properties";
        problem.description = "Analyze mathematical properties of strings and solve related problems.";
        problem.difficulty = ProblemTemplate::HARD;
        problem.category = ProblemTemplate::STRINGS;
        
        problem.solution_profile.key_algorithms = {"String Matching", "Mathematical Analysis"};
        problem.solution_profile.key_data_structures = {"String", "Mathematical Structures"};
        
        return problem;
    }
};
```

### Interactive Problem Generator
```cpp
// Generate interactive problems
class InteractiveProblemGenerator {
public:
    // Generate problems with multiple queries
    static ProblemTemplate create_query_based_problem() {
        ProblemTemplate problem;
        problem.title = "Dynamic Array Queries";
        problem.description = "Process multiple queries on a dynamic array with updates and queries.";
        problem.difficulty = ProblemTemplate::MEDIUM;
        problem.category = ProblemTemplate::ARRAYS;
        
        problem.solution_profile.key_algorithms = {"Query Processing", "Array Updates"};
        problem.solution_profile.key_data_structures = {"Array", "Query Structure"};
        
        return problem;
    }
    
    // Generate problems with user interaction
    static ProblemTemplate create_user_interaction_problem() {
        ProblemTemplate problem;
        problem.title = "Interactive Game Strategy";
        problem.description = "Implement a strategy for an interactive game with optimal moves.";
        problem.difficulty = ProblemTemplate::HARD;
        problem.category = ProblemTemplate::OTHER;
        
        problem.solution_profile.key_algorithms = {"Game Theory", "Strategy Optimization"};
        problem.solution_profile.key_data_structures = {"Game State", "Move Tree"};
        
        return problem;
    }
};
```

## 📚 Best Practices

### 1. Problem Design
- **Start with a clear concept** and build around it
- **Ensure educational value** for learners
- **Test with multiple solution approaches**
- **Validate constraints** are reasonable

### 2. Test Case Design
- **Cover edge cases** and boundary conditions
- **Include both small and large inputs**
- **Test various scenarios** and corner cases
- **Validate expected outputs** are correct

### 3. Problem Validation
- **Check solution efficiency** is achievable
- **Verify problem clarity** and understandability
- **Test with target audience** if possible
- **Iterate and improve** based on feedback

### 4. Documentation
- **Write clear problem statements** with examples
- **Document constraints** and requirements
- **Provide solution hints** when appropriate
- **Include learning objectives** and concepts

## 📖 Resources

### Books
- "Competitive Programming" by Steven Halim
- "Programming Challenges" by Steven Skiena
- "Problem Solving with Algorithms and Data Structures" by Miller and Ranum

### Online Resources
- [Problem Creation Guidelines](https://codeforces.com/blog/entry/18431)
- [Competitive Programming Problems](https://atcoder.jp/)
- [Problem Design Patterns](https://cp-algorithms.com/)

## 🚀 Practice Problems

### Basic Creation Exercises
1. **Simple Problem**: Create a basic array problem
2. **Constraint Design**: Design constraints for different difficulty levels
3. **Test Case Generation**: Generate comprehensive test cases

### Intermediate Creation Exercises
1. **Problem Variation**: Create variations of classic problems
2. **Multi-Concept Problem**: Combine multiple algorithmic concepts
3. **Edge Case Design**: Design problems that test edge case handling

### Advanced Creation Exercises
1. **Novel Problem**: Design a completely original problem
2. **Competitive Problem**: Create a problem suitable for competitions
3. **Educational Problem**: Design a problem that teaches specific concepts

---

*Problem creation is an art that combines technical knowledge with educational insight. Master this skill to contribute to the programming community and help others learn. Remember: good problems challenge the mind while being fair and educational.*
