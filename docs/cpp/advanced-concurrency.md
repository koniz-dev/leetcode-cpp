# 🚀 Advanced C++ Concurrency

## 📚 Overview

Advanced concurrency in C++ goes beyond basic threading to include lock-free programming, memory ordering, atomic operations, and sophisticated synchronization patterns. This guide covers advanced techniques for building high-performance, scalable concurrent applications.

## 🎯 Advanced Concurrency Concepts

### Memory Ordering
- **Sequential Consistency**: Strongest ordering guarantee
- **Acquire-Release Semantics**: Partial ordering for synchronization
- **Relaxed Ordering**: Weakest ordering, maximum performance
- **Memory Barriers**: Explicit ordering control

### Lock-Free Programming
- **Lock-Free Algorithms**: Progress guaranteed for some thread
- **Wait-Free Algorithms**: Progress guaranteed for all threads
- **Obstruction-Free Algorithms**: Progress when no contention
- **CAS Operations**: Compare-and-swap for atomic updates

## 🔧 Memory Ordering Deep Dive

### Sequential Consistency (SC)
```cpp
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> x{0}, y{0};
std::atomic<int> r1{0}, r2{0};

void thread1() {
    x.store(1, std::memory_order_seq_cst);
    r1.store(y.load(std::memory_order_seq_cst), std::memory_order_seq_cst);
}

void thread2() {
    y.store(1, std::memory_order_seq_cst);
    r2.store(x.load(std::memory_order_seq_cst), std::memory_order_seq_cst);
}

// With SC, r1 == 0 && r2 == 0 is impossible
// All threads see operations in the same global order
```

### Acquire-Release Semantics
```cpp
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> data{0};
std::atomic<bool> ready{false};

void producer() {
    data.store(42, std::memory_order_relaxed);
    ready.store(true, std::memory_order_release);  // Release barrier
}

void consumer() {
    while (!ready.load(std::memory_order_acquire)) {  // Acquire barrier
        // Spin until ready
    }
    int value = data.load(std::memory_order_relaxed);
    std::cout << "Data: " << value << std::endl;
}

// Release in producer synchronizes with acquire in consumer
// Data written before release is visible after acquire
```

### Relaxed Ordering
```cpp
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> counter{0};

void increment() {
    for (int i = 0; i < 1000; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

// Relaxed ordering provides no synchronization guarantees
// Only useful for simple counters or when you don't need ordering
```

### Memory Barriers
```cpp
#include <atomic>
#include <thread>

std::atomic<int> x{0}, y{0};
int r1, r2;

void thread1() {
    x.store(1, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_release);  // Release barrier
    y.store(1, std::memory_order_relaxed);
}

void thread2() {
    r1 = y.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);  // Acquire barrier
    r2 = x.load(std::memory_order_relaxed);
}

// Fence ensures ordering between operations
```

## 🚀 Lock-Free Data Structures

### Lock-Free Stack
```cpp
#include <atomic>
#include <memory>

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
    
    ~lock_free_stack() {
        T temp;
        while (pop(temp)) {
            // Pop all elements
        }
    }
};
```

### Lock-Free Queue
```cpp
#include <atomic>
#include <memory>

template<typename T>
class lock_free_queue {
private:
    struct node {
        T data;
        std::atomic<node*> next;
        node(const T& d) : data(d), next(nullptr) {}
    };
    
    std::atomic<node*> head;
    std::atomic<node*> tail;
    
public:
    lock_free_queue() {
        node* dummy = new node(T{});
        head.store(dummy);
        tail.store(dummy);
    }
    
    void enqueue(const T& data) {
        node* new_node = new node(data);
        node* old_tail = tail.load();
        
        while (true) {
            node* old_next = old_tail->next.load();
            if (old_tail == tail.load()) {
                if (old_next == nullptr) {
                    if (old_tail->next.compare_exchange_weak(old_next, new_node)) {
                        tail.compare_exchange_strong(old_tail, new_node);
                        return;
                    }
                } else {
                    tail.compare_exchange_strong(old_tail, old_next);
                }
            }
        }
    }
    
    bool dequeue(T& result) {
        while (true) {
            node* old_head = head.load();
            node* old_tail = tail.load();
            node* old_next = old_head->next.load();
            
            if (old_head == head.load()) {
                if (old_head == old_tail) {
                    if (old_next == nullptr) {
                        return false;
                    }
                    tail.compare_exchange_strong(old_tail, old_next);
                } else {
                    if (head.compare_exchange_weak(old_head, old_next)) {
                        result = old_next->data;
                        delete old_head;
                        return true;
                    }
                }
            }
        }
    }
    
    ~lock_free_queue() {
        T temp;
        while (dequeue(temp)) {
            // Dequeue all elements
        }
        delete head.load();
    }
};
```

