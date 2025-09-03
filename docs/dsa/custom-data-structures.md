# 🏗️ Custom Data Structures

## 📚 Overview

Custom data structures are specialized implementations designed for specific use cases, performance requirements, or domain-specific needs. This guide covers how to design, implement, and optimize custom data structures that go beyond standard library offerings.

## 🎯 Why Build Custom Data Structures?

### Performance Requirements
- **Specialized access patterns** for specific algorithms
- **Memory layout optimization** for cache performance
- **Reduced overhead** compared to generic solutions
- **Domain-specific optimizations**

### Functional Requirements
- **Unique operations** not supported by standard structures
- **Specialized constraints** (e.g., persistence, concurrency)
- **Integration requirements** with existing systems
- **Research and experimentation**

## 🔧 Design Principles

### Interface Design
```cpp
// Example: Custom container interface
template<typename T>
class custom_container {
public:
    // Type definitions
    using value_type = T;
    using size_type = size_t;
    using iterator = custom_iterator<T>;
    using const_iterator = custom_const_iterator<T>;
    
    // Core operations
    virtual void insert(const T& value) = 0;
    virtual bool remove(const T& value) = 0;
    virtual bool contains(const T& value) const = 0;
    virtual size_type size() const = 0;
    virtual bool empty() const = 0;
    
    // Iteration
    virtual iterator begin() = 0;
    virtual iterator end() = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    
    // Virtual destructor for inheritance
    virtual ~custom_container() = default;
};
```

### Memory Management
```cpp
// Custom allocator for specific use cases
template<typename T, size_t BlockSize = 1024>
class block_allocator {
private:
    struct block {
        block* next;
        char data[BlockSize];
    };
    
    block* free_list = nullptr;
    std::vector<block*> blocks;
    
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    
    T* allocate(size_type n) {
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
    
    void deallocate(T* p, size_type n) {
        if (n != 1) {
            ::operator delete(p);
            return;
        }
        
        block* b = reinterpret_cast<block*>(p);
        b->next = free_list;
        free_list = b;
    }
    
    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new(p) U(std::forward<Args>(args)...);
    }
    
    template<typename U>
    void destroy(U* p) {
        p->~U();
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
    
public:
    ~block_allocator() {
        for (block* b : blocks) {
            delete b;
        }
    }
};
```

## 🚀 Specialized Data Structures

### Cache-Optimized Array
```cpp
template<typename T, size_t CacheLineSize = 64>
class cache_optimized_array {
private:
    struct alignas(CacheLineSize) cache_line {
        T data[CacheLineSize / sizeof(T)];
    };
    
    std::vector<cache_line> lines;
    size_t size_;
    
public:
    cache_optimized_array(size_t n) : size_(n) {
        size_t num_lines = (n + (CacheLineSize / sizeof(T)) - 1) / (CacheLineSize / sizeof(T));
        lines.resize(num_lines);
    }
    
    T& operator[](size_t index) {
        size_t line_index = index / (CacheLineSize / sizeof(T));
        size_t offset = index % (CacheLineSize / sizeof(T));
        return lines[line_index].data[offset];
    }
    
    const T& operator[](size_t index) const {
        size_t line_index = index / (CacheLineSize / sizeof(T));
        size_t offset = index % (CacheLineSize / sizeof(T));
        return lines[line_index].data[offset];
    }
    
    size_t size() const { return size_; }
    
    // Cache-friendly iteration
    template<typename Func>
    void for_each_cache_line(Func func) {
        for (auto& line : lines) {
            for (size_t i = 0; i < CacheLineSize / sizeof(T); ++i) {
                func(line.data[i]);
            }
        }
    }
};
```

