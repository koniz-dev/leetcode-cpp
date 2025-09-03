# 🎨 Algorithm Design

## 📚 Overview

Algorithm design is the art and science of creating efficient solutions to computational problems. This guide covers systematic approaches to designing algorithms, from problem analysis to implementation and optimization.

## 🎯 Algorithm Design Process

### 1. Problem Understanding
- **Analyze the problem statement** thoroughly
- **Identify input/output requirements**
- **Understand constraints and edge cases**
- **Clarify any ambiguities**

### 2. Solution Strategy
- **Choose appropriate algorithmic paradigms**
- **Design data structures** for the solution
- **Plan the overall approach**
- **Consider multiple solution strategies**

### 3. Implementation
- **Write clear, readable code**
- **Handle edge cases properly**
- **Ensure correctness**
- **Optimize for performance**

### 4. Analysis and Optimization
- **Analyze time and space complexity**
- **Identify bottlenecks**
- **Apply optimization techniques**
- **Validate improvements**

## 🔧 Problem Analysis Framework

### Problem Classification
```cpp
// Example: Problem analysis template
struct ProblemAnalysis {
    std::string problem_name;
    std::string problem_description;
    
    // Input characteristics
    struct Input {
        size_t max_size;
        std::string data_type;
        std::vector<std::string> constraints;
        std::vector<std::string> edge_cases;
    } input;
    
    // Output requirements
    struct Output {
        std::string expected_format;
        std::vector<std::string> requirements;
        bool order_matters;
    } output;
    
    // Complexity requirements
    struct Complexity {
        std::string time_complexity;
        std::string space_complexity;
        bool online_processing;
    } complexity;
    
    // Algorithmic approaches
    std::vector<std::string> possible_approaches;
    std::string recommended_approach;
    std::string reasoning;
};

// Example usage
ProblemAnalysis analyze_problem(const std::string& problem) {
    ProblemAnalysis analysis;
    
    // Fill in problem details
    analysis.problem_name = "Two Sum";
    analysis.problem_description = "Find two numbers that add up to target";
    
    analysis.input.max_size = 10000;
    analysis.input.data_type = "array of integers";
    analysis.input.constraints = {"exactly one solution exists", "cannot use same element twice"};
    analysis.input.edge_cases = {"empty array", "single element", "all same elements"};
    
    analysis.output.expected_format = "pair of indices";
    analysis.output.requirements = {"return first valid pair", "0-based indexing"};
    analysis.output.order_matters = false;
    
    analysis.complexity.time_complexity = "O(n)";
    analysis.complexity.space_complexity = "O(n)";
    analysis.complexity.online_processing = false;
    
    analysis.possible_approaches = {"brute force", "hash table", "two pointers"};
    analysis.recommended_approach = "hash table";
    analysis.reasoning = "optimal time complexity with reasonable space usage";
    
    return analysis;
}
```

### Constraint Analysis
```cpp
// Constraint analysis helper
class ConstraintAnalyzer {
public:
    struct Constraints {
        size_t max_n;
        size_t max_value;
        bool allow_negative;
        bool allow_duplicates;
        bool require_stable_sort;
        std::string memory_limit;
        std::string time_limit;
    };
    
    static Constraints analyze_constraints(const std::string& problem_statement) {
        Constraints constraints;
        
        // Parse problem statement for constraints
        // This is a simplified example
        if (problem_statement.find("1 ≤ n ≤ 10^5") != std::string::npos) {
            constraints.max_n = 100000;
        }
        
        if (problem_statement.find("1 ≤ ai ≤ 10^9") != std::string::npos) {
            constraints.max_value = 1000000000;
        }
        
        if (problem_statement.find("negative") != std::string::npos) {
            constraints.allow_negative = true;
        }
        
        return constraints;
    }
    
    static bool is_constraint_satisfied(const Constraints& constraints, 
                                      const std::vector<int>& data) {
        if (data.size() > constraints.max_n) return false;
        
        for (int value : data) {
            if (value > static_cast<int>(constraints.max_value)) return false;
            if (!constraints.allow_negative && value < 0) return false;
        }
        
        return true;
    }
};
```

## 🚀 Algorithmic Paradigms

