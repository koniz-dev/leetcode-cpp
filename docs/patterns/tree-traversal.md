# 🌳 Tree Traversal

## 📚 Overview
**Tree Traversal** is a technique for traversing all nodes in a tree in a specific order. Understanding these patterns is crucial for solving tree-related problems.

## 🎯 **When to Use**
- **Tree problems** - Binary tree, binary search tree traversal
- **Graph problems** - DFS, BFS on graphs
- **Path problems** - Find path from root to leaf
- **Validation problems** - Check tree validity
- **Construction problems** - Build tree from data

## 🚀 **Core Traversal Patterns**

### **1. Depth-First Search (DFS)**
```cpp
// DFS Recursive - Inorder (Left -> Root -> Right)
void inorderTraversal(TreeNode* root) {
    if (!root) return;
    
    inorderTraversal(root->left);    // Left
    cout << root->val << " ";        // Root
    inorderTraversal(root->right);   // Right
}

// DFS Recursive - Preorder (Root -> Left -> Right)
void preorderTraversal(TreeNode* root) {
    if (!root) return;
    
    cout << root->val << " ";        // Root
    preorderTraversal(root->left);   // Left
    preorderTraversal(root->right);  // Right
}

// DFS Recursive - Postorder (Left -> Right -> Root)
void postorderTraversal(TreeNode* root) {
    if (!root) return;
    
    postorderTraversal(root->left);  // Left
    postorderTraversal(root->right); // Right
    cout << root->val << " ";        // Root
}
```

**Time Complexity**: O(n)  
**Space Complexity**: O(h) - h is the height of the tree

### **2. Breadth-First Search (BFS)**
```cpp
// BFS Iterative - Level Order Traversal
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            currentLevel.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(currentLevel);
    }
    
    return result;
}
```

**Time Complexity**: O(n)  
**Space Complexity**: O(w) - w is the maximum width

### **3. DFS Iterative with Stack**
```cpp
// Inorder Traversal Iterative
vector<int> inorderTraversalIterative(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* current = root;
    
    while (current || !st.empty()) {
        // Go to leftmost node
        while (current) {
            st.push(current);
            current = current->left;
        }
        
        // Process current node
        current = st.top();
        st.pop();
        result.push_back(current->val);
        
        // Move to right subtree
        current = current->right;
    }
    
    return result;
}
```

## 🔍 **Advanced Patterns**

### **1. Morris Traversal (Space O(1))**
```cpp
// Inorder Morris Traversal - No extra space
vector<int> inorderMorris(TreeNode* root) {
    vector<int> result;
    TreeNode* current = root;
    
    while (current) {
        if (!current->left) {
            // No left child, visit current node
            result.push_back(current->val);
            current = current->right;
        } else {
            // Find inorder predecessor
            TreeNode* predecessor = current->left;
            while (predecessor->right && predecessor->right != current) {
                predecessor = predecessor->right;
            }
            
            if (!predecessor->right) {
                // Make current as right child of predecessor
                predecessor->right = current;
                current = current->left;
            } else {
                // Restore tree structure
                predecessor->right = nullptr;
                result.push_back(current->val);
                current = current->right;
            }
        }
    }
    
    return result;
}
```

### **2. Vertical Order Traversal**
```cpp
// Vertical Order Traversal
vector<vector<int>> verticalTraversal(TreeNode* root) {
    map<int, map<int, multiset<int>>> nodes;
    queue<tuple<TreeNode*, int, int>> q;
    q.push({root, 0, 0});
    
    while (!q.empty()) {
        auto [node, row, col] = q.front();
        q.pop();
        
        if (node) {
            nodes[col][row].insert(node->val);
            q.push({node->left, row + 1, col - 1});
            q.push({node->right, row + 1, col + 1});
        }
    }
    
    vector<vector<int>> result;
    for (auto& [col, rows] : nodes) {
        vector<int> colNodes;
        for (auto& [row, values] : rows) {
            colNodes.insert(colNodes.end(), values.begin(), values.end());
        }
        result.push_back(colNodes);
    }
    
    return result;
}
```

### **3. Boundary Traversal**
```cpp
// Boundary Traversal (Left Boundary + Leaves + Right Boundary)
vector<int> boundaryTraversal(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    // Add root
    result.push_back(root->val);
    
    // Left boundary (excluding root and leaves)
    addLeftBoundary(root->left, result);
    
    // Add leaves
    addLeaves(root, result);
    
    // Right boundary (excluding root and leaves)
    addRightBoundary(root->right, result);
    
    return result;
}

void addLeftBoundary(TreeNode* node, vector<int>& result) {
    if (!node || (!node->left && !node->right)) return;
    
    result.push_back(node->val);
    if (node->left) {
        addLeftBoundary(node->left, result);
    } else {
        addLeftBoundary(node->right, result);
    }
}

void addLeaves(TreeNode* node, vector<int>& result) {
    if (!node) return;
    
    if (!node->left && !node->right) {
        result.push_back(node->val);
        return;
    }
    
    addLeaves(node->left, result);
    addLeaves(node->right, result);
}
```

