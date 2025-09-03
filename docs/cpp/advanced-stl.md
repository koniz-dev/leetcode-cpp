# 🚀 Advanced STL (Standard Template Library)

## 📚 Overview

The Standard Template Library (STL) is a powerful collection of C++ template classes and functions that provide common data structures and algorithms. This guide covers advanced STL techniques, custom allocators, and extending the STL for specialized use cases.

## 🎯 Advanced STL Concepts

### STL Architecture
- **Containers**: Data structure implementations
- **Iterators**: Generic access to container elements
- **Algorithms**: Generic algorithms operating on iterators
- **Allocators**: Memory management for containers
- **Function Objects**: Callable objects for algorithms

### STL Design Principles
- **Generic Programming**: Type-independent algorithms
- **Efficiency**: Zero-overhead abstractions
- **Extensibility**: Custom containers and algorithms
- **Consistency**: Uniform interface across components

## 🔧 Custom Allocators

### Why Custom Allocators?
- **Memory Pooling**: Reduce allocation overhead
- **Specialized Memory**: GPU memory, shared memory
- **Debugging**: Memory leak detection, bounds checking
- **Performance**: Optimize for specific access patterns

### Basic Allocator Interface
```cpp
template<typename T>
class custom_allocator {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;
    
    // Required methods
    T* allocate(size_type n);
    void deallocate(T* p, size_type n);
    
    // Optional methods
    template<typename U, typename... Args>
    void construct(U* p, Args&&... args);
    
    template<typename U>
    void destroy(U* p);
};
```

### Pool Allocator Example
```cpp
template<typename T, size_t BlockSize = 1024>
class pool_allocator {
private:
    struct block {
        block* next;
        char data[BlockSize];
    };
    
    block* free_list = nullptr;
    std::vector<block*> blocks;
    
public:
    using value_type = T;
    
    T* allocate(size_t n) {
        if (n != 1) {
            return static_cast<T*>(::operator new(n * sizeof(T)));
        }
        
        if (!free_list) {
            allocate_block();
        }
        
        T* result = reinterpret_cast<T*>(free_list);
        free_list = free_list->next;
        return result;
    }
    
    void deallocate(T* p, size_t n) {
        if (n != 1) {
            ::operator delete(p);
            return;
        }
        
        block* b = reinterpret_cast<block*>(p);
        b->next = free_list;
        free_list = b;
    }
    
private:
    void allocate_block() {
        block* new_block = new block;
        new_block->next = nullptr;
        blocks.push_back(new_block);
        
        // Initialize free list
        char* data = new_block->data;
        for (size_t i = 0; i < BlockSize - sizeof(T); i += sizeof(T)) {
            block* current = reinterpret_cast<block*>(data + i);
            current->next = free_list;
            free_list = current;
        }
    }
};
```

### Debug Allocator
```cpp
template<typename T>
class debug_allocator {
private:
    std::map<T*, size_t> allocations;
    std::mutex mutex;
    
public:
    using value_type = T;
    
    T* allocate(size_t n) {
        T* p = static_cast<T*>(::operator new(n * sizeof(T)));
        
        std::lock_guard<std::mutex> lock(mutex);
        allocations[p] = n;
        
        std::cout << "Allocated " << n << " elements at " << p << std::endl;
        return p;
    }
    
    void deallocate(T* p, size_t n) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = allocations.find(p);
        if (it != allocations.end()) {
            std::cout << "Deallocated " << it->second << " elements at " << p << std::endl;
            allocations.erase(it);
        }
        
        ::operator delete(p);
    }
    
    ~debug_allocator() {
        if (!allocations.empty()) {
            std::cout << "Memory leak detected! " << allocations.size() 
                      << " allocations not freed." << std::endl;
        }
    }
};
```

## 🚀 Custom Containers