### Divide and Conquer
```cpp
// Generic divide and conquer framework
template<typename T, typename Result>
class DivideAndConquer {
public:
    using problem_type = T;
    using result_type = Result;
    
    virtual bool is_base_case(const problem_type& problem) const = 0;
    virtual result_type solve_base_case(const problem_type& problem) const = 0;
    virtual std::vector<problem_type> divide(const problem_type& problem) const = 0;
    virtual result_type combine(const std::vector<result_type>& sub_results) const = 0;
    
    result_type solve(const problem_type& problem) const {
        if (is_base_case(problem)) {
            return solve_base_case(problem);
        }
        
        auto sub_problems = divide(problem);
        std::vector<result_type> sub_results;
        
        for (const auto& sub_problem : sub_problems) {
            sub_results.push_back(solve(sub_problem));
        }
        
        return combine(sub_results);
    }
};

// Example: Merge Sort using divide and conquer
class MergeSort : public DivideAndConquer<std::vector<int>, std::vector<int>> {
public:
    bool is_base_case(const std::vector<int>& problem) const override {
        return problem.size() <= 1;
    }
    
    std::vector<int> solve_base_case(const std::vector<int>& problem) const override {
        return problem;
    }
    
    std::vector<std::vector<int>> divide(const std::vector<int>& problem) const override {
        size_t mid = problem.size() / 2;
        std::vector<int> left(problem.begin(), problem.begin() + mid);
        std::vector<int> right(problem.begin() + mid, problem.end());
        return {left, right};
    }
    
    std::vector<int> combine(const std::vector<std::vector<int>>& sub_results) const override {
        return merge(sub_results[0], sub_results[1]);
    }
    
private:
    std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) const {
        std::vector<int> result;
        size_t i = 0, j = 0;
        
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                result.push_back(left[i++]);
            } else {
                result.push_back(right[j++]);
            }
        }
        
        while (i < left.size()) result.push_back(left[i++]);
        while (j < right.size()) result.push_back(right[j++]);
        
        return result;
    }
};
```

### Dynamic Programming
```cpp
// Generic dynamic programming framework
template<typename State, typename Result>
class DynamicProgramming {
public:
    using state_type = State;
    using result_type = Result;
    
    virtual bool is_base_case(const state_type& state) const = 0;
    virtual result_type solve_base_case(const state_type& state) const = 0;
    virtual std::vector<state_type> get_transitions(const state_type& state) const = 0;
    virtual result_type combine_results(const state_type& state, 
                                     const std::vector<result_type>& sub_results) const = 0;
    
    result_type solve(const state_type& state) {
        // Check cache first
        auto it = cache.find(state);
        if (it != cache.end()) {
            return it->second;
        }
        
        result_type result;
        if (is_base_case(state)) {
            result = solve_base_case(state);
        } else {
            auto transitions = get_transitions(state);
            std::vector<result_type> sub_results;
            
            for (const auto& transition : transitions) {
                sub_results.push_back(solve(transition));
            }
            
            result = combine_results(state, sub_results);
        }
        
        // Cache the result
        cache[state] = result;
        return result;
    }
    
private:
    std::unordered_map<state_type, result_type> cache;
};

// Example: Fibonacci using dynamic programming
class FibonacciDP : public DynamicProgramming<int, long long> {
public:
    bool is_base_case(int state) const override {
        return state <= 1;
    }
    
    long long solve_base_case(int state) const override {
        return state;
    }
    
    std::vector<int> get_transitions(int state) const override {
        return {state - 1, state - 2};
    }
    
    long long combine_results(int state, const std::vector<long long>& sub_results) const override {
        return sub_results[0] + sub_results[1];
    }
};
```

