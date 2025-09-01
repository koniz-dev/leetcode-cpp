# 🟢 Basic Data Structures

## 📚 Overview
Data structures are ways of organizing and storing data so that it can be accessed and modified efficiently. This guide covers the fundamental data structures you'll use in most programming problems.

---

## 📊 Arrays

### What is an Array?
An array is a collection of elements stored at contiguous memory locations. Elements can be accessed directly using an index.

### Array Properties
- **Fixed size** (in C++)
- **Contiguous memory** allocation
- **Indexed access** (O(1) time)
- **Same data type** for all elements

### Basic Array Operations

```cpp
#include <iostream>
using namespace std;

int main() {
    // Declaration and initialization
    int numbers[5] = {1, 2, 3, 4, 5};
    
    // Accessing elements
    cout << "First element: " << numbers[0] << endl;  // 1
    cout << "Third element: " << numbers[2] << endl;  // 3
    
    // Modifying elements
    numbers[1] = 10;
    cout << "Modified second element: " << numbers[1] << endl;  // 10
    
    // Iterating through array
    cout << "All elements: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Range-based for loop (C++11)
    cout << "Using range-based for: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Array Operations Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Access | O(1) | Direct access by index |
| Search | O(n) | Linear search through elements |
| Insert | O(n) | Need to shift elements |
| Delete | O(n) | Need to shift elements |
| Update | O(1) | Direct access and modify |

---

## 📈 Vectors (Dynamic Arrays)

### What is a Vector?
A vector is a dynamic array that can grow or shrink in size. It's part of the C++ Standard Template Library (STL).

### Vector Advantages over Arrays
- **Dynamic size** - grows and shrinks automatically
- **Built-in functions** - size, push_back, pop_back, etc.
- **Memory management** - handles allocation automatically
- **STL compatibility** - works with all STL algorithms

### Basic Vector Operations

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Declaration
    vector<int> numbers;
    
    // Adding elements
    numbers.push_back(1);    // Add to end
    numbers.push_back(2);
    numbers.push_back(3);
    
    // Accessing elements
    cout << "First element: " << numbers[0] << endl;      // 1
    cout << "Second element: " << numbers.at(1) << endl;  // 2 (bounds checking)
    
    // Size and capacity
    cout << "Size: " << numbers.size() << endl;           // 3
    cout << "Capacity: " << numbers.capacity() << endl;   // 4 (or more)
    
    // Iterating
    cout << "All elements: ";
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Range-based for loop
    cout << "Range-based for: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Removing elements
    numbers.pop_back();      // Remove last element
    cout << "After pop_back, size: " << numbers.size() << endl;  // 2
    
    return 0;
}
```

### Vector Initialization Methods

```cpp
// Method 1: Empty vector
vector<int> v1;

// Method 2: Size with default value
vector<int> v2(5, 0);  // 5 elements, all 0

// Method 3: Initializer list
vector<int> v3 = {1, 2, 3, 4, 5};

// Method 4: Copy from another vector
vector<int> v4(v3);

// Method 5: From array
int arr[] = {1, 2, 3, 4, 5};
vector<int> v5(arr, arr + 5);
```

### Vector Operations Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Access | O(1) | Direct access by index |
| Search | O(n) | Linear search |
| Insert at end | O(1) amortized | push_back |
| Insert at beginning | O(n) | insert at position 0 |
| Delete from end | O(1) | pop_back |
| Delete from beginning | O(n) | erase first element |

---

## 🔤 Strings

### What is a String?
A string is a sequence of characters. In C++, you can use either C-style character arrays or the STL string class.

### STL String (Recommended)

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Declaration and initialization
    string name = "John Doe";
    string greeting("Hello, ");
    
    // Concatenation
    string message = greeting + name;
    cout << message << endl;  // "Hello, John Doe"
    
    // String length
    cout << "Length of name: " << name.length() << endl;  // 8
    cout << "Size of name: " << name.size() << endl;      // 8
    
    // Accessing characters
    cout << "First character: " << name[0] << endl;       // 'J'
    cout << "Last character: " << name.back() << endl;    // 'e'
    
    // Substring
    string firstName = name.substr(0, 4);  // "John"
    string lastName = name.substr(5);      // "Doe"
    
    cout << "First name: " << firstName << endl;
    cout << "Last name: " << lastName << endl;
    
    // Finding substrings
    size_t pos = name.find("Doe");
    if (pos != string::npos) {
        cout << "'Doe' found at position: " << pos << endl;  // 5
    }
    
    // String comparison
    if (firstName == "John") {
        cout << "First name is John" << endl;
    }
    
    // Iterating through characters
    cout << "Characters: ";
    for (char c : name) {
        cout << c << " ";
    }
    cout << endl;
    
    return 0;
}
```

### String Operations

```cpp
string text = "Hello World";