### Persistent Data Structure
```cpp
template<typename T>
class persistent_vector {
private:
    struct node {
        T data;
        std::shared_ptr<node> left, right;
        size_t size;
        
        node(const T& d, std::shared_ptr<node> l, std::shared_ptr<node> r, size_t s)
            : data(d), left(l), right(r), size(s) {}
    };
    
    std::shared_ptr<node> root;
    size_t size_;
    
public:
    persistent_vector() : root(nullptr), size_(0) {}
    
    persistent_vector push_back(const T& value) const {
        if (!root) {
            return persistent_vector(std::make_shared<node>(value, nullptr, nullptr, 1), 1);
        }
        
        auto new_root = push_back_recursive(root, value, 0, size_);
        return persistent_vector(new_root, size_ + 1);
    }
    
    T operator[](size_t index) const {
        return get_recursive(root, index, 0, size_);
    }
    
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    
private:
    persistent_vector(std::shared_ptr<node> r, size_t s) : root(r), size_(s) {}
    
    std::shared_ptr<node> push_back_recursive(std::shared_ptr<node> current, 
                                             const T& value, 
                                             size_t start, 
                                             size_t end) {
        if (start == end - 1) {
            // Leaf node
            return std::make_shared<node>(value, nullptr, nullptr, 1);
        }
        
        size_t mid = start + (end - start) / 2;
        if (start < mid) {
            auto new_left = push_back_recursive(current->left, value, start, mid);
            return std::make_shared<node>(current->data, new_left, current->right, end - start);
        } else {
            auto new_right = push_back_recursive(current->right, value, mid, end);
            return std::make_shared<node>(current->data, current->left, new_right, end - start);
        }
    }
    
    T get_recursive(std::shared_ptr<node> current, 
                   size_t index, 
                   size_t start, 
                   size_t end) const {
        if (start == end - 1) {
            return current->data;
        }
        
        size_t mid = start + (end - start) / 2;
        if (index < mid) {
            return get_recursive(current->left, index, start, mid);
        } else {
            return get_recursive(current->right, index, mid, end);
        }
    }
};
```

### Lock-Free Skip List
```cpp
#include <atomic>
#include <random>
#include <memory>

template<typename T>
class lock_free_skip_list {
private:
    struct node {
        T data;
        std::atomic<node*> next;
        std::atomic<node*> down;
        int level;
        
        node(const T& d, int l) : data(d), next(nullptr), down(nullptr), level(l) {}
    };
    
    std::atomic<node*> head;
    int max_level;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
    
public:
    lock_free_skip_list(int max_l = 16) : max_level(max_l), gen(rd()) {
        head = new node(T{}, max_level);
    }
    
    void insert(const T& value) {
        int level = random_level();
        std::vector<node*> update(max_level + 1);
        std::vector<node*> current(max_level + 1);
        
        // Find insertion points at each level
        node* curr = head.load();
        for (int i = max_level; i >= 0; --i) {
            while (true) {
                node* next = curr->next.load();
                if (next && next->data < value) {
                    curr = next;
                } else {
                    update[i] = curr;
                    current[i] = curr;
                    break;
                }
            }
        }
        
        // Create new node
        auto new_node = new node(value, level);
        
        // Insert at each level
        for (int i = 0; i <= level; ++i) {
            do {
                new_node->next.store(current[i]->next.load());
            } while (!current[i]->next.compare_exchange_weak(new_node->next, new_node));
        }
    }
    
    bool contains(const T& value) const {
        node* curr = head.load();
        
        for (int i = max_level; i >= 0; --i) {
            while (true) {
                node* next = curr->next.load();
                if (next && next->data < value) {
                    curr = next;
                } else {
                    break;
                }
            }
        }
        
        curr = curr->next.load();
        return curr && curr->data == value;
    }
    
    bool remove(const T& value) {
        std::vector<node*> update(max_level + 1);
        std::vector<node*> current(max_level + 1);
        
        // Find deletion points
        node* curr = head.load();
        for (int i = max_level; i >= 0; --i) {
            while (true) {
                node* next = curr->next.load();
                if (next && next->data < value) {
                    curr = next;
                } else {
                    update[i] = curr;
                    current[i] = curr;
                    break;
                }
            }
        }
        
        curr = curr->next.load();
        if (!curr || curr->data != value) {
            return false;
        }
        
        // Remove at each level
        for (int i = 0; i <= curr->level; ++i) {
            while (!update[i]->next.compare_exchange_weak(current[i], curr->next.load())) {
                // Retry if CAS fails
            }
        }
        
        delete curr;
        return true;
    }
    
private:
    int random_level() {
        int level = 0;
        while (dis(gen) < 0.5 && level < max_level) {
            ++level;
        }
        return level;
    }
    
public:
    ~lock_free_skip_list() {
        // Simplified cleanup
        node* curr = head.load();
        while (curr) {
            node* next = curr->next.load();
            delete curr;
            curr = next;
        }
    }
};
```

