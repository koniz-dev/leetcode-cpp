# 🚀 C++ STL Containers: Complete Guide

## 📚 Overview

The Standard Template Library (STL) provides a collection of powerful, efficient, and reusable container classes. Understanding these containers is crucial for writing efficient C++ code and solving complex problems.

## 🎯 Key Concepts

### What are STL Containers?
- **Generic data structures** that can hold objects of any type
- **Type-safe** with compile-time type checking
- **Efficient** implementations optimized for common use cases
- **Standardized** interface across all containers

### Container Categories
- **Sequence containers**: Array, vector, deque, list, forward_list
- **Associative containers**: set, multiset, map, multimap
- **Unordered containers**: unordered_set, unordered_multiset, unordered_map, unordered_multimap
- **Container adapters**: stack, queue, priority_queue

## 📊 Sequence Containers

### Vector
```cpp
#include <vector>
#include <iostream>
using namespace std;

int main() {
    // Declaration and initialization
    vector<int> numbers;                    // Empty vector
    vector<int> scores(5);                  // 5 elements with default value 0
    vector<int> values(3, 42);             // 3 elements with value 42
    vector<int> initial = {1, 2, 3, 4, 5}; // Initializer list
    
    // Adding elements
    numbers.push_back(10);                  // Add to end
    numbers.push_back(20);
    numbers.push_back(30);
    
    // Insert at specific position
    numbers.insert(numbers.begin(), 5);     // Insert at beginning
    numbers.insert(numbers.begin() + 2, 15); // Insert at position 2
    
    // Accessing elements
    cout << "First element: " << numbers.front() << endl;
    cout << "Last element: " << numbers.back() << endl;
    cout << "Element at index 1: " << numbers[1] << endl;
    cout << "Element at index 2: " << numbers.at(2) << endl;
    
    // Size and capacity
    cout << "Size: " << numbers.size() << endl;
    cout << "Capacity: " << numbers.capacity() << endl;
    cout << "Empty: " << numbers.empty() << endl;
    
    // Iterating
    cout << "Elements: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Iterator-based iteration
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Removing elements
    numbers.pop_back();                     // Remove from end
    numbers.erase(numbers.begin());         // Remove first element
    numbers.erase(numbers.begin() + 1, numbers.begin() + 3); // Remove range
    
    // Resizing
    numbers.resize(8, 100);                // Resize to 8, fill new with 100
    
    // Clearing
    numbers.clear();                        // Remove all elements
    
    return 0;
}
```

### Deque (Double-ended Queue)
```cpp
#include <deque>

int main() {
    deque<int> dq = {1, 2, 3, 4, 5};
    
    // Add elements at both ends
    dq.push_front(0);                      // Add to front
    dq.push_back(6);                       // Add to back
    
    // Remove elements from both ends
    dq.pop_front();                        // Remove from front
    dq.pop_back();                         // Remove from back
    
    // Access front and back
    cout << "Front: " << dq.front() << endl;
    cout << "Back: " << dq.back() << endl;
    
    // Insert at specific position
    dq.insert(dq.begin() + 2, 25);        // Insert at position 2
    
    // Display all elements
    for (const auto& item : dq) {
        cout << item << " ";
    }
    cout << endl;
    
    return 0;
}
```

### List (Doubly-linked List)
```cpp
#include <list>

int main() {
    list<int> lst = {1, 2, 3, 4, 5};
    
    // Add elements
    lst.push_front(0);                     // Add to front
    lst.push_back(6);                      // Add to back
    
    // Insert at specific position
    auto it = lst.begin();
    advance(it, 2);                        // Move iterator to position 2
    lst.insert(it, 25);                    // Insert at position 2
    
    // Remove elements
    lst.remove(3);                         // Remove all occurrences of 3
    lst.remove_if([](int n) { return n % 2 == 0; }); // Remove even numbers
    
    // Sort and reverse
    lst.sort();                            // Sort in ascending order
    lst.reverse();                          // Reverse the list
    
    // Merge lists
    list<int> lst2 = {7, 8, 9};
    lst.merge(lst2);                       // Merge lst2 into lst
    
    // Display
    for (const auto& item : lst) {
        cout << item << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Forward List (Singly-linked List)
```cpp
#include <forward_list>

int main() {
    forward_list<int> flst = {1, 2, 3, 4, 5};
    
    // Add elements (only at front)
    flst.push_front(0);
    
    // Insert after specific position
    auto it = flst.begin();
    advance(it, 2);
    flst.insert_after(it, 25);
    
    // Remove elements
    flst.remove(3);                        // Remove all occurrences of 3
    
    // Remove if condition is met
    flst.remove_if([](int n) { return n % 2 == 0; });
    
    // Sort
    flst.sort();
    
    // Display
    for (const auto& item : flst) {
        cout << item << " ";
    }
    cout << endl;
    
    return 0;
}
```

## 🔗 Associative Containers

### Set
```cpp
#include <set>

