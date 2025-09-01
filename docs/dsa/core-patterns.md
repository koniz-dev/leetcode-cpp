# DSA Core Patterns

## Overview

DSA core patterns are fundamental algorithmic techniques that form the building blocks for solving complex problems. Understanding these patterns is essential for intermediate-level problem-solving and provides a systematic approach to algorithm design.

## Two Pointers Technique

The two pointers technique uses two pointers to traverse data structures, often reducing time complexity from O(n²) to O(n).

### Basic Two Pointers

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class TwoPointers {
public:
    // Find pairs with given sum in sorted array
    static std::vector<std::pair<int, int>> findPairsWithSum(const std::vector<int>& arr, int target) {
        std::vector<std::pair<int, int>> pairs;
        int left = 0, right = arr.size() - 1;
        
        while (left < right) {
            int sum = arr[left] + arr[right];
            
            if (sum == target) {
                pairs.push_back({arr[left], arr[right]});
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return pairs;
    }
    
    // Remove duplicates from sorted array
    static int removeDuplicates(std::vector<int>& arr) {
        if (arr.empty()) return 0;
        
        int writeIndex = 1;
        for (int readIndex = 1; readIndex < arr.size(); ++readIndex) {
            if (arr[readIndex] != arr[readIndex - 1]) {
                arr[writeIndex] = arr[readIndex];
                writeIndex++;
            }
        }
        
        return writeIndex;
    }
    
    // Reverse array
    static void reverseArray(std::vector<int>& arr) {
        int left = 0, right = arr.size() - 1;
        
        while (left < right) {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
    
    // Check if array is palindrome
    static bool isPalindrome(const std::vector<int>& arr) {
        int left = 0, right = arr.size() - 1;
        
        while (left < right) {
            if (arr[left] != arr[right]) {
                return false;
            }
            left++;
            right--;
        }
        
        return true;
    }
};
```

### Advanced Two Pointers

```cpp
#include <iostream>
#include <vector>
#include <string>

class AdvancedTwoPointers {
public:
    // Container with most water
    static int maxArea(const std::vector<int>& height) {
        int maxArea = 0;
        int left = 0, right = height.size() - 1;
        
        while (left < right) {
            int width = right - left;
            int h = std::min(height[left], height[right]);
            maxArea = std::max(maxArea, width * h);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxArea;
    }
    
    // Trapping rain water
    static int trapRainWater(const std::vector<int>& height) {
        if (height.size() < 3) return 0;
        
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        int water = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    water += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    water += rightMax - height[right];
                }
                right--;
            }
        }
        
        return water;
    }
    
    // Three sum closest
    static int threeSumClosest(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int closest = nums[0] + nums[1] + nums[2];
        
        for (int i = 0; i < nums.size() - 2; ++i) {
            int left = i + 1, right = nums.size() - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (std::abs(sum - target) < std::abs(closest - target)) {
                    closest = sum;
                }
                
                if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return closest;
    }
};
```

## Sliding Window Technique

The sliding window technique maintains a subset of elements that slides through the data structure, useful for solving problems involving contiguous subarrays or substrings.

### Fixed Size Window

```cpp
#include <iostream>
#include <vector>
#include <deque>

class SlidingWindow {
public:
    // Maximum sum of subarray of size k
    static int maxSumSubarray(const std::vector<int>& arr, int k) {
        if (k > arr.size()) return -1;
        
        int windowSum = 0;
        for (int i = 0; i < k; ++i) {
            windowSum += arr[i];
        }
        
        int maxSum = windowSum;
        for (int i = k; i < arr.size(); ++i) {
            windowSum = windowSum - arr[i - k] + arr[i];
            maxSum = std::max(maxSum, windowSum);
        }
        
        return maxSum;
    }
    
    // First negative number in every window of size k
    static std::vector<int> firstNegativeInWindow(const std::vector<int>& arr, int k) {
        std::vector<int> result;
        std::deque<int> negIndices;
        
        // Process first window
        for (int i = 0; i < k; ++i) {
            if (arr[i] < 0) {
                negIndices.push_back(i);
            }
        }
        
        // Add result for first window
        if (!negIndices.empty()) {
            result.push_back(arr[negIndices.front()]);
        } else {
            result.push_back(0);
        }
        
        // Process remaining windows
        for (int i = k; i < arr.size(); ++i) {
            // Remove elements outside current window
            while (!negIndices.empty() && negIndices.front() <= i - k) {
                negIndices.pop_front();
            }
            
            // Add current element if negative
            if (arr[i] < 0) {
                negIndices.push_back(i);
            }
            
            // Add result for current window
            if (!negIndices.empty()) {
                result.push_back(arr[negIndices.front()]);
            } else {
                result.push_back(0);
            }
        }
        
        return result;
    }
};
```

### Variable Size Window

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

class VariableSlidingWindow {
public:
    // Minimum subarray with sum >= target
    static int minSubarrayLength(const std::vector<int>& arr, int target) {
        int n = arr.size();
        int left = 0, sum = 0;
        int minLength = n + 1;
        
        for (int right = 0; right < n; ++right) {
            sum += arr[right];
            
            while (sum >= target) {
                minLength = std::min(minLength, right - left + 1);
                sum -= arr[left];
                left++;
            }
        }
        
        return minLength <= n ? minLength : 0;
    }
    
    // Longest substring with at most k distinct characters
    static int longestSubstringKDistinct(const std::string& s, int k) {
        std::unordered_map<char, int> charCount;
        int left = 0, maxLength = 0;
        
        for (int right = 0; right < s.length(); ++right) {
            charCount[s[right]]++;
            
            while (charCount.size() > k) {
                charCount[s[left]]--;
                if (charCount[s[left]] == 0) {
                    charCount.erase(s[left]);
                }
                left++;
            }
            
            maxLength = std::max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
    
    // Longest substring without repeating characters
    static int longestSubstringNoRepeat(const std::string& s) {
        std::unordered_map<char, int> charIndex;
        int left = 0, maxLength = 0;
        
        for (int right = 0; right < s.length(); ++right) {
            if (charIndex.find(s[right]) != charIndex.end()) {
                left = std::max(left, charIndex[s[right]] + 1);
            }
            
            charIndex[s[right]] = right;
            maxLength = std::max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};
```

## Binary Search

Binary search is a divide-and-conquer algorithm that efficiently finds elements in sorted arrays or applies to problems with monotonic properties.

### Standard Binary Search

```cpp
#include <iostream>
#include <vector>

class BinarySearch {
public:
    // Standard binary search
    static int search(const std::vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
    
    // Find first occurrence
    static int findFirst(const std::vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                result = mid;
                right = mid - 1;  // Continue searching left
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    // Find last occurrence
    static int findLast(const std::vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                result = mid;
                left = mid + 1;  // Continue searching right
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    // Find insertion position
    static int findInsertPosition(const std::vector<int>& arr, int target) {
        int left = 0, right = arr.size();
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
};
```

### Binary Search on Answer

```cpp
#include <iostream>
#include <vector>
#include <cmath>

class BinarySearchOnAnswer {
public:
    // Square root with precision
    static double sqrt(double x, double precision = 1e-6) {
        if (x < 0) return -1;  // Invalid input
        
        double left = 0, right = std::max(1.0, x);
        
        while (right - left > precision) {
            double mid = left + (right - left) / 2;
            double square = mid * mid;
            
            if (square == x) {
                return mid;
            } else if (square < x) {
                left = mid;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
    
    // Find minimum in rotated sorted array
    static int findMinInRotated(const std::vector<int>& arr) {
        int left = 0, right = arr.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] > arr[right]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return arr[left];
    }
    
    // Capacity to ship packages within D days
    static int shipWithinDays(const std::vector<int>& weights, int days) {
        int left = *std::max_element(weights.begin(), weights.end());
        int right = std::accumulate(weights.begin(), weights.end(), 0);
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (canShip(weights, days, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
private:
    static bool canShip(const std::vector<int>& weights, int days, int capacity) {
        int currentWeight = 0;
        int requiredDays = 1;
        
        for (int weight : weights) {
            if (currentWeight + weight > capacity) {
                currentWeight = weight;
                requiredDays++;
            } else {
                currentWeight += weight;
            }
        }
        
        return requiredDays <= days;
    }
};
```

## Tree Traversal

Tree traversal algorithms visit all nodes in a tree data structure in a specific order.

### Depth-First Search (DFS)

```cpp
#include <iostream>
#include <vector>
#include <stack>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class TreeTraversal {
public:
    // Recursive DFS traversals
    static void inorderRecursive(TreeNode* root) {
        if (root == nullptr) return;
        
        inorderRecursive(root->left);
        std::cout << root->val << " ";
        inorderRecursive(root->right);
    }
    
    static void preorderRecursive(TreeNode* root) {
        if (root == nullptr) return;
        
        std::cout << root->val << " ";
        preorderRecursive(root->left);
        preorderRecursive(root->right);
    }
    
    static void postorderRecursive(TreeNode* root) {
        if (root == nullptr) return;
        
        postorderRecursive(root->left);
        postorderRecursive(root->right);
        std::cout << root->val << " ";
    }
    
    // Iterative DFS traversals
    static std::vector<int> inorderIterative(TreeNode* root) {
        std::vector<int> result;
        std::stack<TreeNode*> stack;
        TreeNode* current = root;
        
        while (current != nullptr || !stack.empty()) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            
            current = stack.top();
            stack.pop();
            result.push_back(current->val);
            current = current->right;
        }
        
        return result;
    }
    
    static std::vector<int> preorderIterative(TreeNode* root) {
        std::vector<int> result;
        if (root == nullptr) return result;
        
        std::stack<TreeNode*> stack;
        stack.push(root);
        
        while (!stack.empty()) {
            TreeNode* current = stack.top();
            stack.pop();
            
            result.push_back(current->val);
            
            if (current->right) {
                stack.push(current->right);
            }
            if (current->left) {
                stack.push(current->left);
            }
        }
        
        return result;
    }
    
    static std::vector<int> postorderIterative(TreeNode* root) {
        std::vector<int> result;
        if (root == nullptr) return result;
        
        std::stack<TreeNode*> stack;
        stack.push(root);
        
        while (!stack.empty()) {
            TreeNode* current = stack.top();
            stack.pop();
            
            result.insert(result.begin(), current->val);
            
            if (current->left) {
                stack.push(current->left);
            }
            if (current->right) {
                stack.push(current->right);
            }
        }
        
        return result;
    }
};
```

### Breadth-First Search (BFS)

```cpp
#include <iostream>
#include <vector>
#include <queue>

class BreadthFirstSearch {
public:
    // Level order traversal
    static std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (root == nullptr) return result;
        
        std::queue<TreeNode*> queue;
        queue.push(root);
        
        while (!queue.empty()) {
            int levelSize = queue.size();
            std::vector<int> currentLevel;
            
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* current = queue.front();
                queue.pop();
                
                currentLevel.push_back(current->val);
                
                if (current->left) {
                    queue.push(current->left);
                }
                if (current->right) {
                    queue.push(current->right);
                }
            }
            
            result.push_back(currentLevel);
        }
        
        return result;
    }
    
    // Zigzag level order traversal
    static std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (root == nullptr) return result;
        
        std::queue<TreeNode*> queue;
        queue.push(root);
        bool leftToRight = true;
        
        while (!queue.empty()) {
            int levelSize = queue.size();
            std::vector<int> currentLevel(levelSize);
            
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* current = queue.front();
                queue.pop();
                
                int index = leftToRight ? i : levelSize - 1 - i;
                currentLevel[index] = current->val;
                
                if (current->left) {
                    queue.push(current->left);
                }
                if (current->right) {
                    queue.push(current->right);
                }
            }
            
            result.push_back(currentLevel);
            leftToRight = !leftToRight;
        }
        
        return result;
    }
    
    // Right side view of binary tree
    static std::vector<int> rightSideView(TreeNode* root) {
        std::vector<int> result;
        if (root == nullptr) return result;
        
        std::queue<TreeNode*> queue;
        queue.push(root);
        
        while (!queue.empty()) {
            int levelSize = queue.size();
            
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* current = queue.front();
                queue.pop();
                
                if (i == levelSize - 1) {
                    result.push_back(current->val);
                }
                
                if (current->left) {
                    queue.push(current->left);
                }
                if (current->right) {
                    queue.push(current->right);
                }
            }
        }
        
        return result;
    }
};
```

## Summary

DSA core patterns provide systematic approaches to problem-solving:

- **Two Pointers**: Efficient traversal and comparison algorithms
- **Sliding Window**: Contiguous subarray/substring problems
- **Binary Search**: Divide-and-conquer with sorted data or monotonic properties
- **Tree Traversal**: Systematic visiting of tree nodes

Key benefits:
- **Efficiency**: Often reduce time complexity significantly
- **Systematic**: Provide structured approaches to complex problems
- **Reusable**: Can be adapted to various problem types
- **Foundation**: Essential for advanced algorithm design

These patterns form the core toolkit for intermediate-level algorithmic problem-solving and are fundamental to mastering data structures and algorithms.