// Case conversion
transform(text.begin(), text.end(), text.begin(), ::toupper);
cout << text << endl;  // "HELLO WORLD"

transform(text.begin(), text.end(), text.begin(), ::tolower);
cout << text << endl;  // "hello world"

// String replacement
text.replace(0, 5, "Hi");  // Replace "Hello" with "Hi"
cout << text << endl;       // "Hi World"

// String insertion
text.insert(3, " there");   // Insert " there" at position 3
cout << text << endl;       // "Hi there World"

// String erasure
text.erase(3, 6);          // Erase 6 characters starting at position 3
cout << text << endl;       // "Hi World"
```

---

## 🔗 Linked Lists

### What is a Linked List?
A linked list is a data structure where elements are stored in nodes, and each node points to the next node in the sequence.

### Singly Linked List

```cpp
#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
    
    Node(int value) : data(value), next(nullptr) {}
};

// Linked List class
class LinkedList {
private:
    Node* head;
    
public:
    LinkedList() : head(nullptr) {}
    
    // Insert at beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    
    // Insert at end
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
    
    // Display list
    void display() {
        Node* current = head;
        cout << "List: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    // Search element
    bool search(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // Delete element
    void deleteElement(int value) {
        if (head == nullptr) return;
        
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }
        
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
    
    // Destructor to free memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    LinkedList list;
    
    // Insert elements
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtBeginning(0);
    
    // Display list
    list.display();  // List: 0 1 2 3
    
    // Search for element
    cout << "Searching for 2: " << (list.search(2) ? "Found" : "Not found") << endl;
    cout << "Searching for 5: " << (list.search(5) ? "Found" : "Not found") << endl;
    
    // Delete element
    list.deleteElement(2);
    list.display();  // List: 0 1 3
    
    return 0;
}
```

### Linked List Operations Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Access | O(n) | Must traverse from head |
| Search | O(n) | Linear search |
| Insert at beginning | O(1) | Direct insertion |
| Insert at end | O(n) | Must traverse to end |
| Delete | O(n) | Must find element first |

---

## 🧪 Practice Examples

### Example 1: Array Rotation
```cpp
#include <iostream>
#include <vector>
using namespace std;

// Rotate array to the right by k positions
void rotateArray(vector<int>& arr, int k) {
    int n = arr.size();
    k = k % n;  // Handle cases where k > n
    
    // Reverse entire array
    reverse(arr.begin(), arr.end());
    
    // Reverse first k elements
    reverse(arr.begin(), arr.begin() + k);
    
    // Reverse remaining elements
    reverse(arr.begin() + k, arr.end());
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int k = 2;
    
    cout << "Original array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
    
    rotateArray(arr, k);
    
    cout << "After rotating by " << k << " positions: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
    
    return 0;
}
```

### Example 2: Find Missing Number
```cpp
#include <iostream>
#include <vector>
using namespace std;

int findMissingNumber(vector<int>& arr) {
    int n = arr.size();
    int expectedSum = n * (n + 1) / 2;
    
    int actualSum = 0;
    for (int num : arr) {
        actualSum += num;
    }
    
    return expectedSum - actualSum;
}

int main() {
    vector<int> arr = {0, 1, 3, 4, 5};  // Missing 2
    
    cout << "Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
    
    int missing = findMissingNumber(arr);
    cout << "Missing number: " << missing << endl;
    
    return 0;
}
```

### Example 3: Palindrome Check
```cpp
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string str) {
    int left = 0;
    int right = str.length() - 1;
    
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main() {
    string test1 = "racecar";
    string test2 = "hello";
    
    cout << "'" << test1 << "' is palindrome: " << (isPalindrome(test1) ? "Yes" : "No") << endl;
    cout << "'" << test2 << "' is palindrome: " << (isPalindrome(test2) ? "Yes" : "No") << endl;
    
    return 0;
}
```

---

## 📚 What's Next?

After mastering basic data structures, explore:
1. **Stacks & Queues** - LIFO and FIFO data structures
2. **Trees** - Hierarchical data organization
3. **Hash Tables** - Fast key-value storage
4. **Graphs** - Network and relationship modeling

---

## 🔗 Related Topics
- [Introduction to DSA](introduction.md)
- [Time & Space Complexity](complexity-analysis.md)
- [Simple Algorithms](basic-algorithms.md)
- [Control Flow](cpp/control-flow.md)

---

## 💡 Key Takeaways

1. **Arrays** are simple but fixed-size
2. **Vectors** are dynamic and more flexible
3. **Strings** are specialized character containers
4. **Linked Lists** are flexible but slower for random access
5. **Choose the right structure** for your specific needs

---

*"Data structures are not just storage containers; they are the foundation upon which efficient algorithms are built."*