int main() {
    // Declaration
    set<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // Elements are automatically sorted and unique
    cout << "Set contents: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Insert elements
    numbers.insert(7);
    numbers.insert(0);
    
    // Check if element exists
    if (numbers.find(5) != numbers.end()) {
        cout << "5 found in set" << endl;
    }
    
    // Count occurrences (0 or 1 for set)
    cout << "Count of 5: " << numbers.count(5) << endl;
    
    // Remove elements
    numbers.erase(1);                      // Remove element 1
    
    // Lower and upper bounds
    auto lower = numbers.lower_bound(4);   // First element >= 4
    auto upper = numbers.upper_bound(6);   // First element > 6
    
    cout << "Elements >= 4 and < 6: ";
    for (auto it = lower; it != upper; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Set operations
    set<int> set1 = {1, 2, 3, 4, 5};
    set<int> set2 = {4, 5, 6, 7, 8};
    
    set<int> intersection, union_set, difference;
    
    // Intersection
    set_intersection(set1.begin(), set1.end(), 
                     set2.begin(), set2.end(),
                     inserter(intersection, intersection.begin()));
    
    // Union
    set_union(set1.begin(), set1.end(),
              set2.begin(), set2.end(),
              inserter(union_set, union_set.begin()));
    
    // Difference
    set_difference(set1.begin(), set1.end(),
                   set2.begin(), set2.end(),
                   inserter(difference, difference.begin()));
    
    return 0;
}
```

### Multiset
```cpp
#include <set>

int main() {
    multiset<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 1};
    
    // Elements are sorted but can have duplicates
    cout << "Multiset contents: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Count occurrences
    cout << "Count of 1: " << numbers.count(1) << endl;
    
    // Find all occurrences
    auto range = numbers.equal_range(1);
    cout << "All 1s: ";
    for (auto it = range.first; it != range.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Remove specific occurrence
    auto it = numbers.find(1);
    if (it != numbers.end()) {
        numbers.erase(it);                 // Remove first occurrence
    }
    
    return 0;
}
```

### Map
```cpp
#include <map>

int main() {
    // Declaration
    map<string, int> scores;
    
    // Insert elements
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    scores.insert({"David", 78});
    scores.insert(make_pair("Eve", 89));
    
    // Access elements
    cout << "Alice's score: " << scores["Alice"] << endl;
    
    // Safe access (doesn't create element if not exists)
    auto it = scores.find("Frank");
    if (it != scores.end()) {
        cout << "Frank's score: " << it->second << endl;
    } else {
        cout << "Frank not found" << endl;
    }
    
    // Check if key exists
    if (scores.count("Alice") > 0) {
        cout << "Alice exists in map" << endl;
    }
    
    // Iterate through map
    cout << "All scores:" << endl;
    for (const auto& [name, score] : scores) {
        cout << name << ": " << score << endl;
    }
    
    // Update values
    scores["Alice"] = 98;
    
    // Remove elements
    scores.erase("Bob");
    
    // Map operations
    map<string, int> scores1 = {{"A", 90}, {"B", 85}};
    map<string, int> scores2 = {{"B", 88}, {"C", 92}};
    
    // Merge maps
    scores1.insert(scores2.begin(), scores2.end());
    
    // Find bounds
    auto lower = scores1.lower_bound("B");
    auto upper = scores1.upper_bound("B");
    
    return 0;
}
```

### Multimap
```cpp
#include <map>

int main() {
    multimap<string, int> scores;
    
    // Insert multiple values for same key
    scores.insert({"Alice", 95});
    scores.insert({"Alice", 98});
    scores.insert({"Bob", 87});
    scores.insert({"Bob", 89});
    
    // Find all values for a key
    auto range = scores.equal_range("Alice");
    cout << "Alice's scores: ";
    for (auto it = range.first; it != range.second; ++it) {
        cout << it->second << " ";
    }
    cout << endl;
    
    // Count values for a key
    cout << "Number of scores for Alice: " << scores.count("Alice") << endl;
    
    return 0;
}
```

## 🌊 Unordered Containers

### Unordered Set
```cpp
#include <unordered_set>

int main() {
    unordered_set<string> names = {"Alice", "Bob", "Charlie"};
    
    // Insert elements
    names.insert("David");
    names.insert("Eve");
    
    // Check if element exists
    if (names.find("Alice") != names.end()) {
        cout << "Alice found" << endl;
    }
    
    // Count occurrences
    cout << "Count of Alice: " << names.count("Alice") << endl;
    
    // Remove elements
    names.erase("Bob");
    
    // Display
    for (const auto& name : names) {
        cout << name << " ";
    }
    cout << endl;
    
    // Hash function and bucket info
    cout << "Number of buckets: " << names.bucket_count() << endl;
    cout << "Load factor: " << names.load_factor() << endl;
    
    return 0;
}
```

### Unordered Map
```cpp
#include <unordered_map>

int main() {
    unordered_map<string, int> scores;
    
    // Insert elements
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    
    // Access elements
    cout << "Alice's score: " << scores["Alice"] << endl;
    
    // Safe access
    auto it = scores.find("David");
    if (it != scores.end()) {
        cout << "David's score: " << it->second << endl;
    }
    
    // Iterate
    for (const auto& [name, score] : scores) {
        cout << name << ": " << score << endl;
    }
    
    // Hash function info
    cout << "Hash for Alice: " << scores.hash_function()("Alice") << endl;
    
    return 0;
}
```

## 🎭 Container Adapters

### Stack
```cpp
#include <stack>

int main() {
    stack<int> st;
    
    // Push elements
    st.push(10);
    st.push(20);
    st.push(30);
    
    // Access top element
    cout << "Top element: " << st.top() << endl;
    
    // Remove top element
    st.pop();
    
    // Check size and empty
    cout << "Size: " << st.size() << endl;
    cout << "Empty: " << st.empty() << endl;
    
    // Display all elements (note: stack doesn't support iteration)
    cout << "Stack contents: ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
    
    return 0;
}
```

### Queue
```cpp
#include <queue>

int main() {
    queue<int> q;
    
    // Enqueue elements
    q.push(10);
    q.push(20);
    q.push(30);
    
    // Access front and back
    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;
    
    // Dequeue element
    q.pop();
    
    // Check size and empty
    cout << "Size: " << q.size() << endl;
    cout << "Empty: " << q.empty() << endl;
    
    // Display all elements
    cout << "Queue contents: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    
    return 0;
}
```

### Priority Queue
```cpp
#include <queue>

int main() {
    // Max heap (default)
    priority_queue<int> maxHeap;
    
    // Min heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    // Insert elements
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);
    maxHeap.push(50);
    maxHeap.push(40);
    
    // Access top element
    cout << "Max heap top: " << maxHeap.top() << endl;
    
    // Remove top element
    maxHeap.pop();
    
    // Display all elements
    cout << "Max heap contents: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;
    
    // Custom priority queue
    struct Person {
        string name;
        int age;
        
        bool operator<(const Person& other) const {
            return age < other.age;  // Max heap by age
        }
    };
    
    priority_queue<Person> personQueue;
    personQueue.push({"Alice", 25});
    personQueue.push({"Bob", 30});
    personQueue.push({"Charlie", 20});
    
    cout << "Person queue contents: ";
    while (!personQueue.empty()) {
        cout << personQueue.top().name << "(" << personQueue.top().age << ") ";
        personQueue.pop();
    }
    cout << endl;
    
    return 0;
}
```

## 🔧 Container Operations

### Common Operations
```cpp
#include <algorithm>
#include <vector>