### Greedy Algorithms
```cpp
// Generic greedy algorithm framework
template<typename Problem, typename Solution>
class GreedyAlgorithm {
public:
    using problem_type = Problem;
    using solution_type = Solution;
    
    virtual bool is_solved(const problem_type& problem) const = 0;
    virtual std::vector<typename problem_type::element_type> get_candidates(
        const problem_type& problem) const = 0;
    virtual typename problem_type::element_type select_best_candidate(
        const std::vector<typename problem_type::element_type>& candidates) const = 0;
    virtual void apply_choice(problem_type& problem, 
                            const typename problem_type::element_type& choice) const = 0;
    virtual void update_solution(solution_type& solution, 
                               const typename problem_type::element_type& choice) const = 0;
    
    solution_type solve(problem_type problem) const {
        solution_type solution;
        
        while (!is_solved(problem)) {
            auto candidates = get_candidates(problem);
            if (candidates.empty()) break;
            
            auto choice = select_best_candidate(candidates);
            apply_choice(problem, choice);
            update_solution(solution, choice);
        }
        
        return solution;
    }
};

// Example: Activity Selection using greedy approach
struct Activity {
    int start, finish;
    Activity(int s, int f) : start(s), finish(f) {}
    
    bool operator<(const Activity& other) const {
        return finish < other.finish;
    }
};

class ActivitySelection : public GreedyAlgorithm<std::vector<Activity>, std::vector<Activity>> {
public:
    bool is_solved(const std::vector<Activity>& problem) const override {
        return problem.empty();
    }
    
    std::vector<Activity> get_candidates(const std::vector<Activity>& problem) const override {
        return problem;
    }
    
    Activity select_best_candidate(const std::vector<Activity>& candidates) const override {
        // Select activity with earliest finish time
        return *std::min_element(candidates.begin(), candidates.end());
    }
    
    void apply_choice(std::vector<Activity>& problem, const Activity& choice) const override {
        // Remove selected activity and incompatible activities
        problem.erase(std::remove_if(problem.begin(), problem.end(),
            [&choice](const Activity& a) {
                return a.start < choice.finish;
            }), problem.end());
    }
    
    void update_solution(std::vector<Activity>& solution, const Activity& choice) const override {
        solution.push_back(choice);
    }
};
```

## 🔍 Advanced Design Techniques

### State Space Search
```cpp
// Generic state space search framework
template<typename State>
class StateSpaceSearch {
public:
    using state_type = State;
    
    virtual bool is_goal_state(const state_type& state) const = 0;
    virtual std::vector<state_type> get_successors(const state_type& state) const = 0;
    virtual double heuristic(const state_type& state) const = 0;
    virtual double cost(const state_type& from, const state_type& to) const = 0;
    
    // A* search implementation
    std::vector<state_type> astar_search(const state_type& start) const {
        struct Node {
            state_type state;
            double g_cost;  // Cost from start
            double f_cost;  // g_cost + heuristic
            std::vector<state_type> path;
            
            Node(const state_type& s, double g, double f, const std::vector<state_type>& p)
                : state(s), g_cost(g), f_cost(f), path(p) {}
            
            bool operator>(const Node& other) const {
                return f_cost > other.f_cost;
            }
        };
        
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_set;
        std::unordered_set<state_type> closed_set;
        
        open_set.emplace(start, 0, heuristic(start), std::vector<state_type>{start});
        
        while (!open_set.empty()) {
            Node current = open_set.top();
            open_set.pop();
            
            if (is_goal_state(current.state)) {
                return current.path;
            }
            
            if (closed_set.find(current.state) != closed_set.end()) {
                continue;
            }
            
            closed_set.insert(current.state);
            
            for (const auto& successor : get_successors(current.state)) {
                if (closed_set.find(successor) != closed_set.end()) {
                    continue;
                }
                
                double new_g_cost = current.g_cost + cost(current.state, successor);
                double new_f_cost = new_g_cost + heuristic(successor);
                
                auto new_path = current.path;
                new_path.push_back(successor);
                
                open_set.emplace(successor, new_g_cost, new_f_cost, new_path);
            }
        }
        
        return {};  // No solution found
    }
};

// Example: 8-puzzle using A* search
struct PuzzleState {
    std::vector<int> board;
    int empty_pos;
    
    PuzzleState(const std::vector<int>& b) : board(b) {
        for (size_t i = 0; i < board.size(); ++i) {
            if (board[i] == 0) {
                empty_pos = i;
                break;
            }
        }
    }
    
    bool operator==(const PuzzleState& other) const {
        return board == other.board;
    }
    
    std::vector<PuzzleState> get_neighbors() const {
        std::vector<PuzzleState> neighbors;
        int row = empty_pos / 3;
        int col = empty_pos % 3;
        
        // Try moving empty space in all directions
        std::vector<std::pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (const auto& [dr, dc] : moves) {
            int new_row = row + dr;
            int new_col = col + dc;
            
            if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
                int new_pos = new_row * 3 + new_col;
                auto new_board = board;
                std::swap(new_board[empty_pos], new_board[new_pos]);
                neighbors.emplace_back(new_board);
            }
        }
        
        return neighbors;
    }
};

namespace std {
    template<>
    struct hash<PuzzleState> {
        size_t operator()(const PuzzleState& state) const {
            size_t hash = 0;
            for (int value : state.board) {
                hash = hash * 31 + value;
            }
            return hash;
        }
    };
}

class PuzzleSolver : public StateSpaceSearch<PuzzleState> {
public:
    bool is_goal_state(const PuzzleState& state) const override {
        std::vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        return state.board == goal;
    }
    
    std::vector<PuzzleState> get_successors(const PuzzleState& state) const override {
        return state.get_neighbors();
    }
    
    double heuristic(const PuzzleState& state) const override {
        // Manhattan distance heuristic
        double total_distance = 0;
        for (size_t i = 0; i < state.board.size(); ++i) {
            if (state.board[i] != 0) {
                int goal_pos = state.board[i] - 1;
                int current_row = i / 3;
                int current_col = i % 3;
                int goal_row = goal_pos / 3;
                int goal_col = goal_pos % 3;
                
                total_distance += std::abs(current_row - goal_row) + 
                                std::abs(current_col - goal_col);
            }
        }
        return total_distance;
    }
    
    double cost(const PuzzleState& from, const PuzzleState& to) const override {
        return 1;  // Each move costs 1
    }
};
```