## 🔍 Domain-Specific Structures

### Spatial Data Structure (Octree)
```cpp
#include <vector>
#include <memory>

template<typename T>
class octree {
private:
    struct bounds {
        double x_min, y_min, z_min;
        double x_max, y_max, z_max;
        
        bounds(double x1, double y1, double z1, double x2, double y2, double z2)
            : x_min(x1), y_min(y1), z_min(z1), x_max(x2), y_max(y2), z_max(z2) {}
        
        bool contains(double x, double y, double z) const {
            return x >= x_min && x <= x_max && 
                   y >= y_min && y <= y_max && 
                   z >= z_min && z <= z_max;
        }
        
        bool intersects(const bounds& other) const {
            return !(x_max < other.x_min || x_min > other.x_max ||
                     y_max < other.y_min || y_min > other.y_max ||
                     z_max < other.z_min || z_min > other.z_max);
        }
    };
    
    struct octree_node {
        bounds boundary;
        std::vector<std::pair<std::tuple<double, double, double>, T>> objects;
        std::array<std::unique_ptr<octree_node>, 8> children;
        bool is_leaf;
        
        octree_node(const bounds& b) : boundary(b), is_leaf(true) {}
    };
    
    std::unique_ptr<octree_node> root;
    size_t max_objects_per_node;
    int max_depth;
    
public:
    octree(const bounds& boundary, size_t max_objects = 10, int max_d = 8)
        : max_objects_per_node(max_objects), max_depth(max_d) {
        root = std::make_unique<octree_node>(boundary);
    }
    
    void insert(double x, double y, double z, const T& object) {
        insert_recursive(root.get(), x, y, z, object, 0);
    }
    
    std::vector<T> query_range(const bounds& query_bounds) const {
        std::vector<T> result;
        query_range_recursive(root.get(), query_bounds, result);
        return result;
    }
    
    std::vector<T> query_point(double x, double y, double z) const {
        bounds point_bounds(x, y, z, x, y, z);
        return query_range(point_bounds);
    }
    
private:
    void insert_recursive(octree_node* node, double x, double y, double z, 
                         const T& object, int depth) {
        if (!node->boundary.contains(x, y, z)) {
            return;
        }
        
        if (node->is_leaf) {
            if (node->objects.size() < max_objects_per_node || depth >= max_depth) {
                node->objects.emplace_back(std::make_tuple(x, y, z), object);
                return;
            }
            
            // Split node
            split_node(node, depth);
        }
        
        // Insert into appropriate child
        int child_index = get_child_index(node->boundary, x, y, z);
        insert_recursive(node->children[child_index].get(), x, y, z, object, depth + 1);
    }
    
    void split_node(octree_node* node, int depth) {
        double x_mid = (node->boundary.x_min + node->boundary.x_max) / 2;
        double y_mid = (node->boundary.y_min + node->boundary.y_max) / 2;
        double z_mid = (node->boundary.z_min + node->boundary.z_max) / 2;
        
        // Create 8 children
        node->children[0] = std::make_unique<octree_node>(
            bounds(node->boundary.x_min, node->boundary.y_min, node->boundary.z_min, 
                   x_mid, y_mid, z_mid));
        node->children[1] = std::make_unique<octree_node>(
            bounds(x_mid, node->boundary.y_min, node->boundary.z_min, 
                   node->boundary.x_max, y_mid, z_mid));
        node->children[2] = std::make_unique<octree_node>(
            bounds(node->boundary.x_min, y_mid, node->boundary.z_min, 
                   x_mid, node->boundary.y_max, z_mid));
        node->children[3] = std::make_unique<octree_node>(
            bounds(x_mid, y_mid, node->boundary.z_min, 
                   node->boundary.x_max, node->boundary.y_max, z_mid));
        node->children[4] = std::make_unique<octree_node>(
            bounds(node->boundary.x_min, node->boundary.y_min, z_mid, 
                   x_mid, y_mid, node->boundary.z_max));
        node->children[5] = std::make_unique<octree_node>(
            bounds(x_mid, node->boundary.y_min, z_mid, 
                   node->boundary.x_max, y_mid, node->boundary.z_max));
        node->children[6] = std::make_unique<octree_node>(
            bounds(node->boundary.x_min, y_mid, z_mid, 
                   x_mid, node->boundary.y_max, node->boundary.z_max));
        node->children[7] = std::make_unique<octree_node>(
            bounds(x_mid, y_mid, z_mid, 
                   node->boundary.x_max, node->boundary.y_max, node->boundary.z_max));
        
        // Redistribute objects to children
        for (const auto& obj : node->objects) {
            int child_index = get_child_index(node->boundary, 
                                            std::get<0>(obj.first), 
                                            std::get<1>(obj.first), 
                                            std::get<2>(obj.first));
            node->children[child_index]->objects.push_back(obj);
        }
        
        node->objects.clear();
        node->is_leaf = false;
    }
    
    int get_child_index(const bounds& boundary, double x, double y, double z) {
        double x_mid = (boundary.x_min + boundary.x_max) / 2;
        double y_mid = (boundary.y_min + boundary.y_max) / 2;
        double z_mid = (boundary.z_min + boundary.z_max) / 2;
        
        int index = 0;
        if (x >= x_mid) index |= 1;
        if (y >= y_mid) index |= 2;
        if (z >= z_mid) index |= 4;
        
        return index;
    }
    
    void query_range_recursive(const octree_node* node, const bounds& query_bounds, 
                              std::vector<T>& result) const {
        if (!node->boundary.intersects(query_bounds)) {
            return;
        }
        
        if (node->is_leaf) {
            for (const auto& obj : node->objects) {
                double x = std::get<0>(obj.first);
                double y = std::get<1>(obj.first);
                double z = std::get<2>(obj.first);
                
                if (query_bounds.contains(x, y, z)) {
                    result.push_back(obj.second);
                }
            }
        } else {
            for (const auto& child : node->children) {
                if (child) {
                    query_range_recursive(child.get(), query_bounds, result);
                }
            }
        }
    }
};
```