int main() {
    vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // Sorting
    sort(numbers.begin(), numbers.end());           // Ascending
    sort(numbers.rbegin(), numbers.rend());        // Descending
    
    // Finding elements
    auto it = find(numbers.begin(), numbers.end(), 5);
    if (it != numbers.end()) {
        cout << "Found 5 at position: " << (it - numbers.begin()) << endl;
    }
    
    // Binary search (requires sorted container)
    bool found = binary_search(numbers.begin(), numbers.end(), 5);
    
    // Min and max elements
    auto minIt = min_element(numbers.begin(), numbers.end());
    auto maxIt = max_element(numbers.begin(), numbers.end());
    
    // Count elements
    int count = count(numbers.begin(), numbers.end(), 1);
    
    // Remove duplicates (requires sorted container)
    auto last = unique(numbers.begin(), numbers.end());
    numbers.erase(last, numbers.end());
    
    // Reverse
    reverse(numbers.begin(), numbers.end());
    
    // Rotate
    rotate(numbers.begin(), numbers.begin() + 2, numbers.end());
    
    // Fill
    fill(numbers.begin(), numbers.end(), 0);
    
    // Generate
    generate(numbers.begin(), numbers.end(), []() { return rand() % 100; });
    
    return 0;
}
```

### Container Algorithms
```cpp
#include <numeric>
#include <vector>

