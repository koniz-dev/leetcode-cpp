# 🛠️ Custom STL Implementation

## 📚 Overview

Building custom STL implementations is the ultimate test of C++ mastery. It requires deep understanding of templates, memory management, algorithms, and design principles. This guide covers how to implement core STL components from scratch, providing insights into the internals of the standard library.

## 🎯 Why Implement Custom STL?

### Learning Benefits
- **Deep Understanding**: Learn how STL actually works internally
- **Template Mastery**: Master advanced template techniques
- **Memory Management**: Understand allocation strategies
- **Algorithm Design**: Learn efficient algorithm implementations
- **Performance Optimization**: Discover optimization techniques

### Practical Applications
- **Embedded Systems**: Custom allocators for constrained environments
- **Game Development**: Specialized containers for performance
- **Domain-Specific**: Containers tailored to specific use cases
- **Educational**: Teaching STL concepts through implementation

## 🔧 Core STL Components

### Iterator Framework
```cpp
// Iterator tags
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// Iterator traits
template<typename Iterator>
struct iterator_traits {
    using iterator_category = typename Iterator::iterator_category;
    using value_type = typename Iterator::value_type;
    using difference_type = typename Iterator::difference_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
};

// Specialization for pointers
template<typename T>
struct iterator_traits<T*> {
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
};
```

### Basic Iterator Implementation
```cpp
// Forward iterator for singly linked list
template<typename T>
class forward_iterator {
private:
    struct node {
        T data;
        node* next;
        node(const T& d, node* n = nullptr) : data(d), next(n) {}
    };
    
    node* current;
    
public:
    using iterator_category = forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    
    forward_iterator(node* n = nullptr) : current(n) {}
    
    reference operator*() { return current->data; }
    pointer operator->() { return &(current->data); }
    
    forward_iterator& operator++() {
        current = current->next;
        return *this;
    }
    
    forward_iterator operator++(int) {
        forward_iterator temp = *this;
        ++(*this);
        return temp;
    }
    
    bool operator==(const forward_iterator& other) const {
        return current == other.current;
    }
    
    bool operator!=(const forward_iterator& other) const {
        return !(*this == other);
    }
};
```

## 🚀 Custom Vector Implementation

### Basic Vector Structure
```cpp
template<typename T, typename Allocator = std::allocator<T>>
class custom_vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    Allocator alloc_;
    
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
    // Constructors
    custom_vector() : data_(nullptr), size_(0), capacity_(0) {}
    
    explicit custom_vector(size_type count, const T& value = T{}) 
        : size_(count), capacity_(count) {
        data_ = alloc_.allocate(count);
        for (size_type i = 0; i < count; ++i) {
            alloc_.construct(data_ + i, value);
        }
    }
    
    custom_vector(const custom_vector& other) 
        : size_(other.size_), capacity_(other.size_) {
        data_ = alloc_.allocate(size_);
        for (size_type i = 0; i < size_; ++i) {
            alloc_.construct(data_ + i, other.data_[i]);
        }
    }
    
    // Destructor
    ~custom_vector() {
        clear();
        if (data_) {
            alloc_.deallocate(data_, capacity_);
        }
    }
    
    // Assignment
    custom_vector& operator=(const custom_vector& other) {
        if (this != &other) {
            custom_vector temp(other);
            swap(temp);
        }
        return *this;
    }
    
    // Element access
    reference operator[](size_type index) { return data_[index]; }
    const_reference operator[](size_type index) const { return data_[index]; }
    
    reference at(size_type index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }
    
    reference front() { return data_[0]; }
    const_reference front() const { return data_[0]; }
    
    reference back() { return data_[size_ - 1]; }
    const_reference back() const { return data_[size_ - 1]; }
    
    // Capacity
    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }
    size_type capacity() const { return capacity_; }
    
    void reserve(size_type new_capacity) {
        if (new_capacity > capacity_) {
            T* new_data = alloc_.allocate(new_capacity);
            for (size_type i = 0; i < size_; ++i) {
                alloc_.construct(new_data + i, std::move(data_[i]));
            }
            
            for (size_type i = 0; i < size_; ++i) {
                alloc_.destroy(data_ + i);
            }
            
            if (data_) {
                alloc_.deallocate(data_, capacity_);
            }
            
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }
    
    // Modifiers
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        alloc_.construct(data_ + size_, value);
        ++size_;
    }
    
    void push_back(T&& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        alloc_.construct(data_ + size_, std::move(value));
        ++size_;
    }
    
    void pop_back() {
        if (size_ > 0) {
            alloc_.destroy(data_ + size_ - 1);
            --size_;
        }
    }
    
    void clear() {
        for (size_type i = 0; i < size_; ++i) {
            alloc_.destroy(data_ + i);
        }
        size_ = 0;
    }
    
    // Iterators
    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    const_iterator cbegin() const { return data_; }
    
    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }
    const_iterator cend() const { return data_ + size_; }
    
    // Utility
    void swap(custom_vector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(alloc_, other.alloc_);
    }
};
```

