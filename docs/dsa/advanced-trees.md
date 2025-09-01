# Advanced Tree Data Structures

## Overview

Advanced tree data structures extend beyond basic binary trees to provide efficient solutions for specific problems. These include self-balancing trees, specialized tree variants, and tree-based algorithms that optimize for different use cases.

## Self-Balancing Trees

### AVL Tree

```cpp
#include <iostream>
#include <algorithm>

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    
    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        
        return x;
    }
    
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        
        return y;
    }
    
    AVLNode* insert(AVLNode* node, int key) {
        if (!node) {
            return new AVLNode(key);
        }
        
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node; // Duplicate keys not allowed
        }
        
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        
        // Right Right Case
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        
        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    void inorderTraversal(AVLNode* node) {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(int key) {
        root = insert(root, key);
    }
    
    void print() {
        inorderTraversal(root);
        std::cout << std::endl;
    }
};
```

### Red-Black Tree

```cpp
#include <iostream>

enum Color { RED, BLACK };

struct RBNode {
    int key;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    Color color;
    
    RBNode(int k) : key(k), left(nullptr), right(nullptr), 
                    parent(nullptr), color(RED) {}
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* nil;
    
    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        
        if (y->left != nil) {
            y->left->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        
        y->left = x;
        x->parent = y;
    }
    
    void rightRotate(RBNode* x) {
        RBNode* y = x->left;
        x->left = y->right;
        
        if (y->right != nil) {
            y->right->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        
        y->right = x;
        x->parent = y;
    }
    
    void insertFixup(RBNode* k) {
        RBNode* u;
        while (k->parent && k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u && u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;
                if (u && u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->color = BLACK;
    }
    
public:
    RedBlackTree() {
        nil = new RBNode(0);
        nil->color = BLACK;
        root = nil;
    }
    
    void insert(int key) {
        RBNode* node = new RBNode(key);
        RBNode* y = nullptr;
        RBNode* x = root;
        
        while (x != nil) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->key < y->key) {
            y->left = node;
        } else {
            y->right = node;
        }
        
        node->left = nil;
        node->right = nil;
        node->color = RED;
        
        insertFixup(node);
    }
};
```

## B-Trees

### B-Tree Implementation

```cpp
#include <vector>
#include <iostream>

template<typename T>
struct BTreeNode {
    std::vector<T> keys;
    std::vector<BTreeNode<T>*> children;
    bool isLeaf;
    
    BTreeNode(bool leaf = true) : isLeaf(leaf) {}
};

template<typename T>
class BTree {
private:
    BTreeNode<T>* root;
    int t; // Minimum degree
    
    void splitChild(BTreeNode<T>* parent, int index) {
        BTreeNode<T>* child = parent->children[index];
        BTreeNode<T>* newNode = new BTreeNode<T>(child->isLeaf);
        
        // Move keys
        for (int i = 0; i < t - 1; ++i) {
            newNode->keys.push_back(child->keys[i + t]);
        }
        
        // Move children if not leaf
        if (!child->isLeaf) {
            for (int i = 0; i < t; ++i) {
                newNode->children.push_back(child->children[i + t]);
            }
        }
        
        // Insert middle key into parent
        parent->keys.insert(parent->keys.begin() + index, child->keys[t - 1]);
        parent->children.insert(parent->children.begin() + index + 1, newNode);
        
        // Remove moved keys and children from child
        child->keys.resize(t - 1);
        if (!child->isLeaf) {
            child->children.resize(t);
        }
    }
    
    void insertNonFull(BTreeNode<T>* node, T key) {
        int i = node->keys.size() - 1;
        
        if (node->isLeaf) {
            while (i >= 0 && key < node->keys[i]) {
                node->keys.insert(node->keys.begin() + i + 1, node->keys[i]);
                i--;
            }
            node->keys.insert(node->keys.begin() + i + 1, key);
        } else {
            while (i >= 0 && key < node->keys[i]) {
                i--;
            }
            i++;
            
            if (node->children[i]->keys.size() == 2 * t - 1) {
                splitChild(node, i);
                if (key > node->keys[i]) {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }
    
    void printTree(BTreeNode<T>* node, int depth = 0) {
        if (node) {
            for (int i = 0; i < depth; ++i) {
                std::cout << "  ";
            }
            
            for (int i = 0; i < node->keys.size(); ++i) {
                std::cout << node->keys[i] << " ";
            }
            std::cout << std::endl;
            
            if (!node->isLeaf) {
                for (int i = 0; i < node->children.size(); ++i) {
                    printTree(node->children[i], depth + 1);
                }
            }
        }
    }
    
public:
    BTree(int degree) : root(nullptr), t(degree) {}
    
    void insert(T key) {
        if (root == nullptr) {
            root = new BTreeNode<T>(true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == 2 * t - 1) {
                BTreeNode<T>* newRoot = new BTreeNode<T>(false);
                newRoot->children.push_back(root);
                splitChild(newRoot, 0);
                
                int i = 0;
                if (key > newRoot->keys[0]) {
                    i++;
                }
                insertNonFull(newRoot->children[i], key);
                
                root = newRoot;
            } else {
                insertNonFull(root, key);
            }
        }
    }
    
    void print() {
        printTree(root);
    }
};
```

