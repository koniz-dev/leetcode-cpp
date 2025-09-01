# Concurrency in C++

## Overview

Concurrency in C++ allows multiple tasks to execute simultaneously, improving performance and responsiveness. Modern C++ provides several mechanisms for concurrent programming, including threads, async tasks, mutexes, and condition variables.

## Threads

### Basic Thread Creation

```cpp
#include <thread>
#include <iostream>

void workerFunction(int id) {
    std::cout << "Worker " << id << " started" << std::endl;
    // Simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Worker " << id << " finished" << std::endl;
}

int main() {
    // Create thread
    std::thread worker(workerFunction, 1);
    
    // Main thread continues
    std::cout << "Main thread working..." << std::endl;
    
    // Wait for worker to finish
    worker.join();
    
    std::cout << "All threads finished" << std::endl;
    return 0;
}
```

### Thread with Lambda

```cpp
#include <thread>
#include <vector>

int main() {
    std::vector<std::thread> threads;
    
    // Create multiple threads with lambda
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([i]() {
            std::cout << "Thread " << i << " working" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        });
    }
    
    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    return 0;
}
```

### Thread with Member Function

```cpp
#include <thread>

class Worker {
public:
    void doWork(int id) {
        std::cout << "Worker " << id << " processing..." << std::endl;
        // Work implementation
    }
    
    void startWork(int id) {
        std::thread worker(&Worker::doWork, this, id);
        worker.detach();  // Let thread run independently
    }
};

int main() {
    Worker worker;
    worker.startWork(42);
    
    // Main thread continues
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return 0;
}
```

## Data Sharing and Synchronization

### Race Conditions

```cpp
#include <thread>
#include <iostream>

int sharedCounter = 0;  // Shared data

void incrementCounter() {
    for (int i = 0; i < 1000000; ++i) {
        sharedCounter++;  // Race condition!
    }
}

int main() {
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);
    
    t1.join();
    t2.join();
    
    // Result may not be 2000000 due to race condition
    std::cout << "Final counter: " << sharedCounter << std::endl;
    return 0;
}
```

### Mutex Protection

```cpp
#include <thread>
#include <mutex>
#include <iostream>

int sharedCounter = 0;
std::mutex counterMutex;

void incrementCounter() {
    for (int i = 0; i < 1000000; ++i) {
        std::lock_guard<std::mutex> lock(counterMutex);
        sharedCounter++;  // Protected access
    }
}

int main() {
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);
    
    t1.join();
    t2.join();
    
    // Result will be 2000000
    std::cout << "Final counter: " << sharedCounter << std::endl;
    return 0;
}
```

### Different Mutex Types

```cpp
#include <mutex>
#include <shared_mutex>
#include <thread>

class ThreadSafeCounter {
private:
    mutable std::shared_mutex mutex_;
    int value_ = 0;

public:
    // Multiple readers can access simultaneously
    int get() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return value_;
    }
    
    // Only one writer at a time
    void increment() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        ++value_;
    }
    
    // Reset value
    void reset() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        value_ = 0;
    }
};

// Usage
ThreadSafeCounter counter;

void reader() {
    for (int i = 0; i < 100; ++i) {
        int val = counter.get();
        // Process value
    }
}

void writer() {
    for (int i = 0; i < 10; ++i) {
        counter.increment();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
```

## Condition Variables

### Producer-Consumer Pattern

```cpp
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;

public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(value));
        condition_.notify_one();
    }
    
    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return false;
        }
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }
    
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return !queue_.empty(); });
        value = std::move(queue_.front());
        queue_.pop();
    }
    
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }
};

// Producer-consumer example
ThreadSafeQueue<int> queue;
std::atomic<bool> done{false};

void producer() {
    for (int i = 0; i < 10; ++i) {
        queue.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    done = true;
}

void consumer() {
    while (!done || !queue.empty()) {
        int value;
        if (queue.try_pop(value)) {
            std::cout << "Consumed: " << value << std::endl;
        }
    }
}
```

## Atomic Operations

### Atomic Variables

```cpp
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> atomicCounter{0};
std::atomic<bool> ready{false};

void worker() {
    while (!ready) {
        std::this_thread::yield();  // Give other threads a chance
    }
    
    for (int i = 0; i < 1000000; ++i) {
        atomicCounter.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);
    
    ready = true;  // Signal threads to start
    
    t1.join();
    t2.join();
    
    std::cout << "Final counter: " << atomicCounter.load() << std::endl;
    return 0;
}
```

### Memory Ordering

```cpp
#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> data{0};
std::atomic<bool> ready{false};

void producer() {
    data.store(42, std::memory_order_relaxed);
    ready.store(true, std::memory_order_release);
}

void consumer() {
    while (!ready.load(std::memory_order_acquire)) {
        std::this_thread::yield();
    }
    
    int value = data.load(std::memory_order_relaxed);
    std::cout << "Consumed: " << value << std::endl;
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    
    t1.join();
    t2.join();
    return 0;
}
```

## Async Tasks

### std::async

```cpp
#include <future>
#include <iostream>
#include <chrono>

int longRunningTask(int id) {
    std::cout << "Task " << id << " started" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Task " << id << " finished" << std::endl;
    return id * 10;
}

int main() {
    // Launch task asynchronously
    auto future1 = std::async(std::launch::async, longRunningTask, 1);
    auto future2 = std::async(std::launch::async, longRunningTask, 2);
    
    // Do other work while tasks are running
    std::cout << "Main thread working..." << std::endl;
    
    // Get results (this will wait if not ready)
    int result1 = future1.get();
    int result2 = future2.get();
    
    std::cout << "Results: " << result1 << ", " << result2 << std::endl;
    return 0;
}
```