### Approximation Algorithms
```cpp
// Generic approximation algorithm framework
template<typename Problem, typename Solution>
class ApproximationAlgorithm {
public:
    using problem_type = Problem;
    using solution_type = Solution;
    
    virtual solution_type solve_exact(const problem_type& problem) const = 0;
    virtual solution_type solve_approximate(const problem_type& problem) const = 0;
    virtual double get_approximation_ratio() const = 0;
    virtual double evaluate_solution(const problem_type& problem, 
                                   const solution_type& solution) const = 0;
    
    // Compare exact vs approximate solutions
    struct Comparison {
        solution_type exact_solution;
        solution_type approximate_solution;
        double exact_value;
        double approximate_value;
        double ratio;
        
        Comparison(const solution_type& exact, const solution_type& approx,
                  double exact_val, double approx_val)
            : exact_solution(exact), approximate_solution(approx),
              exact_value(exact_val), approximate_value(approx_val) {
            ratio = approximate_value / exact_value;
        }
    };
    
    Comparison compare_solutions(const problem_type& problem) const {
        auto exact_sol = solve_exact(problem);
        auto approx_sol = solve_approximate(problem);
        
        double exact_val = evaluate_solution(problem, exact_sol);
        double approx_val = evaluate_solution(problem, approx_sol);
        
        return Comparison(exact_sol, approx_sol, exact_val, approx_val);
    }
};

// Example: Vertex Cover approximation
struct Graph {
    std::vector<std::vector<int>> adjacency_list;
    
    Graph(size_t vertices) : adjacency_list(vertices) {}
    
    void add_edge(int u, int v) {
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }
    
    std::vector<std::pair<int, int>> get_edges() const {
        std::vector<std::pair<int, int>> edges;
        for (size_t u = 0; u < adjacency_list.size(); ++u) {
            for (int v : adjacency_list[u]) {
                if (u < static_cast<size_t>(v)) {
                    edges.emplace_back(u, v);
                }
            }
        }
        return edges;
    }
};

class VertexCoverApproximation : public ApproximationAlgorithm<Graph, std::vector<int>> {
public:
    std::vector<int> solve_exact(const Graph& problem) const override {
        // Exact solution using exponential algorithm (simplified)
        // In practice, this would use a more sophisticated approach
        return {};
    }
    
    std::vector<int> solve_approximate(const Graph& problem) const override {
        std::vector<int> cover;
        auto edges = problem.get_edges();
        std::vector<bool> covered(edges.size(), false);
        
        // 2-approximation algorithm
        for (size_t i = 0; i < edges.size(); ++i) {
            if (!covered[i]) {
                int u = edges[i].first;
                int v = edges[i].second;
                
                cover.push_back(u);
                cover.push_back(v);
                
                // Mark all edges incident to u and v as covered
                for (size_t j = 0; j < edges.size(); ++j) {
                    if (edges[j].first == u || edges[j].first == v ||
                        edges[j].second == u || edges[j].second == v) {
                        covered[j] = true;
                    }
                }
            }
        }
        
        return cover;
    }
    
    double get_approximation_ratio() const override {
        return 2.0;  // 2-approximation
    }
    
    double evaluate_solution(const Graph& problem, const std::vector<int>& solution) const override {
        return static_cast<double>(solution.size());
    }
};
```

## 🔧 Optimization Techniques

