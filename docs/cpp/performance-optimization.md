# ⚡ C++ Performance Optimization

## 📚 Overview

Performance optimization in C++ involves understanding how the compiler works, memory layout, CPU architecture, and applying various techniques to make your code run faster. This guide covers both low-level optimizations and high-level design principles.

## 🎯 Performance Fundamentals

### What Affects Performance?
- **CPU Cache**: Memory access patterns and cache locality
- **Memory Layout**: Data structure organization and alignment
- **Compiler Optimizations**: How the compiler transforms your code
- **Algorithm Complexity**: Time and space complexity of algorithms
- **System Calls**: Operating system overhead

### Performance Measurement
```cpp
#include <chrono>
#include <iostream>

// High-resolution timing
auto start = std::chrono::high_resolution_clock::now();
// ... your code here ...
auto end = std::chrono::high_resolution_clock::now();

auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
```

## 🔧 Compiler Optimizations

### Understanding Compiler Flags
```bash
# GCC optimization flags
g++ -O0    # No optimization (debug builds)
g++ -O1    # Basic optimizations
g++ -O2    # More aggressive optimizations (recommended for production)
g++ -O3    # Maximum optimization (may increase code size)
g++ -Os    # Optimize for size
g++ -Ofast # Aggressive optimizations (may break standards compliance)

# Additional flags
g++ -march=native    # Optimize for current CPU
g++ -ffast-math      # Fast math operations
g++ -funroll-loops   # Loop unrolling
g++ -flto           # Link-time optimization
```

### Compiler Intrinsics
```cpp
// CPU-specific optimizations
#include <immintrin.h>

// SSE/AVX instructions
void vector_add(float* a, float* b, float* result, size_t n) {
    for (size_t i = 0; i < n; i += 4) {
        __m128 va = _mm_load_ps(&a[i]);
        __m128 vb = _mm_load_ps(&b[i]);
        __m128 vr = _mm_add_ps(va, vb);
        _mm_store_ps(&result[i], vr);
    }
}

// Bit manipulation
int count_set_bits(uint32_t n) {
    return _mm_popcnt_u32(n);  // Use POPCNT instruction
}
```

### Inline Functions
```cpp
// Force inline for performance-critical functions
inline int fast_add(int a, int b) {
    return a + b;
}

// Modern C++ inline
constexpr int constexpr_add(int a, int b) {
    return a + b;
}

// Compiler hints
__attribute__((always_inline)) int always_inline_add(int a, int b) {
    return a + b;
}
```

## 🚀 Memory Optimization

### Cache Locality
```cpp
// ❌ Bad: Poor cache locality
struct bad_layout {
    int id;
    double value;
    char name[100];
    bool active;
};

// ✅ Good: Better cache locality
struct good_layout {
    int id;
    bool active;
    double value;
    char name[100];
};

// Array of structures vs Structure of arrays
// ❌ AoS: Poor cache locality for specific fields
struct person_aos {
    std::string name;
    int age;
    double salary;
};
std::vector<person_aos> people;

// ✅ SoA: Better cache locality for field-based operations
struct people_soa {
    std::vector<std::string> names;
    std::vector<int> ages;
    std::vector<double> salaries;
};
```

### Memory Alignment
```cpp
// Ensure proper alignment for performance
struct aligned_data {
    alignas(64) double values[8];  // Align to cache line
};

// Custom allocator with alignment
template<typename T, size_t Alignment>
class aligned_allocator {
public:
    using value_type = T;
    
    T* allocate(size_t n) {
        return static_cast<T*>(std::aligned_alloc(Alignment, n * sizeof(T)));
    }
    
    void deallocate(T* p, size_t) {
        std::free(p);
    }
};

// Usage
std::vector<double, aligned_allocator<double, 64>> aligned_vector;
```

### Memory Pooling
```cpp
// Efficient allocation for small objects
template<typename T, size_t BlockSize = 1024>
class memory_pool {
private:
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

## ⚡ Algorithm Optimization

### Loop Optimizations
```cpp
// ❌ Bad: Multiple passes
std::vector<int> data = {1, 2, 3, 4, 5};
int sum = 0, min_val = INT_MAX, max_val = INT_MIN;

for (int x : data) sum += x;
for (int x : data) min_val = std::min(min_val, x);
for (int x : data) max_val = std::max(max_val, x);