### std::packaged_task

```cpp
#include <future>
#include <functional>
#include <iostream>

int complexCalculation(int x, int y) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return x * x + y * y;
}

int main() {
    // Create packaged task
    std::packaged_task<int(int, int)> task(complexCalculation);
    
    // Get future from task
    std::future<int> future = task.get_future();
    
    // Launch task in separate thread
    std::thread worker(std::move(task), 3, 4);
    
    // Do other work
    std::cout << "Working on other things..." << std::endl;
    
    // Get result
    int result = future.get();
    std::cout << "Result: " << result << std::endl;
    
    worker.join();
    return 0;
}
```

### std::promise and std::future

```cpp
#include <future>
#include <thread>
#include <iostream>

void workerFunction(std::promise<int> promise) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    promise.set_value(42);
}

int main() {
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    
    std::thread worker(workerFunction, std::move(promise));
    
    // Wait for result
    int result = future.get();
    std::cout << "Result: " << result << std::endl;
    
    worker.join();
    return 0;
}
```

## Thread Pools

### Simple Thread Pool Implementation

```cpp
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;

public:
    ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this] { 
                            return stop || !tasks.empty(); 
                        });
                        
                        if (stop && tasks.empty()) {
                            return;
                        }
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    }
    
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }
};

// Usage
int main() {
    ThreadPool pool(4);
    
    auto future1 = pool.enqueue([](int x) { return x * x; }, 5);
    auto future2 = pool.enqueue([](int x) { return x * x; }, 10);
    
    std::cout << "5^2 = " << future1.get() << std::endl;
    std::cout << "10^2 = " << future2.get() << std::endl;
    
    return 0;
}
```

## Deadlock Prevention

### Lock Ordering

```cpp
#include <mutex>
#include <thread>

class BankAccount {
private:
    std::mutex mutex_;
    int balance_;

public:
    BankAccount(int initial) : balance_(initial) {}
    
    void transfer(BankAccount& other, int amount) {
        // Always lock in consistent order to prevent deadlock
        std::lock_guard<std::mutex> lock1(mutex_);
        std::lock_guard<std::mutex> lock2(other.mutex_);
        
        if (balance_ >= amount) {
            balance_ -= amount;
            other.balance_ += amount;
        }
    }
    
    int getBalance() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return balance_;
    }
};
```

### std::lock for Multiple Mutexes

```cpp
#include <mutex>
#include <thread>

class SafeTransfer {
private:
    std::mutex mutex1, mutex2;
    int data1 = 0, data2 = 0;

public:
    void safeOperation() {
        // Lock both mutexes atomically
        std::lock(mutex1, mutex2);
        
        // Adopt the locks
        std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);
        
        // Safe to access both data1 and data2
        data1++;
        data2++;
    }
};
```

## Best Practices

### Thread Safety Guidelines

```cpp
// DO: Use RAII for locks
class SafeCounter {
private:
    mutable std::mutex mutex_;
    int value_ = 0;

public:
    void increment() {
        std::lock_guard<std::mutex> lock(mutex_);
        ++value_;
    }
    
    int get() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return value_;
    }
};

// DON'T: Return references to internal data
class BadCounter {
private:
    mutable std::mutex mutex_;
    int value_ = 0;

public:
    // BAD: Returns reference to internal data
    int& getValue() {
        std::lock_guard<std::mutex> lock(mutex_);
        return value_;  // Lock released, reference becomes invalid
    }
};

// DO: Use const member functions when possible
class ThreadSafeContainer {
private:
    mutable std::shared_mutex mutex_;
    std::vector<int> data_;

public:
    // Multiple readers can access simultaneously
    int at(size_t index) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return data_.at(index);
    }
    
    // Only one writer at a time
    void push_back(int value) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        data_.push_back(value);
    }
};
```

### Performance Considerations

```cpp
// Use appropriate synchronization primitives
class OptimizedCounter {
private:
    std::atomic<int> value_{0};  // Use atomic for simple operations

public:
    void increment() {
        value_.fetch_add(1, std::memory_order_relaxed);
    }
    
    int get() const {
        return value_.load(std::memory_order_relaxed);
    }
};

// Avoid false sharing
struct alignas(64) PaddedCounter {  // 64-byte alignment
    std::atomic<int> value{0};
    char padding[60];  // Padding to avoid false sharing
};

// Use thread-local storage when appropriate
thread_local int threadId = 0;
thread_local std::vector<int> localBuffer;
```

## Summary

Concurrency in C++ provides:
- **Performance**: Parallel execution of tasks
- **Responsiveness**: Non-blocking operations
- **Resource utilization**: Better CPU and I/O usage
- **Scalability**: Handle multiple requests simultaneously

Key components:
- **Threads**: Basic unit of execution
- **Mutexes**: Protect shared data from race conditions
- **Condition variables**: Synchronize threads based on conditions
- **Atomic operations**: Lock-free synchronization for simple operations
- **Async tasks**: High-level concurrency abstractions

Best practices:
- **Use RAII**: Automatic resource management
- **Minimize shared state**: Reduce synchronization overhead
- **Choose appropriate primitives**: Atomic for simple, mutex for complex
- **Avoid deadlocks**: Consistent locking order
- **Consider performance**: Use appropriate memory ordering

Concurrency is powerful but complex. Start simple and add complexity only when needed. Always test thoroughly with multiple threads and consider using higher-level abstractions like `std::async` when possible.