### Advanced Vector Features
```cpp
template<typename T, typename Allocator = std::allocator<T>>
class advanced_vector : public custom_vector<T, Allocator> {
public:
    using base = custom_vector<T, Allocator>;
    using base::base;
    
    // Emplace operations
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (this->size() >= this->capacity()) {
            this->reserve(this->capacity() == 0 ? 1 : this->capacity() * 2);
        }
        this->alloc_.construct(this->data_ + this->size(), 
                              std::forward<Args>(args)...);
        ++this->size_;
    }
    
    // Insert operations
    iterator insert(const_iterator pos, const T& value) {
        size_t index = pos - this->begin();
        if (this->size() >= this->capacity()) {
            this->reserve(this->capacity() == 0 ? 1 : this->capacity() * 2);
        }
        
        // Shift elements
        for (size_t i = this->size(); i > index; --i) {
            this->alloc_.construct(this->data_ + i, 
                                  std::move(this->data_[i - 1]));
            this->alloc_.destroy(this->data_ + i - 1);
        }
        
        this->alloc_.construct(this->data_ + index, value);
        ++this->size_;
        return this->begin() + index;
    }
    
    // Erase operations
    iterator erase(const_iterator pos) {
        size_t index = pos - this->begin();
        this->alloc_.destroy(this->data_ + index);
        
        // Shift elements
        for (size_t i = index; i < this->size() - 1; ++i) {
            this->alloc_.construct(this->data_ + i, 
                                  std::move(this->data_[i + 1]));
            this->alloc_.destroy(this->data_ + i + 1);
        }
        
        --this->size_;
        return this->begin() + index;
    }
    
    // Resize operations
    void resize(size_type count, const T& value = T{}) {
        if (count > this->size()) {
            if (count > this->capacity()) {
                this->reserve(count);
            }
            for (size_type i = this->size(); i < count; ++i) {
                this->alloc_.construct(this->data_ + i, value);
            }
        } else if (count < this->size()) {
            for (size_type i = count; i < this->size(); ++i) {
                this->alloc_.destroy(this->data_ + i);
            }
        }
        this->size_ = count;
    }
};
```

## 🔍 Custom List Implementation