// ✅ Good: Single pass
int sum = 0, min_val = INT_MAX, max_val = INT_MIN;
for (int x : data) {
    sum += x;
    min_val = std::min(min_val, x);
    max_val = std::max(max_val, x);
}

// Loop unrolling
void unrolled_sum(const int* data, size_t n, int& result) {
    result = 0;
    size_t i = 0;
    
    // Process 4 elements at a time
    for (; i + 3 < n; i += 4) {
        result += data[i] + data[i+1] + data[i+2] + data[i+3];
    }
    
    // Handle remaining elements
    for (; i < n; ++i) {
        result += data[i];
    }
}
```

### Branch Prediction
```cpp
// Help the CPU predict branches
// ❌ Bad: Unpredictable branches
std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int sum_even = 0, sum_odd = 0;

for (int x : data) {
    if (x % 2 == 0) {
        sum_even += x;
    } else {
        sum_odd += x;
    }
}

// ✅ Good: Separate loops for better branch prediction
std::vector<int> even_numbers, odd_numbers;
for (int x : data) {
    if (x % 2 == 0) {
        even_numbers.push_back(x);
    } else {
        odd_numbers.push_back(x);
    }
}

int sum_even = 0, sum_odd = 0;
for (int x : even_numbers) sum_even += x;
for (int x : odd_numbers) sum_odd += x;

// Use likely/unlikely hints
if (__builtin_expect(condition, 1)) {  // Likely true
    // Fast path
} else {
    // Slow path
}
```

### SIMD Optimization
```cpp
// Vectorized operations
#include <immintrin.h>

void vectorized_add(const float* a, const float* b, float* result, size_t n) {
    size_t i = 0;
    
    // Process 8 floats at a time with AVX
    for (; i + 7 < n; i += 8) {
        __m256 va = _mm256_load_ps(&a[i]);
        __m256 vb = _mm256_load_ps(&b[i]);
        __m256 vr = _mm256_add_ps(va, vb);
        _mm256_store_ps(&result[i], vr);
    }
    
    // Handle remaining elements
    for (; i < n; ++i) {
        result[i] = a[i] + b[i];
    }
}

// Auto-vectorization hints
void vectorizable_sum(const int* data, size_t n, int& result) {
    result = 0;
    #pragma omp simd reduction(+:result)
    for (size_t i = 0; i < n; ++i) {
        result += data[i];
    }
}
```

## 🔍 Data Structure Optimization

### Container Selection
```cpp
// Choose the right container for your use case
#include <unordered_map>
#include <map>
#include <vector>

// ✅ Fast lookups, no ordering needed
std::unordered_map<std::string, int> hash_map;

// ✅ Ordered, logarithmic operations
std::map<std::string, int> ordered_map;

// ✅ Fast iteration, random access
std::vector<int> dynamic_array;

// ✅ Fast insertion/deletion at ends
std::deque<int> double_ended_queue;

// ✅ Fast insertion/deletion anywhere
std::list<int> linked_list;
```

### Custom Data Structures
```cpp
// Optimized small vector (no dynamic allocation for small sizes)
template<typename T, size_t N = 16>
class small_vector {
private:
    T* data_ptr;
    size_t size_;
    size_t capacity_;
    T stack_data[N];
    
public:
    small_vector() : data_ptr(stack_data), size_(0), capacity_(N) {}
    
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            grow();
        }
        new (data_ptr + size_) T(value);
        ++size_;
    }
    
    const T& operator[](size_t index) const {
        return data_ptr[index];
    }
    
private:
    void grow() {
        size_t new_capacity = capacity_ * 2;
        T* new_data = new T[new_capacity];
        
        for (size_t i = 0; i < size_; ++i) {
            new (new_data + i) T(std::move(data_ptr[i]));
        }
        
        if (data_ptr != stack_data) {
            delete[] data_ptr;
        }
        
        data_ptr = new_data;
        capacity_ = new_capacity;
    }
};
```

### Bit Manipulation
```cpp
// Efficient bit operations
class bit_set {
private:
    std::vector<uint64_t> data;
    
public:
    bit_set(size_t size) : data((size + 63) / 64) {}
    
    void set(size_t index) {
        data[index / 64] |= (1ULL << (index % 64));
    }
    
    void clear(size_t index) {
        data[index / 64] &= ~(1ULL << (index % 64));
    }
    
    bool test(size_t index) const {
        return (data[index / 64] & (1ULL << (index % 64))) != 0;
    }
    