## 🔍 **Problem Examples**

### **Easy Level**
- [94. Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
- [144. Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)
- [145. Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/)

### **Medium Level**
- [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
- [103. Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)
- [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)

### **Hard Level**
- [987. Vertical Order Traversal of a Binary Tree](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/)
- [545. Boundary of Binary Tree](https://leetcode.com/problems/boundary-of-binary-tree/)
- [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

## 💡 **Key Insights**

### **1. Recursive vs Iterative**
```cpp
// Recursive: Simple, easy to understand, but uses stack space
void dfsRecursive(TreeNode* root) {
    if (!root) return;
    // Process node
    dfsRecursive(root->left);
    dfsRecursive(root->right);
}

// Iterative: More complex, but uses less stack space
void dfsIterative(TreeNode* root) {
    stack<TreeNode*> st;
    st.push(root);
    
    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        // Process node
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
}
```

### **2. State Management**
```cpp
// Use stack to manage state
struct NodeState {
    TreeNode* node;
    bool visited;
    NodeState(TreeNode* n, bool v) : node(n), visited(v) {}
};

void dfsWithState(TreeNode* root) {
    stack<NodeState> st;
    st.push({root, false});
    
    while (!st.empty()) {
        auto [node, visited] = st.top();
        st.pop();
        
        if (!node) continue;
        
        if (!visited) {
            st.push({node, true});
            st.push({node->right, false});
            st.push({node->left, false});
        } else {
            // Process node
            cout << node->val << " ";
        }
    }
}
```

### **3. Path Tracking**
```cpp
// Track path from root to current node
void dfsWithPath(TreeNode* root, vector<int>& path) {
    if (!root) return;
    
    path.push_back(root->val);
    
    if (!root->left && !root->right) {
        // Leaf node - process path
        printPath(path);
    }
    
    dfsWithPath(root->left, path);
    dfsWithPath(root->right, path);
    
    path.pop_back();  // Backtrack
}
```

## 🎯 **C++23 Modern Implementation**

### **Using std::ranges and std::views**
```cpp
// Modern C++23 approach with ranges
auto levelOrderModern = [&](TreeNode* root) -> std::vector<std::vector<int>> {
    if (!root) return {};
    
    std::vector<std::vector<int>> result;
    std::queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<int> currentLevel;
        
        // Process current level
        for (int i : std::views::iota(0, levelSize)) {
            TreeNode* node = q.front();
            q.pop();
            
            currentLevel.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(std::move(currentLevel));
    }
    
    return result;
};
```

### **Using std::function for Traversal Strategy**
```cpp
// Strategy pattern for traversal
using TraversalStrategy = std::function<void(TreeNode*, std::vector<int>&)>;

auto createTraversalStrategy(const std::string& type) -> TraversalStrategy {
    if (type == "inorder") {
        return [](TreeNode* root, std::vector<int>& result) {
            if (!root) return;
            createTraversalStrategy("inorder")(root->left, result);
            result.push_back(root->val);
            createTraversalStrategy("inorder")(root->right, result);
        };
    } else if (type == "preorder") {
        return [](TreeNode* root, std::vector<int>& result) {
            if (!root) return;
            result.push_back(root->val);
            createTraversalStrategy("preorder")(root->left, result);
            createTraversalStrategy("preorder")(root->right, result);
        };
    }
    // Add more strategies...
    
    return [](TreeNode*, std::vector<int>&) {};
}
```

## 📊 **Complexity Analysis**

| Traversal | Time | Space | Best For |
|-----------|------|-------|----------|
| DFS Recursive | O(n) | O(h) | Simple traversal |
| DFS Iterative | O(n) | O(w) | Memory efficient |
| BFS Level Order | O(n) | O(w) | Level-based problems |
| Morris | O(n) | O(1) | Space optimization |

## 🎓 **Practice Problems by Category**

### **Basic Traversal**
1. [Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
2. [Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)
3. [Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/)

### **Level Order Problems**
1. [Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
2. [Zigzag Level Order](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)
3. [Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)

### **Advanced Traversal**
1. [Vertical Order](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/)
2. [Boundary Traversal](https://leetcode.com/problems/boundary-of-binary-tree/)
3. [Serialize/Deserialize](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

## 🔗 **Related Patterns**
- **Graph Algorithms** - DFS/BFS on graphs
- **Backtracking** - Path finding and state exploration
- **Dynamic Programming** - Tree DP problems
- **Binary Search** - BST validation and operations

## 🚀 **Optimization Tips**

### **1. Early Termination**
```cpp
// Stop early when result is found
if (found) return;
```

### **2. Memory Optimization**
```cpp
// Use Morris traversal for O(1) space
// Or iterative approach instead of recursive
```

### **3. State Compression**
```cpp
// Use bit manipulation for state
// Example: visited nodes, path state
```

---

**Remember**: Tree Traversal is the foundation for many tree and graph problems. Practice to master! 🚀