### Extending STL Containers
```cpp
// Custom vector with bounds checking
template<typename T, typename Allocator = std::allocator<T>>
class safe_vector : public std::vector<T, Allocator> {
public:
    using base = std::vector<T, Allocator>;
    using base::base;
    
    T& at(size_t index) {
        if (index >= this->size()) {
            throw std::out_of_range("Index out of bounds: " + std::to_string(index));
        }
        return (*this)[index];
    }
    
    const T& at(size_t index) const {
        if (index >= this->size()) {
            throw std::out_of_range("Index out of bounds: " + std::to_string(index));
        }
        return (*this)[index];
    }
    
    // Safe access with default value
    T get(size_t index, const T& default_value = T{}) const {
        return (index < this->size()) ? (*this)[index] : default_value;
    }
};
```

### Custom Iterator
```cpp
// Iterator that skips null elements
template<typename Container>
class skip_null_iterator {
private:
    using iterator_type = typename Container::iterator;
    iterator_type current;
    iterator_type end;
    
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename Container::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = typename Container::pointer;
    using reference = typename Container::reference;
    
    skip_null_iterator(iterator_type begin, iterator_type end) 
        : current(begin), end(end) {
        skip_nulls();
    }
    
    skip_null_iterator& operator++() {
        ++current;
        skip_nulls();
        return *this;
    }
    
    skip_null_iterator operator++(int) {
        skip_null_iterator temp = *this;
        ++(*this);
        return temp;
    }
    
    reference operator*() { return *current; }
    pointer operator->() { return &(*current); }
    
    bool operator==(const skip_null_iterator& other) const {
        return current == other.current;
    }
    
    bool operator!=(const skip_null_iterator& other) const {
        return !(*this == other);
    }
    
private:
    void skip_nulls() {
        while (current != end && !*current) {
            ++current;
        }
    }
};
```

### Custom Algorithm
```cpp
// Parallel for_each with thread pool
template<typename InputIt, typename UnaryFunction>
void parallel_for_each(InputIt first, InputIt last, UnaryFunction f, 
                      size_t num_threads = std::thread::hardware_concurrency()) {
    auto distance = std::distance(first, last);
    if (distance == 0) return;
    
    size_t chunk_size = (distance + num_threads - 1) / num_threads;
    std::vector<std::thread> threads;
    
    for (size_t i = 0; i < num_threads; ++i) {
        auto start = std::next(first, i * chunk_size);
        auto end = (i == num_threads - 1) ? last : std::next(first, (i + 1) * chunk_size);
        
        threads.emplace_back([start, end, &f]() {
            std::for_each(start, end, f);
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
}
```

## 🎨 Advanced STL Techniques

### Type Erasure with STL
```cpp
// Polymorphic container using type erasure
class drawable {
    struct concept {
        virtual ~concept() = default;
        virtual void draw() const = 0;
        virtual std::unique_ptr<concept> clone() const = 0;
    };
    
    template<typename T>
    struct model : concept {
        T data;
        model(T x) : data(std::move(x)) {}
        
        void draw() const override { data.draw(); }
        std::unique_ptr<concept> clone() const override {
            return std::make_unique<model>(data);
        }
    };
    
    std::unique_ptr<concept> pimpl;
    
public:
    template<typename T>
    drawable(T&& obj) : pimpl(std::make_unique<model<T>>(std::forward<T>(obj))) {}
    
    drawable(const drawable& other) : pimpl(other.pimpl->clone()) {}
    drawable& operator=(const drawable& other) {
        pimpl = other.pimpl->clone();
        return *this;
    }
    
    void draw() const { pimpl->draw(); }
};

// Usage
std::vector<drawable> shapes;
shapes.emplace_back(circle{5.0});
shapes.emplace_back(rectangle{3.0, 4.0});
shapes.emplace_back(triangle{1.0, 2.0, 3.0});

for (const auto& shape : shapes) {
    shape.draw();
}
```

