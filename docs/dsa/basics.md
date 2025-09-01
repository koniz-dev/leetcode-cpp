# DSA Basics

## Overview

Data Structures and Algorithms (DSA) form the foundation of computer science and programming. This section introduces the fundamental concepts, basic data structures, and simple algorithms that every programmer should understand.

## What is DSA?

**Data Structures** are ways of organizing and storing data so that it can be accessed and modified efficiently. **Algorithms** are step-by-step procedures or formulas for solving problems.

### Why DSA Matters

- **Efficiency**: Choose the right data structure and algorithm for optimal performance
- **Problem Solving**: Systematic approach to breaking down complex problems
- **Interview Preparation**: Essential for technical interviews and coding assessments
- **Real-world Applications**: Used in databases, operating systems, games, and more

## Time and Space Complexity

### Big O Notation

Big O notation describes the performance or complexity of an algorithm in terms of how it scales with input size.

```cpp
#include <iostream>
#include <vector>

// O(1) - Constant time
int getFirstElement(const std::vector<int>& arr) {
    if (!arr.empty()) return arr[0];
    return -1;
}

// O(n) - Linear time
int findElement(const std::vector<int>& arr, int target) {
    for (int num : arr) {
        if (num == target) return num;
    }
    return -1;
}

// O(n²) - Quadratic time
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// O(log n) - Logarithmic time
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```

### Common Complexity Classes

- **O(1)**: Constant time - operations that don't depend on input size
- **O(log n)**: Logarithmic time - operations that reduce problem size by half each step
- **O(n)**: Linear time - operations that process each element once
- **O(n log n)**: Linearithmic time - efficient sorting algorithms
- **O(n²)**: Quadratic time - nested loops, simple sorting
- **O(2ⁿ)**: Exponential time - recursive algorithms, avoid for large inputs
- **O(n!)**: Factorial time - permutation problems, extremely slow

## Basic Data Structures

### Arrays

Arrays are the simplest data structure - a collection of elements stored at contiguous memory locations.

```cpp
#include <iostream>
#include <array>
#include <vector>

int main() {
    // Static array
    int arr[5] = {1, 2, 3, 4, 5};
    
    // std::array (C++11)
    std::array<int, 5> stdArr = {1, 2, 3, 4, 5};
    
    // std::vector (dynamic array)
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6);
    
    // Accessing elements
    std::cout << "First element: " << arr[0] << std::endl;
    std::cout << "Vector size: " << vec.size() << std::endl;
    
    return 0;
}
```

### Linked Lists

Linked lists are linear data structures where elements are stored in nodes, and each node points to the next node.

```cpp
struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    
public:
    LinkedList() : head(nullptr) {}
    
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    
    bool search(int key) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == key) return true;
            current = current->next;
        }
        return false;
    }
    
    void printList() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};
```

### Stacks

A stack is a linear data structure that follows the Last In First Out (LIFO) principle.

```cpp
#include <iostream>
#include <stack>

int main() {
    std::stack<int> stack;
    
    // Push elements
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    std::cout << "Top element: " << stack.top() << std::endl;
    std::cout << "Stack size: " << stack.size() << std::endl;
    
    // Pop elements
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    std::cout << std::endl;
    
    return 0;
}
```

### Queues

A queue is a linear data structure that follows the First In First Out (FIFO) principle.

```cpp
#include <iostream>
#include <queue>

int main() {
    std::queue<int> queue;
    
    // Enqueue elements
    queue.push(1);
    queue.push(2);
    queue.push(3);
    
    std::cout << "Front element: " << queue.front() << std::endl;
    std::cout << "Back element: " << queue.back() << std::endl;
    
    // Dequeue elements
    while (!queue.empty()) {
        std::cout << queue.front() << " ";
        queue.pop();
    }
    std::cout << std::endl;
    
    return 0;
}
```

## Simple Algorithms

### Linear Search

Linear search is the simplest search algorithm that checks each element in a list until the target is found.

```cpp
int linearSearch(const std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;  // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}

// Using range-based for loop
int linearSearchRange(const std::vector<int>& arr, int target) {
    int index = 0;
    for (const auto& element : arr) {
        if (element == target) {
            return index;
        }
        index++;
    }
    return -1;
}
```

### Bubble Sort

Bubble sort is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.

```cpp
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Optimized bubble sort
void optimizedBubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // If no swapping occurred, array is sorted
        if (!swapped) {
            break;
        }
    }
}
```

## Summary

DSA basics provide the essential foundation for:

- **Understanding complexity**: How algorithms scale with input size
- **Basic data structures**: Arrays, linked lists, stacks, and queues
- **Simple algorithms**: Linear search and bubble sort
- **Problem-solving approach**: Systematic thinking about data organization

Key concepts:
- **Time complexity**: How fast an algorithm runs
- **Space complexity**: How much memory an algorithm uses
- **Data organization**: Choosing the right structure for the problem
- **Algorithm efficiency**: Understanding trade-offs between different approaches

These basics form the foundation for more advanced data structures and algorithms, and are essential for writing efficient, scalable code.