### Algorithmic Optimization
```cpp
// Optimization strategies
class AlgorithmOptimizer {
public:
    // Loop optimization
    template<typename Container, typename Func>
    static void optimize_loop(Container& container, Func func) {
        // Cache size to avoid repeated calls
        size_t size = container.size();
        
        // Use references to avoid copying
        for (size_t i = 0; i < size; ++i) {
            auto& item = container[i];
            func(item);
        }
    }
    
    // Memory access optimization
    template<typename T>
    static void optimize_memory_access(std::vector<T>& data) {
        // Sort data for better cache locality
        std::sort(data.begin(), data.end());
        
        // Use structure of arrays if beneficial
        // This is a simplified example
    }
    
    // Branch prediction optimization
    template<typename Container, typename Pred>
    static void optimize_branch_prediction(Container& container, Pred pred) {
        // Separate elements based on predicate
        std::vector<typename Container::value_type> true_elements, false_elements;
        
        for (const auto& item : container) {
            if (pred(item)) {
                true_elements.push_back(item);
            } else {
                false_elements.push_back(item);
            }
        }
        
        // Process each group separately
        for (const auto& item : true_elements) {
            // Process true items
        }
        
        for (const auto& item : false_elements) {
            // Process false items
        }
    }
};
```

### Data Structure Optimization
```cpp
// Optimized data structure selection
class DataStructureOptimizer {
public:
    // Choose optimal container based on usage patterns
    template<typename T>
    static auto select_optimal_container() {
        // This is a simplified example - in practice, you'd analyze usage patterns
        if constexpr (std::is_same_v<T, int>) {
            return std::vector<T>();  // Vector for integers
        } else if constexpr (std::is_same_v<T, std::string>) {
            return std::unordered_set<T>();  // Hash set for strings
        } else {
            return std::set<T>();  // Ordered set for other types
        }
    }
    
    // Optimize for specific access patterns
    template<typename T>
    static auto optimize_for_access_pattern(const std::string& pattern) {
        if (pattern == "random_access") {
            return std::vector<T>();
        } else if (pattern == "frequent_insertion") {
            return std::list<T>();
        } else if (pattern == "frequent_lookup") {
            return std::unordered_map<int, T>();
        } else {
            return std::vector<T>();  // Default
        }
    }
};
```

## 📚 Best Practices

### 1. Problem Analysis
- **Understand the problem completely** before starting
- **Identify key constraints** and requirements
- **Consider edge cases** and boundary conditions
- **Break complex problems** into simpler subproblems

### 2. Solution Design
- **Choose appropriate paradigms** for the problem
- **Design clear interfaces** and data structures
- **Plan the implementation** step by step
- **Consider multiple approaches** and trade-offs

### 3. Implementation
- **Write clean, readable code** from the start
- **Handle errors and edge cases** properly
- **Use appropriate data structures** for the problem
- **Optimize incrementally** after correctness

### 4. Testing and Validation
- **Test with small inputs** first
- **Verify correctness** with known test cases
- **Stress test** with large inputs
- **Profile performance** to identify bottlenecks

## 📖 Resources

### Books
- "Introduction to Algorithms" by CLRS
- "Algorithm Design" by Kleinberg and Tardos
- "The Algorithm Design Manual" by Steven Skiena
- "Competitive Programming" by Steven Halim

### Online Resources
- [Algorithm Design Patterns](https://en.wikipedia.org/wiki/Algorithm_design)
- [Competitive Programming](https://cp-algorithms.com/)
- [Algorithm Visualization](https://visualgo.net/)

## 🚀 Practice Problems

### Basic Design Exercises
1. **Problem Analysis**: Analyze and classify problems
2. **Paradigm Selection**: Choose appropriate algorithmic paradigms
3. **Simple Implementation**: Implement basic algorithms

### Intermediate Design Exercises
1. **Complex Problem Solving**: Solve multi-step problems
2. **Optimization**: Optimize existing algorithms
3. **Multiple Approaches**: Implement different solutions to same problem

### Advanced Design Exercises
1. **Novel Algorithm Design**: Design custom algorithms
2. **Performance Optimization**: Optimize for specific constraints
3. **Research Implementation**: Implement algorithms from research papers

---

*Algorithm design is both an art and a science. Master the fundamentals, practice systematically, and always strive for elegant, efficient solutions. Remember: the best algorithm is the one that solves your specific problem effectively.*