## Trie (Prefix Tree)

### Basic Trie Implementation

```cpp
#include <string>
#include <unordered_map>
#include <iostream>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;
    
    void deleteTrie(TrieNode* node) {
        if (node) {
            for (auto& pair : node->children) {
                deleteTrie(pair.second);
            }
            delete node;
        }
    }
    
public:
    Trie() : root(new TrieNode()) {}
    
    ~Trie() {
        deleteTrie(root);
    }
    
    void insert(const std::string& word) {
        TrieNode* current = root;
        
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        
        current->isEndOfWord = true;
    }
    
    bool search(const std::string& word) {
        TrieNode* current = root;
        
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        
        return current->isEndOfWord;
    }
    
    bool startsWith(const std::string& prefix) {
        TrieNode* current = root;
        
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        
        return true;
    }
    
    void getAllWordsWithPrefix(const std::string& prefix, std::vector<std::string>& words) {
        TrieNode* current = root;
        
        // Navigate to prefix
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return;
            }
            current = current->children[c];
        }
        
        // Collect all words from this node
        collectWords(current, prefix, words);
    }
    
private:
    void collectWords(TrieNode* node, std::string currentWord, std::vector<std::string>& words) {
        if (node->isEndOfWord) {
            words.push_back(currentWord);
        }
        
        for (const auto& pair : node->children) {
            collectWords(pair.second, currentWord + pair.first, words);
        }
    }
};
```

## Segment Trees

### Basic Segment Tree

```cpp
#include <vector>
#include <iostream>

class SegmentTree {
private:
    std::vector<int> tree;
    int n;
    
    void build(const std::vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    void update(int node, int start, int end, int index, int value) {
        if (start == end) {
            tree[node] = value;
            return;
        }
        
        int mid = (start + end) / 2;
        if (index <= mid) {
            update(2 * node, start, mid, index, value);
        } else {
            update(2 * node + 1, mid + 1, end, index, value);
        }
        
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    int query(int node, int start, int end, int left, int right) {
        if (right < start || left > end) {
            return 0;
        }
        
        if (left <= start && right >= end) {
            return tree[node];
        }
        
        int mid = (start + end) / 2;
        int leftSum = query(2 * node, start, mid, left, right);
        int rightSum = query(2 * node + 1, mid + 1, end, left, right);
        
        return leftSum + rightSum;
    }
    
public:
    SegmentTree(const std::vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    
    void update(int index, int value) {
        update(1, 0, n - 1, index, value);
    }
    
    int rangeSum(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }
};
```

### Lazy Propagation Segment Tree

```cpp
#include <vector>
#include <iostream>

class LazySegmentTree {
private:
    std::vector<int> tree;
    std::vector<int> lazy;
    int n;
    
    void pushDown(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node] * (end - start + 1);
            
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            
            lazy[node] = 0;
        }
    }
    
    void updateRange(int node, int start, int end, int left, int right, int value) {
        pushDown(node, start, end);
        
        if (right < start || left > end) {
            return;
        }
        
        if (left <= start && right >= end) {
            lazy[node] += value;
            pushDown(node, start, end);
            return;
        }
        
        int mid = (start + end) / 2;
        updateRange(2 * node, start, mid, left, right, value);
        updateRange(2 * node + 1, mid + 1, end, left, right, value);
        
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    int queryRange(int node, int start, int end, int left, int right) {
        pushDown(node, start, end);
        
        if (right < start || left > end) {
            return 0;
        }
        
        if (left <= start && right >= end) {
            return tree[node];
        }
        
        int mid = (start + end) / 2;
        int leftSum = queryRange(2 * node, start, mid, left, right);
        int rightSum = queryRange(2 * node + 1, mid + 1, end, left, right);
        
        return leftSum + rightSum;
    }
    
public:
    LazySegmentTree(int size) : n(size) {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }
    
    void updateRange(int left, int right, int value) {
        updateRange(1, 0, n - 1, left, right, value);
    }
    
    int queryRange(int left, int right) {
        return queryRange(1, 0, n - 1, left, right);
    }
};
```