### STL with Concepts (C++20)
```cpp
// Custom concept for sortable types
template<typename T>
concept Sortable = requires(T& t) {
    { t.begin() } -> std::input_iterator;
    { t.end() } -> std::input_iterator;
    requires std::totally_ordered<typename T::value_type>;
};

// Algorithm that works with any sortable container
template<Sortable Container>
void sort_container(Container& c) {
    std::sort(c.begin(), c.end());
}

// Usage
std::vector<int> v = {3, 1, 4, 1, 5, 9};
std::list<double> l = {3.14, 2.71, 1.41};
sort_container(v);  // OK
sort_container(l);  // OK
```

### STL with Ranges (C++20)
```cpp
#include <ranges>

// Modern range-based algorithms
auto numbers = std::views::iota(1, 101);
auto even_squares = numbers 
    | std::views::filter([](int n) { return n % 2 == 0; })
    | std::views::transform([](int n) { return n * n; })
    | std::views::take(10);

for (int n : even_squares) {
    std::cout << n << " ";  // 4 16 36 64 100 144 196 256 324 400
}
```

## 🔍 STL Internals and Optimization

### Container Memory Layout
```cpp
// Understanding vector memory layout
template<typename T>
void analyze_vector(const std::vector<T>& vec) {
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Data pointer: " << vec.data() << std::endl;
    std::cout << "Memory usage: " << vec.capacity() * sizeof(T) << " bytes" << std::endl;
}
```

### Iterator Invalidation
```cpp
// Common iterator invalidation scenarios
void demonstrate_invalidation() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    
    // ❌ Invalid: iterator becomes invalid after push_back
    auto it = v.begin();
    v.push_back(6);
    // *it;  // Undefined behavior!
    
    // ✅ Valid: use indices instead
    size_t index = 0;
    v.push_back(6);
    int value = v[index];  // Safe
    
    // ✅ Valid: refresh iterator after modification
    it = v.begin();
    v.push_back(7);
    it = v.begin();  // Refresh iterator
    *it;  // Safe
}
```

### STL Performance Tips
```cpp
// Reserve capacity to avoid reallocation
std::vector<int> v;
v.reserve(1000);  // Pre-allocate space
for (int i = 0; i < 1000; ++i) {
    v.push_back(i);  // No reallocation
}

// Use emplace_back for efficiency
std::vector<std::string> strings;
strings.emplace_back("hello");  // Constructs in-place
strings.push_back("world");     // Creates temporary, then copies

// Avoid unnecessary copies
std::vector<std::string> data;
// ❌ Bad: copies string
for (const std::string& item : data) { /* ... */ }
// ✅ Good: no copy
for (const auto& item : data) { /* ... */ }
```

## 🛠️ Custom STL Extensions

### Custom Hash Function
```cpp
// Custom hash for user-defined types
struct point {
    int x, y;
    
    bool operator==(const point& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template<>
    struct hash<point> {
        size_t operator()(const point& p) const {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };
}

// Usage
std::unordered_set<point> points;
points.insert({1, 2});
points.insert({3, 4});
```

### Custom Comparator
```cpp
// Case-insensitive string comparator
struct case_insensitive_less {
    bool operator()(const std::string& a, const std::string& b) const {
        return std::lexicographical_compare(
            a.begin(), a.end(), b.begin(), b.end(),
            [](char c1, char c2) {
                return std::tolower(c1) < std::tolower(c2);
            }
        );
    }
};

// Usage
std::map<std::string, int, case_insensitive_less> word_count;
word_count["Hello"] = 1;
word_count["hello"] = 2;  // Overwrites "Hello"
```

### STL Adapter
```cpp
// Adapter to make any container work like a stack
template<typename Container>
class stack_adapter {
    Container c;
    
public:
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    
    void push(const value_type& value) { c.push_back(value); }
    void pop() { c.pop_back(); }
    value_type& top() { return c.back(); }
    const value_type& top() const { return c.back(); }
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
};

// Usage
stack_adapter<std::vector<int>> stack;
stack.push(1);
stack.push(2);
stack.push(3);
while (!stack.empty()) {
    std::cout << stack.top() << " ";
    stack.pop();
}  // Output: 3 2 1
```

## 📚 Advanced STL Patterns

