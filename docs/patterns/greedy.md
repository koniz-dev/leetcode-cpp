# 🎯 Greedy Algorithms

## 📚 Overview
**Greedy Algorithms** are algorithmic techniques that choose the optimal choice at each step with the hope of achieving a globally optimal solution. Although not always correct, they often provide good and efficient results.

## 🎯 **When to Use**
- **Optimization problems** - Find optimal values (min/max)
- **Scheduling problems** - Job scheduling, meeting rooms
- **Selection problems** - Choose elements satisfying conditions
- **Partition problems** - Divide arrays/strings into parts
- **Interval problems** - Sort and select intervals

## 🚀 **Core Patterns**

### **1. Activity Selection**
```cpp
// Choose maximum number of activities from n activities
int activitySelection(vector<pair<int, int>>& activities) {
    if (activities.empty()) return 0;
    
    // Sort by end time
    sort(activities.begin(), activities.end(), 
         [](const auto& a, const auto& b) {
             return a.second < b.second;
         });
    
    int count = 1;  // Choose first activity
    int lastEnd = activities[0].second;
    
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].first >= lastEnd) {
            count++;
            lastEnd = activities[i].second;
        }
    }
    
    return count;
}
```

**Time Complexity**: O(n log n)  
**Space Complexity**: O(1)

### **2. Fractional Knapsack**
```cpp
// Knapsack with divisible items
double fractionalKnapsack(vector<pair<int, int>>& items, int capacity) {
    // Sort by value/weight ratio in descending order
    sort(items.begin(), items.end(), 
         [](const auto& a, const auto& b) {
             return (double)a.second / a.first > (double)b.second / b.first;
         });
    
    double totalValue = 0.0;
    int remainingCapacity = capacity;
    
    for (const auto& [weight, value] : items) {
        if (remainingCapacity >= weight) {
            // Take entire item
            totalValue += value;
            remainingCapacity -= weight;
        } else {
            // Take partial item
            totalValue += (double)value * remainingCapacity / weight;
            break;
        }
    }
    
    return totalValue;
}
```

**Time Complexity**: O(n log n)  
**Space Complexity**: O(1)

### **3. Huffman Coding**
```cpp
// Build Huffman tree for data compression
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode *left, *right;
    
    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

HuffmanNode* buildHuffmanTree(vector<pair<char, int>>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
    
    // Create leaf nodes
    for (const auto& [ch, freq] : frequencies) {
        pq.push(new HuffmanNode(ch, freq));
    }
    
    // Build tree
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        
        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }
    
    return pq.top();
}
```

## 🔍 **Advanced Patterns**

### **1. Interval Scheduling**
```cpp
// Sort intervals for optimization
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    // Sort by start time
    sort(intervals.begin(), intervals.end());
    
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] <= merged.back()[1]) {
            // Merge intervals
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            // Add new interval
            merged.push_back(intervals[i]);
        }
    }
    
    return merged;
}

// Find the minimum number of meeting rooms needed
int minMeetingRooms(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    
    vector<int> starts, ends;
    for (const auto& interval : intervals) {
        starts.push_back(interval[0]);
        ends.push_back(interval[1]);
    }
    
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    
    int rooms = 0, endPtr = 0;
    for (int start : starts) {
        if (start < ends[endPtr]) {
            rooms++;  // Need new room
        } else {
            endPtr++;  // Can reuse old room
        }
    }
    
    return rooms;
}
```

### **2. Gas Station Problem**
```cpp
// Find the starting point to complete a circuit
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int totalGas = 0, currentGas = 0, start = 0;
    
    for (int i = 0; i < gas.size(); i++) {
        totalGas += gas[i] - cost[i];
        currentGas += gas[i] - cost[i];
        
        if (currentGas < 0) {
            start = i + 1;
            currentGas = 0;
        }
    }
    
    return totalGas >= 0 ? start : -1;
}
```

### **3. Jump Game**
```cpp
// Check if you can jump to the end of the array
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        if (i > maxReach) return false;  // Cannot reach position i
        
        maxReach = max(maxReach, i + nums[i]);
        
        if (maxReach >= nums.size() - 1) return true;
    }
    
    return true;
}

// Find the minimum number of jumps
int jump(vector<int>& nums) {
    int jumps = 0, currentEnd = 0, farthest = 0;
    
    for (int i = 0; i < nums.size() - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        
        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;
        }
    }
    
    return jumps;
}
```

## 🔍 **Problem Examples**