### Bloom Filter
```cpp
#include <vector>
#include <functional>
#include <random>

template<typename T>
class bloom_filter {
private:
    std::vector<bool> bits;
    size_t num_bits;
    size_t num_hashes;
    std::vector<std::function<size_t(const T&)>> hash_functions;
    
public:
    bloom_filter(size_t n_bits, size_t n_hashes) 
        : num_bits(n_bits), num_hashes(n_hashes) {
        bits.resize(n_bits, false);
        generate_hash_functions();
    }
    
    void insert(const T& item) {
        for (const auto& hash_func : hash_functions) {
            size_t index = hash_func(item) % num_bits;
            bits[index] = true;
        }
    }
    
    bool contains(const T& item) const {
        for (const auto& hash_func : hash_functions) {
            size_t index = hash_func(item) % num_bits;
            if (!bits[index]) {
                return false;
            }
        }
        return true;
    }
    
    double false_positive_rate() const {
        // Estimate false positive rate
        size_t set_bits = 0;
        for (bool bit : bits) {
            if (bit) ++set_bits;
        }
        
        double p = static_cast<double>(set_bits) / num_bits;
        return std::pow(p, num_hashes);
    }
    
private:
    void generate_hash_functions() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(1, 1000000);
        
        for (size_t i = 0; i < num_hashes; ++i) {
            size_t seed = dis(gen);
            hash_functions.emplace_back([seed](const T& item) {
                return std::hash<std::string>{}(std::to_string(seed) + std::to_string(std::hash<T>{}(item)));
            });
        }
    }
};
```

## 🔧 Performance Optimization

### Memory Layout Optimization
```cpp
// Structure of Arrays (SoA) for better cache performance
template<typename T>
class soa_vector {
private:
    std::vector<T> data;
    std::vector<size_t> indices;
    
public:
    void push_back(const T& value) {
        data.push_back(value);
        indices.push_back(data.size() - 1);
    }
    
    // Cache-friendly iteration
    template<typename Func>
    void iterate_cache_friendly(Func func) {
        for (size_t i = 0; i < indices.size(); ++i) {
            func(data[indices[i]]);
        }
    }
    
    // Sort indices for better cache locality
    void optimize_for_access() {
        std::sort(indices.begin(), indices.end());
    }
};

// Array of Structures (AoS) for object-oriented design
template<typename T>
class aos_vector {
private:
    std::vector<T> data;
    
public:
    void push_back(const T& value) {
        data.push_back(value);
    }
    
    // Object-oriented iteration
    template<typename Func>
    void iterate_object_oriented(Func func) {
        for (auto& item : data) {
            func(item);
        }
    }
};
```