### Lock-Free Hash Table
```cpp
#include <atomic>
#include <vector>
#include <memory>

template<typename K, typename V>
class lock_free_hash_table {
private:
    struct entry {
        K key;
        V value;
        std::atomic<entry*> next;
        entry(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };
    
    struct bucket {
        std::atomic<entry*> head;
        bucket() : head(nullptr) {}
    };
    
    std::vector<std::unique_ptr<bucket>> buckets;
    size_t bucket_count;
    
public:
    lock_free_hash_table(size_t count = 16) : bucket_count(count) {
        buckets.resize(count);
        for (auto& b : buckets) {
            b = std::make_unique<bucket>();
        }
    }
    
    void insert(const K& key, const V& value) {
        size_t index = std::hash<K>{}(key) % bucket_count;
        entry* new_entry = new entry(key, value);
        
        bucket& b = *buckets[index];
        entry* old_head = b.head.load();
        do {
            new_entry->next.store(old_head);
        } while (!b.head.compare_exchange_weak(old_head, new_entry));
    }
    
    bool find(const K& key, V& value) const {
        size_t index = std::hash<K>{}(key) % bucket_count;
        const bucket& b = *buckets[index];
        
        entry* current = b.head.load();
        while (current) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next.load();
        }
        return false;
    }
};
```

## 🔍 Advanced Synchronization Patterns

### Read-Write Lock
```cpp
#include <atomic>
#include <thread>
#include <chrono>

class read_write_lock {
private:
    std::atomic<int> readers{0};
    std::atomic<bool> writer{false};
    
public:
    void read_lock() {
        while (true) {
            int current_readers = readers.load();
            if (writer.load()) {
                std::this_thread::yield();
                continue;
            }
            if (readers.compare_exchange_weak(current_readers, current_readers + 1)) {
                break;
            }
        }
    }
    
    void read_unlock() {
        readers.fetch_sub(1);
    }
    
    void write_lock() {
        while (true) {
            bool expected = false;
            if (writer.compare_exchange_weak(expected, true)) {
                while (readers.load() > 0) {
                    std::this_thread::yield();
                }
                break;
            }
            std::this_thread::yield();
        }
    }
    
    void write_unlock() {
        writer.store(false);
    }
};

// Usage
read_write_lock rwlock;
std::vector<int> data;

void reader() {
    rwlock.read_lock();
    // Read data safely
    rwlock.read_unlock();
}

void writer() {
    rwlock.write_lock();
    // Write data safely
    rwlock.write_unlock();
}
```

### Condition Variable with Lock-Free Notification
```cpp
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>

template<typename T>
class lock_free_notification_queue {
private:
    struct notification {
        T data;
        std::atomic<notification*> next;
        notification(const T& d) : data(d), next(nullptr) {}
    };
    
    std::atomic<notification*> head;
    std::atomic<notification*> tail;
    std::mutex mutex;
    std::condition_variable cv;
    
public:
    lock_free_notification_queue() {
        notification* dummy = new notification(T{});
        head.store(dummy);
        tail.store(dummy);
    }
    
    void notify(const T& data) {
        notification* new_notification = new notification(data);
        notification* old_tail = tail.load();
        
        while (true) {
            notification* old_next = old_tail->next.load();
            if (old_tail == tail.load()) {
                if (old_next == nullptr) {
                    if (old_tail->next.compare_exchange_weak(old_next, new_notification)) {
                        tail.compare_exchange_strong(old_tail, new_notification);
                        cv.notify_one();
                        return;
                    }
                } else {
                    tail.compare_exchange_strong(old_tail, old_next);
                }
            }
        }
    }
    
    bool wait_for_notification(T& data, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mutex);
        
        if (cv.wait_for(lock, timeout, [this] { return has_notifications(); })) {
            return dequeue_notification(data);
        }
        return false;
    }
    
private:
    bool has_notifications() {
        notification* current = head.load();
        return current->next.load() != nullptr;
    }
    
    bool dequeue_notification(T& data) {
        notification* old_head = head.load();
        notification* new_head = old_head->next.load();
        
        if (new_head) {
            if (head.compare_exchange_weak(old_head, new_head)) {
                data = new_head->data;
                delete old_head;
                return true;
            }
        }
        return false;
    }
};
```