### Policy-Based Design
```cpp
// Container with configurable policies
template<typename T, 
         typename Allocator = std::allocator<T>,
         typename GrowthPolicy = exponential_growth,
         typename ThreadingPolicy = single_threaded>
class smart_vector {
    // Implementation using policies
};

// Usage
smart_vector<int, std::allocator<int>, linear_growth, multi_threaded> v;
```

### CRTP with STL
```cpp
// Curiously Recurring Template Pattern for STL extension
template<typename Derived>
class stl_extension {
public:
    template<typename Container>
    auto find_and_replace(Container& c, 
                         const typename Container::value_type& old_val,
                         const typename Container::value_type& new_val) {
        return static_cast<Derived*>(this)->find_and_replace_impl(c, old_val, new_val);
    }
};

class vector_utils : public stl_extension<vector_utils> {
public:
    template<typename T, typename Alloc>
    auto find_and_replace_impl(std::vector<T, Alloc>& v, const T& old_val, const T& new_val) {
        std::replace(v.begin(), v.end(), old_val, new_val);
        return v;
    }
};
```

## 🚀 Performance Optimization

### Memory Pooling
```cpp
// Efficient memory pool for small objects
template<typename T, size_t BlockSize = 1024>
class memory_pool {
    struct block {
        block* next;
        char data[BlockSize];
    };
    
    block* free_list = nullptr;
    std::vector<block*> blocks;
    
public:
    T* allocate() {
        if (!free_list) {
            allocate_block();
        }
        
        T* result = reinterpret_cast<T*>(free_list);
        free_list = free_list->next;
        return result;
    }
    
    void deallocate(T* p) {
        block* b = reinterpret_cast<block*>(p);
        b->next = free_list;
        free_list = b;
    }
    
private:
    void allocate_block() {
        block* new_block = new block;
        new_block->next = nullptr;
        blocks.push_back(new_block);
        
        char* data = new_block->data;
        for (size_t i = 0; i < BlockSize - sizeof(T); i += sizeof(T)) {
            block* current = reinterpret_cast<block*>(data + i);
            current->next = free_list;
            free_list = current;
        }
    }
};
```

### Lock-Free Containers
```cpp
// Simple lock-free stack
template<typename T>
class lock_free_stack {
    struct node {
        T data;
        node* next;
        node(const T& d) : data(d), next(nullptr) {}
    };
    
    std::atomic<node*> head;
    
public:
    void push(const T& data) {
        node* new_node = new node(data);
        node* old_head = head.load();
        do {
            new_node->next = old_head;
        } while (!head.compare_exchange_weak(old_head, new_node));
    }
    
    bool pop(T& result) {
        node* old_head = head.load();
        do {
            if (!old_head) return false;
        } while (!head.compare_exchange_weak(old_head, old_head->next));
        
        result = old_head->data;
        delete old_head;
        return true;
    }
};
```

## 📖 Resources

### Books
- "Effective STL" by Scott Meyers
- "The C++ Standard Library" by Nicolai Josuttis
- "C++ Concurrency in Action" by Anthony Williams

### Online Resources
- [cppreference.com](https://en.cppreference.com/w/cpp/container)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [STL Documentation](https://en.cppreference.com/w/cpp/algorithm)

## 🚀 Practice Problems

### Basic Exercises
1. **Custom Allocator**: Implement a simple pool allocator
2. **Container Extension**: Add bounds checking to std::vector
3. **Custom Iterator**: Create an iterator that skips certain elements

### Intermediate Exercises
1. **Type Erasure**: Implement polymorphic containers
2. **Custom Algorithms**: Create parallel versions of STL algorithms
3. **STL Adapters**: Build adapters for different container types

### Advanced Exercises
1. **Lock-Free Containers**: Implement thread-safe containers
2. **Memory Pools**: Create efficient memory management systems
3. **STL Extensions**: Build domain-specific STL components

---

*Advanced STL usage allows you to create highly efficient, customizable, and extensible data structures and algorithms. Master these techniques to build robust and performant C++ applications.*