### Doubly Linked List
```cpp
template<typename T, typename Allocator = std::allocator<T>>
class custom_list {
private:
    struct node {
        T data;
        node* prev;
        node* next;
        
        node(const T& d, node* p = nullptr, node* n = nullptr)
            : data(d), prev(p), next(n) {}
    };
    
    node* head_;
    node* tail_;
    size_t size_;
    Allocator alloc_;
    
    // Node allocator
    using node_allocator = typename std::allocator_traits<Allocator>
        ::template rebind_alloc<node>;
    node_allocator node_alloc_;
    
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;
    
    // Iterator implementation
    class iterator {
    private:
        node* current_;
        
    public:
        using iterator_category = bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator(node* n = nullptr) : current_(n) {}
        
        reference operator*() { return current_->data; }
        pointer operator->() { return &(current_->data); }
        
        iterator& operator++() {
            current_ = current_->next;
            return *this;
        }
        
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        iterator& operator--() {
            current_ = current_->prev;
            return *this;
        }
        
        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }
        
        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
        
        friend class custom_list;
    };
    
    // Constructors
    custom_list() : size_(0) {
        head_ = tail_ = create_sentinel();
    }
    
    custom_list(size_type count, const T& value = T{}) : size_(0) {
        head_ = tail_ = create_sentinel();
        for (size_type i = 0; i < count; ++i) {
            push_back(value);
        }
    }
    
    // Destructor
    ~custom_list() {
        clear();
        destroy_sentinel(head_);
    }
    
    // Element access
    reference front() { return head_->next->data; }
    const_reference front() const { return head_->next->data; }
    
    reference back() { return tail_->prev->data; }
    const_reference back() const { return tail_->prev->data; }
    
    // Capacity
    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }
    
    // Modifiers
    void push_front(const T& value) {
        insert_after(head_, value);
    }
    
    void push_back(const T& value) {
        insert_before(tail_, value);
    }
    
    void pop_front() {
        if (!empty()) {
            erase(head_->next);
        }
    }
    
    void pop_back() {
        if (!empty()) {
            erase(tail_->prev);
        }
    }
    
    // Insert operations
    iterator insert(iterator pos, const T& value) {
        node* n = pos.current_;
        insert_before(n, value);
        return iterator(n->prev);
    }
    
    // Erase operations
    iterator erase(iterator pos) {
        node* n = pos.current_;
        iterator next(n->next);
        erase(n);
        return next;
    }
    
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
    
    // Iterators
    iterator begin() { return iterator(head_->next); }
    iterator end() { return iterator(tail_); }
    
private:
    node* create_sentinel() {
        node* sentinel = node_alloc_.allocate(1);
        node_alloc_.construct(sentinel, T{}, nullptr, nullptr);
        return sentinel;
    }
    
    void destroy_sentinel(node* n) {
        node_alloc_.destroy(n);
        node_alloc_.deallocate(n, 1);
    }
    
    void insert_after(node* n, const T& value) {
        node* new_node = node_alloc_.allocate(1);
        node_alloc_.construct(new_node, value, n, n->next);
        
        n->next->prev = new_node;
        n->next = new_node;
        ++size_;
    }
    
    void insert_before(node* n, const T& value) {
        node* new_node = node_alloc_.allocate(1);
        node_alloc_.construct(new_node, value, n->prev, n);
        
        n->prev->next = new_node;
        n->prev = new_node;
        ++size_;
    }
    
    void erase(node* n) {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        
        node_alloc_.destroy(n);
        node_alloc_.deallocate(n, 1);
        --size_;
    }
};
```

## 🎯 Custom Map Implementation