## ⚡ Performance Optimization Techniques

### Memory Pool for Lock-Free Structures
```cpp
#include <vector>
#include <atomic>

template<typename T, size_t BlockSize = 1024>
class lock_free_memory_pool {
private:
    struct block {
        block* next;
        char data[BlockSize];
    };
    
    struct free_list {
        T* head;
        std::atomic<size_t> count;
        
        free_list() : head(nullptr), count(0) {}
    };
    
    std::vector<std::unique_ptr<block>> blocks;
    std::vector<free_list> free_lists;
    size_t block_count;
    
public:
    lock_free_memory_pool(size_t blocks = 4) : block_count(blocks) {
        free_lists.resize(blocks);
        allocate_blocks();
    }
    
    T* allocate() {
        for (size_t i = 0; i < block_count; ++i) {
            free_list& fl = free_lists[i];
            T* result = fl.head;
            
            if (result) {
                if (fl.head.compare_exchange_weak(result, 
                    reinterpret_cast<T*>(result->next))) {
                    fl.count.fetch_sub(1);
                    return result;
                }
            }
        }
        return nullptr;
    }
    
    void deallocate(T* ptr) {
        if (!ptr) return;
        
        // Find appropriate free list
        for (size_t i = 0; i < block_count; ++i) {
            free_list& fl = free_lists[i];
            
            // Simple strategy: use first available list
            if (fl.count.load() < BlockSize / sizeof(T)) {
                ptr->next = fl.head;
                while (!fl.head.compare_exchange_weak(ptr->next, ptr)) {
                    // Retry if CAS fails
                }
                fl.count.fetch_add(1);
                return;
            }
        }
    }
    
private:
    void allocate_blocks() {
        for (size_t i = 0; i < block_count; ++i) {
            auto new_block = std::make_unique<block>();
            new_block->next = nullptr;
            
            // Initialize free list
            char* data = new_block->data;
            free_list& fl = free_lists[i];
            
            for (size_t j = 0; j < BlockSize - sizeof(T); j += sizeof(T)) {
                T* current = reinterpret_cast<T*>(data + j);
                current->next = fl.head;
                fl.head = current;
                fl.count.fetch_add(1);
            }
            
            blocks.push_back(std::move(new_block));
        }
    }
};
```

### Lock-Free Work Stealing Queue
```cpp
#include <atomic>
#include <array>
#include <thread>

template<typename T, size_t QueueSize = 1024>
class work_stealing_queue {
private:
    std::array<T, QueueSize> data;
    std::atomic<size_t> head{0};
    std::atomic<size_t> tail{0};
    
public:
    bool push(const T& item) {
        size_t current_tail = tail.load();
        size_t next_tail = (current_tail + 1) % QueueSize;
        
        if (next_tail == head.load()) {
            return false;  // Queue full
        }
        
        data[current_tail] = item;
        tail.store(next_tail);
        return true;
    }
    
    bool pop(T& item) {
        size_t current_head = head.load();
        size_t current_tail = tail.load();
        
        if (current_head == current_tail) {
            return false;  // Queue empty
        }
        
        item = data[current_head];
        head.store((current_head + 1) % QueueSize);
        return true;
    }
    
    bool steal(T& item) {
        size_t current_head = head.load();
        size_t current_tail = tail.load();
        
        if (current_head == current_tail) {
            return false;  // Queue empty
        }
        
        item = data[current_head];
        head.store((current_head + 1) % QueueSize);
        return true;
    }
    
    bool empty() const {
        return head.load() == tail.load();
    }
    
    size_t size() const {
        size_t h = head.load();
        size_t t = tail.load();
        return (t >= h) ? (t - h) : (QueueSize - h + t);
    }
};
```

## 🔧 Advanced Thread Management