### Custom Iterator Implementation
```cpp
template<typename Container>
class cache_optimized_iterator {
private:
    using container_type = Container;
    using value_type = typename Container::value_type;
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    
    Container* container;
    size_t index;
    
public:
    cache_optimized_iterator(Container* c, size_t i) : container(c), index(i) {}
    
    reference operator*() { return (*container)[index]; }
    pointer operator->() { return &(*container)[index]; }
    
    cache_optimized_iterator& operator++() { ++index; return *this; }
    cache_optimized_iterator operator++(int) { 
        cache_optimized_iterator temp = *this; ++index; return temp; 
    }
    
    cache_optimized_iterator& operator--() { --index; return *this; }
    cache_optimized_iterator operator--(int) { 
        cache_optimized_iterator temp = *this; --index; return temp; 
    }
    
    cache_optimized_iterator& operator+=(difference_type n) { index += n; return *this; }
    cache_optimized_iterator& operator-=(difference_type n) { index -= n; return *this; }
    
    cache_optimized_iterator operator+(difference_type n) const {
        return cache_optimized_iterator(container, index + n);
    }
    
    cache_optimized_iterator operator-(difference_type n) const {
        return cache_optimized_iterator(container, index - n);
    }
    
    difference_type operator-(const cache_optimized_iterator& other) const {
        return static_cast<difference_type>(index - other.index);
    }
    
    reference operator[](difference_type n) { return (*container)[index + n]; }
    
    bool operator==(const cache_optimized_iterator& other) const {
        return container == other.container && index == other.index;
    }
    
    bool operator!=(const cache_optimized_iterator& other) const {
        return !(*this == other);
    }
    
    bool operator<(const cache_optimized_iterator& other) const {
        return index < other.index;
    }
    
    bool operator<=(const cache_optimized_iterator& other) const {
        return index <= other.index;
    }
    
    bool operator>(const cache_optimized_iterator& other) const {
        return index > other.index;
    }
    
    bool operator>=(const cache_optimized_iterator& other) const {
        return index >= other.index;
    }
};
```

## 📚 Best Practices

### 1. Design Principles
- **Start with clear requirements** and use cases
- **Design for performance** from the beginning
- **Consider memory layout** and cache behavior
- **Plan for extensibility** and maintenance

### 2. Implementation Guidelines
- **Use RAII** for resource management
- **Implement proper iterators** for STL compatibility
- **Handle edge cases** and error conditions
- **Profile and optimize** critical paths

### 3. Testing and Validation
- **Unit test** all operations thoroughly
- **Performance benchmark** against alternatives
- **Stress test** with large datasets
- **Validate correctness** with formal methods when possible

## 📖 Resources

### Books
- "Data Structures and Algorithm Analysis" by Mark Allen Weiss
- "Advanced Data Structures" by Peter Brass
- "The Art of Computer Programming, Volume 1" by Donald Knuth

### Online Resources
- [Custom Data Structures](https://github.com/topics/data-structures)
- [Performance Optimization](https://en.cppreference.com/w/cpp/language/alignas)
- [Memory Layout](https://en.cppreference.com/w/cpp/language/memory_model)

## 🚀 Practice Problems

### Basic Exercises
1. **Custom Vector**: Implement vector with custom allocator
2. **Specialized Container**: Build container for specific data type
3. **Memory Pool**: Create simple memory pool allocator

### Intermediate Exercises
1. **Persistent Structure**: Implement persistent data structure
2. **Spatial Index**: Build spatial data structure (quadtree/octree)
3. **Lock-Free Structure**: Design lock-free data structure

### Advanced Exercises
1. **Domain-Specific Structure**: Design structure for specific domain
2. **Performance Optimization**: Optimize existing structure for performance
3. **Research Structure**: Implement novel data structure from research

---

*Custom data structures give you the power to solve specific problems with optimal performance. Start with simple optimizations and gradually build more complex structures. Remember: the best data structure is the one that fits your specific use case.*