### Binary Search Tree Map
```cpp
template<typename Key, typename Value, typename Compare = std::less<Key>,
         typename Allocator = std::allocator<std::pair<const Key, Value>>>
class custom_map {
private:
    struct node {
        std::pair<const Key, Value> data;
        node* left;
        node* right;
        node* parent;
        bool is_red;  // For red-black tree properties
        
        node(const std::pair<const Key, Value>& d, node* p = nullptr)
            : data(d), left(nullptr), right(nullptr), parent(p), is_red(true) {}
    };
    
    node* root_;
    size_t size_;
    Compare comp_;
    Allocator alloc_;
    
    using node_allocator = typename std::allocator_traits<Allocator>
        ::template rebind_alloc<node>;
    node_allocator node_alloc_;
    
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const Key, Value>;
    using size_type = size_t;
    using key_compare = Compare;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    
    // Iterator implementation
    class iterator {
    private:
        node* current_;
        
    public:
        using iterator_category = bidirectional_iterator_tag;
        using value_type = std::pair<const Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        
        iterator(node* n = nullptr) : current_(n) {}
        
        reference operator*() { return current_->data; }
        pointer operator->() { return &(current_->data); }
        
        iterator& operator++() {
            if (current_->right) {
                current_ = current_->right;
                while (current_->left) {
                    current_ = current_->left;
                }
            } else {
                node* parent = current_->parent;
                while (parent && current_ == parent->right) {
                    current_ = parent;
                    parent = parent->parent;
                }
                current_ = parent;
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        iterator& operator--() {
            if (current_->left) {
                current_ = current_->left;
                while (current_->right) {
                    current_ = current_->right;
                }
            } else {
                node* parent = current_->parent;
                while (parent && current_ == parent->left) {
                    current_ = parent;
                    parent = parent->parent;
                }
                current_ = parent;
            }
            return *this;
        }
        
        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }
        
        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
        
        friend class custom_map;
    };
    
    // Constructors
    custom_map() : root_(nullptr), size_(0) {}
    
    // Destructor
    ~custom_map() {
        clear();
    }
    
    // Capacity
    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }
    
    // Element access
    Value& operator[](const Key& key) {
        auto [it, inserted] = insert({key, Value{}});
        return it->second;
    }
    
    // Modifiers
    std::pair<iterator, bool> insert(const value_type& value) {
        if (!root_) {
            root_ = create_node(value);
            root_->is_red = false;  // Root is always black
            ++size_;
            return {iterator(root_), true};
        }
        
        node* current = root_;
        node* parent = nullptr;
        
        while (current) {
            parent = current;
            if (comp_(value.first, current->data.first)) {
                current = current->left;
            } else if (comp_(current->data.first, value.first)) {
                current = current->right;
            } else {
                return {iterator(current), false};  // Key already exists
            }
        }
        
        node* new_node = create_node(value, parent);
        if (comp_(value.first, parent->data.first)) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        
        ++size_;
        fix_red_black_properties(new_node);
        return {iterator(new_node), true};
    }
    
    // Lookup
    iterator find(const Key& key) {
        node* current = root_;
        while (current) {
            if (comp_(key, current->data.first)) {
                current = current->left;
            } else if (comp_(current->data.first, key)) {
                current = current->right;
            } else {
                return iterator(current);
            }
        }
        return end();
    }
    
    // Iterators
    iterator begin() {
        if (!root_) return end();
        node* current = root_;
        while (current->left) {
            current = current->left;
        }
        return iterator(current);
    }
    
    iterator end() { return iterator(nullptr); }
    
private:
    node* create_node(const value_type& value, node* parent = nullptr) {
        node* n = node_alloc_.allocate(1);
        node_alloc_.construct(n, value, parent);
        return n;
    }
    
    void fix_red_black_properties(node* n) {
        // Red-black tree balancing logic
        // This is a simplified version - real implementation would be more complex
        while (n != root_ && n->parent->is_red) {
            if (n->parent == n->parent->parent->left) {
                node* uncle = n->parent->parent->right;
                if (uncle && uncle->is_red) {
                    n->parent->is_red = false;
                    uncle->is_red = false;
                    n->parent->parent->is_red = true;
                    n = n->parent->parent;
                } else {
                    if (n == n->parent->right) {
                        n = n->parent;
                        rotate_left(n);
                    }
                    n->parent->is_red = false;
                    n->parent->parent->is_red = true;
                    rotate_right(n->parent->parent);
                }
            } else {
                // Symmetric case for right child
                // Implementation similar to left case
            }
        }
        root_->is_red = false;
    }
    
    void rotate_left(node* n) {
        node* right_child = n->right;
        n->right = right_child->left;
        if (right_child->left) {
            right_child->left->parent = n;
        }
        right_child->parent = n->parent;
        if (!n->parent) {
            root_ = right_child;
        } else if (n == n->parent->left) {
            n->parent->left = right_child;
        } else {
            n->parent->right = right_child;
        }
        right_child->left = n;
        n->parent = right_child;
    }
    
    void rotate_right(node* n) {
        node* left_child = n->left;
        n->left = left_child->right;
        if (left_child->right) {
            left_child->right->parent = n;
        }
        left_child->parent = n->parent;
        if (!n->parent) {
            root_ = left_child;
        } else if (n == n->parent->right) {
            n->parent->right = left_child;
        } else {
            n->parent->left = left_child;
        }
        left_child->right = n;
        n->parent = left_child;
    }
    
    void clear() {
        // Recursive deletion of tree nodes
        clear_recursive(root_);
        root_ = nullptr;
        size_ = 0;
    }
    
    void clear_recursive(node* n) {
        if (n) {
            clear_recursive(n->left);
            clear_recursive(n->right);
            node_alloc_.destroy(n);
            node_alloc_.deallocate(n, 1);
        }
    }
};
```

## 🚀 Custom Algorithm Implementation

### Basic Algorithms
```cpp
// Custom find algorithm
template<typename InputIt, typename T>
InputIt custom_find(InputIt first, InputIt last, const T& value) {
    for (; first != last; ++first) {
        if (*first == value) {
            return first;
        }
    }
    return last;
}

// Custom copy algorithm
template<typename InputIt, typename OutputIt>
OutputIt custom_copy(InputIt first, InputIt last, OutputIt d_first) {
    for (; first != last; ++first, ++d_first) {
        *d_first = *first;
    }
    return d_first;
}

// Custom sort algorithm (quicksort)
template<typename RandomIt>
void custom_sort(RandomIt first, RandomIt last) {
    if (first < last) {
        RandomIt pivot = partition(first, last);
        custom_sort(first, pivot);
        custom_sort(pivot + 1, last);
    }
}

template<typename RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
    auto pivot = *(last - 1);
    RandomIt i = first - 1;
    
    for (RandomIt j = first; j < last - 1; ++j) {
        if (*j <= pivot) {
            ++i;
            std::iter_swap(i, j);
        }
    }
    
    std::iter_swap(i + 1, last - 1);
    return i + 1;
}
```