### Work Stealing Thread Pool
```cpp
#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

class work_stealing_thread_pool {
private:
    using task_type = std::function<void()>;
    
    std::vector<std::unique_ptr<work_stealing_queue<task_type>>> local_queues;
    std::vector<std::thread> workers;
    std::atomic<bool> done{false};
    
    static thread_local size_t thread_index;
    static thread_local work_stealing_queue<task_type>* local_queue;
    
public:
    work_stealing_thread_pool(size_t thread_count = std::thread::hardware_concurrency()) {
        local_queues.resize(thread_count);
        for (size_t i = 0; i < thread_count; ++i) {
            local_queues[i] = std::make_unique<work_stealing_queue<task_type>>();
        }
        
        for (size_t i = 0; i < thread_count; ++i) {
            workers.emplace_back([this, i] { worker_thread(i); });
        }
    }
    
    template<typename F>
    auto submit(F&& f) -> std::future<decltype(f())> {
        using result_type = decltype(f());
        
        auto task = std::make_shared<std::packaged_task<result_type()>>(std::forward<F>(f));
        std::future<result_type> result = task->get_future();
        
        if (local_queue) {
            local_queue->push([task]() { (*task)(); });
        } else {
            // Fallback to random queue
            size_t index = std::hash<std::thread::id>{}(std::this_thread::get_id()) % local_queues.size();
            local_queues[index]->push([task]() { (*task)(); });
        }
        
        return result;
    }
    
    ~work_stealing_thread_pool() {
        done = true;
        for (auto& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }
    
private:
    void worker_thread(size_t index) {
        thread_index = index;
        local_queue = local_queues[index].get();
        
        while (!done) {
            task_type task;
            
            if (local_queue->pop(task)) {
                task();
            } else {
                // Try to steal work from other queues
                bool found_work = false;
                for (size_t i = 0; i < local_queues.size(); ++i) {
                    if (i != index && local_queues[i]->steal(task)) {
                        found_work = true;
                        break;
                    }
                }
                
                if (!found_work) {
                    std::this_thread::yield();
                }
            }
        }
    }
};

thread_local size_t work_stealing_thread_pool::thread_index = 0;
thread_local work_stealing_queue<std::function<void()>>* work_stealing_thread_pool::local_queue = nullptr;
```

## 📚 Best Practices

### 1. Memory Ordering Guidelines
- **Use SC for simple cases** where performance isn't critical
- **Use acquire-release for synchronization** between threads
- **Use relaxed only when you understand the implications**
- **Always document memory ordering assumptions**

### 2. Lock-Free Programming
- **Start with existing lock-free structures** before building your own
- **Use memory barriers sparingly** - they're expensive
- **Test thoroughly** with multiple threads and stress tests
- **Consider ABA problems** in your designs

### 3. Performance Considerations
- **Profile your concurrent code** to identify bottlenecks
- **Use appropriate data structures** for your access patterns
- **Minimize cache line sharing** between threads
- **Consider NUMA effects** in multi-socket systems

## 📖 Resources

### Books
- "C++ Concurrency in Action" by Anthony Williams
- "The Art of Multiprocessor Programming" by Maurice Herlihy and Nir Shavit
- "Is Parallel Programming Hard, And, If So, What Can You Do About It?" by Paul McKenney

### Online Resources
- [C++ Concurrency Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Lock-Free Programming](https://preshing.com/20120612/an-introduction-to-lock-free-programming/)
- [Memory Ordering](https://en.cppreference.com/w/cpp/atomic/memory_order)

## 🚀 Practice Problems

### Basic Exercises
1. **Memory Ordering**: Implement producer-consumer with different orderings
2. **Lock-Free Counter**: Build atomic counter with relaxed ordering
3. **Simple Lock-Free Stack**: Implement basic lock-free stack

### Intermediate Exercises
1. **Lock-Free Queue**: Build lock-free queue with proper synchronization
2. **Read-Write Lock**: Implement lock-free read-write lock
3. **Memory Pool**: Create lock-free memory pool for specific types

### Advanced Exercises
1. **Lock-Free Hash Table**: Build concurrent hash table without locks
2. **Work Stealing Scheduler**: Implement work stealing thread pool
3. **Lock-Free Data Structures**: Design custom lock-free structures for specific use cases

---

*Advanced concurrency is about finding the right balance between performance, correctness, and complexity. Start with simple patterns and gradually build up to more sophisticated lock-free algorithms. Remember: correctness always comes before performance.*