    // Count set bits efficiently
    size_t count() const {
        size_t total = 0;
        for (uint64_t word : data) {
            total += _mm_popcnt_u64(word);
        }
        return total;
    }
};
```

## 🚀 Concurrency Optimization

### Lock-Free Programming
```cpp
// Lock-free stack
template<typename T>
class lock_free_stack {
private:
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

### Thread Pool
```cpp
class thread_pool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
    
public:
    thread_pool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    
    template<typename F>
    void enqueue(F&& f) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace(std::forward<F>(f));
        }
        condition.notify_one();
    }
    
    ~thread_pool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }
};
```

## 🔧 Profiling and Analysis

### Performance Profiling Tools
```bash
# CPU profiling
perf record ./your_program
perf report

# Memory profiling
valgrind --tool=massif ./your_program
ms_print massif.out.*

# Cache profiling
perf stat -e cache-misses,cache-references ./your_program

# Branch prediction profiling
perf stat -e branch-misses,branches ./your_program
```

### Compiler Explorer
```cpp
// Use godbolt.org to see assembly output
// Example: https://godbolt.org/
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Compare different optimization levels and compilers
```

## 📚 Best Practices

### 1. Measure First
- **Profile your code** before optimizing
- **Identify bottlenecks** using real data
- **Don't optimize prematurely**

### 2. Algorithm First
- **Choose efficient algorithms** over micro-optimizations
- **Understand complexity** of your solutions
- **Use appropriate data structures**

### 3. Compiler-Friendly Code
- **Write clear, simple code** that the compiler can optimize
- **Use const and constexpr** where possible
- **Avoid undefined behavior**

### 4. Cache-Aware Design
- **Structure data** for good cache locality
- **Minimize cache misses** in hot paths
- **Use appropriate container types**

### 5. Modern C++ Features
- **Use move semantics** to avoid copies
- **Prefer algorithms** over raw loops
- **Leverage constexpr** for compile-time computation

## 🚀 Advanced Techniques

### Template Metaprogramming for Performance
```cpp
// Compile-time optimization
template<size_t N>
struct unrolled_sum {
    template<typename Iterator>
    static auto sum(Iterator begin) {
        return *begin + unrolled_sum<N-1>::sum(std::next(begin));
    }
};

template<>
struct unrolled_sum<1> {
    template<typename Iterator>
    static auto sum(Iterator begin) {
        return *begin;
    }
};

// Usage
auto result = unrolled_sum<4>::sum(data.begin());
```

### Custom Memory Allocators
```cpp
// Arena allocator for temporary allocations
class arena_allocator {
private:
    std::vector<std::unique_ptr<char[]>> blocks;
    char* current_block = nullptr;
    size_t current_pos = 0;
    size_t block_size = 4096;
    
public:
    void* allocate(size_t size) {
        if (current_pos + size > block_size) {
            allocate_new_block();
        }
        
        void* result = current_block + current_pos;
        current_pos += size;
        return result;
    }
    
    void reset() {
        current_pos = 0;
        for (auto& block : blocks) {
            current_block = block.get();
            break;
        }
    }
    
private:
    void allocate_new_block() {
        blocks.push_back(std::make_unique<char[]>(block_size));
        current_block = blocks.back().get();
        current_pos = 0;
    }
};
```

## 📖 Resources

### Books
- "Optimized C++" by Kurt Guntheroth
- "Effective C++" by Scott Meyers
- "C++ Performance" by Björn Andrist

### Online Resources
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Compiler Explorer](https://godbolt.org/)
- [Performance Analysis Tools](https://perf.wiki.kernel.org/)

## 🚀 Practice Problems

### Basic Exercises
1. **Profile Analysis**: Profile a simple program and identify bottlenecks
2. **Cache Locality**: Compare AoS vs SoA performance
3. **Loop Optimization**: Optimize nested loops for better performance

### Intermediate Exercises
1. **Custom Allocator**: Implement a pool allocator
2. **SIMD Operations**: Vectorize simple mathematical operations
3. **Lock-Free Data Structures**: Implement a lock-free queue

### Advanced Exercises
1. **Compiler Optimizations**: Analyze assembly output for different optimization levels
2. **Memory Layout**: Design cache-friendly data structures
3. **Performance Profiling**: Build a custom profiling system

---

*Performance optimization is both an art and a science. Start with good algorithms and data structures, then use profiling to identify bottlenecks, and finally apply targeted optimizations. Remember: premature optimization is the root of all evil.*