## 🔧 Custom Allocator Implementation

### Pool Allocator
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
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::false_type;
    
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
    ~pool_allocator() {
        for (block* b : blocks) {
            delete b;
        }
    }
};
```

## 📚 Best Practices

### 1. Exception Safety
- **Basic guarantee**: Container remains in valid state
- **Strong guarantee**: Operation succeeds or leaves container unchanged
- **No-throw guarantee**: Operation never throws

### 2. Memory Management
- **RAII**: Use constructors/destructors for resource management
- **Smart pointers**: Avoid raw pointer management
- **Allocator awareness**: Respect allocator requirements

### 3. Performance Considerations
- **Cache locality**: Design for good memory access patterns
- **Minimal allocations**: Reduce dynamic memory operations
- **Efficient algorithms**: Choose appropriate complexity

### 4. Standard Compliance
- **Iterator requirements**: Implement required iterator operations
- **Container requirements**: Meet standard container interface
- **Exception specifications**: Follow standard exception guarantees

## 🚀 Advanced Features

### Type Traits Support
```cpp
// Custom type traits for your containers
template<typename Container>
struct container_traits {
    using value_type = typename Container::value_type;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using size_type = typename Container::size_type;
    
    static constexpr bool is_contiguous = false;
    static constexpr bool is_sequence = true;
    static constexpr bool is_associative = false;
};

// Specialization for vector-like containers
template<typename T, typename Alloc>
struct container_traits<std::vector<T, Alloc>> {
    using value_type = T;
    using iterator = typename std::vector<T, Alloc>::iterator;
    using const_iterator = typename std::vector<T, Alloc>::const_iterator;
    using size_type = typename std::vector<T, Alloc>::size_type;
    
    static constexpr bool is_contiguous = true;
    static constexpr bool is_sequence = true;
    static constexpr bool is_associative = false;
};
```

### Concepts Support (C++20)
```cpp
// Custom concepts for containers
template<typename T>
concept Container = requires(T& t) {
    typename T::value_type;
    typename T::iterator;
    typename T::const_iterator;
    typename T::size_type;
    
    { t.begin() } -> std::input_iterator;
    { t.end() } -> std::input_iterator;
    { t.size() } -> std::convertible_to<typename T::size_type>;
    { t.empty() } -> std::convertible_to<bool>;
};

template<typename T>
concept SequenceContainer = Container<T> && requires(T& t) {
    { t.push_back(std::declval<typename T::value_type>()) };
    { t.pop_back() };
    { t.front() } -> std::convertible_to<typename T::value_type>;
    { t.back() } -> std::convertible_to<typename T::value_type>;
};
```

## 📖 Resources

### Books
- "The C++ Standard Library" by Nicolai Josuttis
- "Effective STL" by Scott Meyers
- "C++ Templates: The Complete Guide" by David Vandevoorde

### Online Resources
- [cppreference.com](https://en.cppreference.com/w/cpp/container)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [STL Implementation Examples](https://github.com/microsoft/STL)

## 🚀 Practice Problems

### Basic Exercises
1. **Simple Vector**: Implement basic vector with push_back/pop_back
2. **Linked List**: Build singly linked list with iterators
3. **Basic Allocator**: Create simple pool allocator

### Intermediate Exercises
1. **Red-Black Tree**: Implement balanced binary search tree
2. **Hash Table**: Build unordered_map with chaining
3. **Custom Algorithms**: Implement sort, find, copy algorithms

### Advanced Exercises
1. **STL-Compatible Container**: Full STL compliance
2. **Custom Iterator Types**: Bidirectional, random access iterators
3. **Advanced Allocators**: Arena, stack, or custom memory allocators

---

*Implementing custom STL components is the ultimate way to understand C++ deeply. Start with simple containers and gradually build up to complex data structures. Remember: the standard library is the result of decades of optimization and design refinement.*