## Fenwick Tree (Binary Indexed Tree)

```cpp
#include <vector>
#include <iostream>

class FenwickTree {
private:
    std::vector<int> tree;
    int n;
    
    int getNext(int index) {
        return index + (index & -index);
    }
    
    int getParent(int index) {
        return index - (index & -index);
    }
    
public:
    FenwickTree(int size) : n(size) {
        tree.resize(n + 1, 0);
    }
    
    void update(int index, int value) {
        index++; // 1-indexed
        while (index <= n) {
            tree[index] += value;
            index = getNext(index);
        }
    }
    
    int query(int index) {
        index++; // 1-indexed
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index = getParent(index);
        }
        return sum;
    }
    
    int rangeQuery(int left, int right) {
        return query(right) - query(left - 1);
    }
};
```

## Splay Trees

```cpp
#include <iostream>

struct SplayNode {
    int key;
    SplayNode* left;
    SplayNode* right;
    SplayNode* parent;
    
    SplayNode(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

class SplayTree {
private:
    SplayNode* root;
    
    void rotateRight(SplayNode* x) {
        SplayNode* y = x->left;
        x->left = y->right;
        
        if (y->right) {
            y->right->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        
        y->right = x;
        x->parent = y;
    }
    
    void rotateLeft(SplayNode* x) {
        SplayNode* y = x->right;
        x->right = y->left;
        
        if (y->left) {
            y->left->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        
        y->left = x;
        x->parent = y;
    }
    
    void splay(SplayNode* x) {
        while (x->parent) {
            if (x->parent->parent == nullptr) {
                // Zig
                if (x == x->parent->left) {
                    rotateRight(x->parent);
                } else {
                    rotateLeft(x->parent);
                }
            } else {
                SplayNode* p = x->parent;
                SplayNode* g = p->parent;
                
                if (x == p->left && p == g->left) {
                    // Zig-Zig
                    rotateRight(g);
                    rotateRight(p);
                } else if (x == p->right && p == g->right) {
                    // Zig-Zig
                    rotateLeft(g);
                    rotateLeft(p);
                } else if (x == p->right && p == g->left) {
                    // Zig-Zag
                    rotateLeft(p);
                    rotateRight(g);
                } else {
                    // Zig-Zag
                    rotateRight(p);
                    rotateLeft(g);
                }
            }
        }
    }
    
public:
    SplayTree() : root(nullptr) {}
    
    void insert(int key) {
        SplayNode* newNode = new SplayNode(key);
        
        if (root == nullptr) {
            root = newNode;
            return;
        }
        
        SplayNode* current = root;
        SplayNode* parent = nullptr;
        
        while (current) {
            parent = current;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        newNode->parent = parent;
        if (key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        
        splay(newNode);
    }
    
    SplayNode* search(int key) {
        SplayNode* current = root;
        SplayNode* last = nullptr;
        
        while (current) {
            last = current;
            if (key < current->key) {
                current = current->left;
            } else if (key > current->key) {
                current = current->right;
            } else {
                break;
            }
        }
        
        if (last) {
            splay(last);
        }
        
        return current;
    }
};
```

## Summary

Advanced tree data structures provide:
- **Self-balancing**: AVL trees, Red-Black trees for guaranteed height
- **Efficient storage**: B-trees for disk-based systems
- **String operations**: Tries for prefix matching
- **Range queries**: Segment trees for interval operations
- **Dynamic updates**: Fenwick trees for cumulative operations
- **Adaptive structure**: Splay trees for frequently accessed elements

Key applications:
- **Databases**: B-trees for indexing
- **Text processing**: Tries for autocomplete
- **Range queries**: Segment trees for statistics
- **Dynamic programming**: Fenwick trees for cumulative sums
- **Caching**: Splay trees for hot data

These structures optimize different aspects of tree operations, from height balancing to cache performance, making them suitable for various specialized use cases.