### **Easy Level**
- [55. Jump Game](https://leetcode.com/problems/jump-game/)
- [122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)
- [455. Assign Cookies](https://leetcode.com/problems/assign-cookies/)

### **Medium Level**
- [45. Jump Game II](https://leetcode.com/problems/jump-game-ii/)
- [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)
- [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/)
- [134. Gas Station](https://leetcode.com/problems/gas-station/)

### **Hard Level**
- [135. Candy](https://leetcode.com/problems/candy/)
- [330. Patching Array](https://leetcode.com/problems/patching-array/)
- [502. IPO](https://leetcode.com/problems/ipo/)

## 💡 **Key Insights**

### **1. Greedy Choice Property**
```cpp
// Choose the optimal choice at each step
// Example: Choose the interval that finishes first
sort(intervals.begin(), intervals.end(), 
     [](const auto& a, const auto& b) {
         return a.second < b.second;  // Sort by end time
     });
```

### **2. Optimal Substructure**
```cpp
// The optimal solution contains the optimal solution of the subproblem
// Example: If item i is chosen, then we need to solve the problem with capacity - weight[i]
```

### **3. Exchange Argument**
```cpp
// Prove that the solution cannot be improved by exchanging
// Often used to prove correctness
```

## 🎯 **C++23 Modern Implementation**

### **Using std::ranges and std::views**
```cpp
// Modern C++23 approach with ranges
auto activitySelectionModern = [&](const auto& activities) -> int {
    if (activities.empty()) return 0;
    
    // Use std::ranges::sort
    auto sorted = activities | std::views::all;
    std::ranges::sort(sorted, {}, &std::pair<int, int>::second);
    
    int count = 1;
    int lastEnd = activities[0].second;
    
    // Use std::views::drop to skip the first element
    for (const auto& [start, end] : activities | std::views::drop(1)) {
        if (start >= lastEnd) {
            count++;
            lastEnd = end;
        }
    }
    
    return count;
};
```

### **Using std::accumulate for Greedy Calculations**
```cpp
// Calculate greedy with std::accumulate
auto calculateGreedyValue = [&](const auto& items, int capacity) -> double {
    // Sort by value/weight ratio
    auto sorted = items | std::views::all;
    std::ranges::sort(sorted, std::greater{}, 
        [](const auto& item) { return (double)item.second / item.first; });
    
    // Use std::accumulate to calculate the sum
    return std::accumulate(sorted.begin(), sorted.end(), 0.0,
        [capacity](double acc, const auto& item) mutable {
            if (capacity <= 0) return acc;
            
            int take = std::min(capacity, item.first);
            capacity -= take;
            return acc + (double)item.second * take / item.first;
        });
};
```

## 📊 **Complexity Analysis**

| Pattern | Time | Space | Best For |
|---------|------|-------|----------|
| Activity Selection | O(n log n) | O(1) | Scheduling problems |
| Fractional Knapsack | O(n log n) | O(1) | Resource allocation |
| Interval Merging | O(n log n) | O(n) | Time-based problems |
| Jump Game | O(n) | O(1) | Array traversal |

## 🎓 **Practice Problems by Category**

### **Scheduling Problems**
1. [Meeting Rooms](https://leetcode.com/problems/meeting-rooms/)
2. [Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/)
3. [Task Scheduler](https://leetcode.com/problems/task-scheduler/)

### **Interval Problems**
1. [Merge Intervals](https://leetcode.com/problems/merge-intervals/)
2. [Insert Interval](https://leetcode.com/problems/insert-interval/)
3. [Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)

### **Jump Problems**
1. [Jump Game](https://leetcode.com/problems/jump-game/)
2. [Jump Game II](https://leetcode.com/problems/jump-game-ii/)
3. [Jump Game III](https://leetcode.com/problems/jump-game-iii/)

### **Stock Problems**
1. [Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)
2. [Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

## 🔗 **Related Patterns**
- **Dynamic Programming** - When greedy is not correct
- **Two Pointers** - Combined with greedy
- **Sorting** - Often necessary for greedy
- **Heap/Priority Queue** - Choose the optimal

## 🚀 **Optimization Tips**

### **1. Early Termination**
```cpp
// Terminate early when possible
if (maxReach >= target) return true;
if (currentSum >= target) break;
```

### **2. State Compression**
```cpp
// Use simple variables instead of complex structures
int maxReach = 0;  // Instead of vector<bool> visited
```

### **3. Greedy Heuristics**
```cpp
// Use heuristics to guide selection
// Example: Choose item with the highest value/weight ratio
```

---

**Remember**: Greedy Algorithms need to prove correctness. Practice to identify patterns! 🚀