int main() {
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Accumulate (sum)
    int sum = accumulate(numbers.begin(), numbers.end(), 0);
    
    // Accumulate with custom operation
    int product = accumulate(numbers.begin(), numbers.end(), 1, multiplies<int>());
    
    // Inner product
    vector<int> weights = {2, 3, 1, 4, 2};
    int weightedSum = inner_product(numbers.begin(), numbers.end(), 
                                   weights.begin(), 0);
    
    // Partial sum
    vector<int> partialSums(numbers.size());
    partial_sum(numbers.begin(), numbers.end(), partialSums.begin());
    
    // Adjacent difference
    vector<int> differences(numbers.size());
    adjacent_difference(numbers.begin(), numbers.end(), differences.begin());
    
    return 0;
}
```

## 📝 Best Practices

### 1. Choose the Right Container
```cpp
// Use vector when:
// - Need random access
// - Don't know size in advance
// - Need to insert/delete at end only

// Use list when:
// - Need frequent insertions/deletions in middle
// - Don't need random access
// - Need bidirectional iteration

// Use set when:
// - Need sorted, unique elements
// - Need to check existence frequently
// - Need range operations

// Use unordered_set when:
// - Don't need sorted order
// - Need fast lookups
// - Elements have good hash functions

// Use map when:
// - Need key-value pairs
// - Need sorted keys
// - Need range operations

// Use unordered_map when:
// - Don't need sorted keys
// - Need fast lookups
// - Keys have good hash functions
```

### 2. Reserve Capacity
```cpp
// Good: Reserve capacity when you know size
vector<int> numbers;
numbers.reserve(1000);
for (int i = 0; i < 1000; i++) {
    numbers.push_back(i);
}

// Bad: Frequent reallocation
vector<int> numbers;
for (int i = 0; i < 1000; i++) {
    numbers.push_back(i);  // May cause multiple reallocations
}
```

### 3. Use Appropriate Iterators
```cpp
// Good: Use const iterators when not modifying
for (auto it = container.cbegin(); it != container.cend(); ++it) {
    cout << *it << endl;
}

// Good: Use reverse iterators when needed
for (auto it = container.rbegin(); it != container.rend(); ++it) {
    cout << *it << endl;
}
```

### 4. Handle Container State
```cpp
// Good: Check container state before operations
if (!container.empty()) {
    auto value = container.front();
    container.pop_front();
}

// Good: Use try-catch for operations that may throw
try {
    auto value = container.at(index);
} catch (const out_of_range& e) {
    cout << "Index out of range" << endl;
}
```

## 🎯 Practice Problems

### Problem 1: Find First Non-repeating Character
```cpp
char firstNonRepeating(const string& str) {
    unordered_map<char, int> count;
    
    // Count occurrences
    for (char c : str) {
        count[c]++;
    }
    
    // Find first non-repeating
    for (char c : str) {
        if (count[c] == 1) {
            return c;
        }
    }
    
    return '\0';  // No non-repeating character
}
```

### Problem 2: Group Anagrams
```cpp
vector<vector<string>> groupAnagrams(const vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    
    for (const string& str : strs) {
        string sorted = str;
        sort(sorted.begin(), sorted.end());
        groups[sorted].push_back(str);
    }
    
    vector<vector<string>> result;
    for (const auto& [key, group] : groups) {
        result.push_back(group);
    }
    
    return result;
}
```

### Problem 3: LRU Cache
```cpp
class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> map;
    
public:
    LRUCache(int cap) : capacity(cap) {}
    
    int get(int key) {
        auto it = map.find(key);
        if (it == map.end()) return -1;
        
        // Move to front (most recently used)
        cache.splice(cache.begin(), cache, it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        auto it = map.find(key);
        if (it != map.end()) {
            // Update existing
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
        } else {
            // Add new
            if (cache.size() >= capacity) {
                // Remove least recently used
                int keyToRemove = cache.back().first;
                cache.pop_back();
                map.erase(keyToRemove);
            }
            
            cache.push_front({key, value});
            map[key] = cache.begin();
        }
    }
};
```

## 📚 Summary

Key takeaways:
- **Choose containers based on your specific needs**
- **Sequence containers** for ordered data with different access patterns
- **Associative containers** for sorted data with fast lookups
- **Unordered containers** for fast lookups without ordering requirements
- **Container adapters** for specific data structure behaviors
- **Use STL algorithms** for common operations
- **Follow best practices** for performance and safety

Master these containers to write efficient, maintainable C++ code!

---

## 🔗 Related Topics
- [Arrays & Vectors](arrays-vectors.md)
- [Templates](templates.md)
- [STL Algorithms](stl-algorithms.md)
- [Basic Algorithms](dsa/basic-algorithms.md)
