# 🎨 C++ Design Patterns

## 📚 Overview

Design patterns are proven solutions to common software design problems. They provide a shared vocabulary for developers and help create maintainable, extensible, and reusable code. This guide covers both classic Gang of Four patterns and modern C++-specific patterns.

## 🎯 Design Pattern Categories

### Creational Patterns
- **Factory Method**: Create objects without specifying exact classes
- **Abstract Factory**: Create families of related objects
- **Builder**: Construct complex objects step by step
- **Singleton**: Ensure only one instance exists
- **Prototype**: Clone existing objects

### Structural Patterns
- **Adapter**: Make incompatible interfaces work together
- **Bridge**: Separate abstraction from implementation
- **Composite**: Compose objects into tree structures
- **Decorator**: Add behavior to objects dynamically
- **Facade**: Provide simplified interface to complex subsystem
- **Flyweight**: Share common parts of state between objects
- **Proxy**: Control access to another object

### Behavioral Patterns
- **Chain of Responsibility**: Pass requests along handler chain
- **Command**: Encapsulate request as object
- **Iterator**: Access elements without exposing structure
- **Mediator**: Reduce coupling between components
- **Memento**: Save and restore object state
- **Observer**: Notify objects of state changes
- **State**: Change object behavior when state changes
- **Strategy**: Define family of algorithms
- **Template Method**: Define algorithm skeleton
- **Visitor**: Add operations without changing classes

## 🏭 Creational Patterns

### Factory Method Pattern
```cpp
// Abstract creator
class DocumentCreator {
public:
    virtual ~DocumentCreator() = default;
    virtual std::unique_ptr<Document> createDocument() = 0;
};

// Concrete creators
class PDFCreator : public DocumentCreator {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<PDFDocument>();
    }
};

class WordCreator : public DocumentCreator {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<WordDocument>();
    }
};

// Usage
std::unique_ptr<DocumentCreator> creator = std::make_unique<PDFCreator>();
auto document = creator->createDocument();
```

### Abstract Factory Pattern
```cpp
// Abstract factory interface
class UIFactory {
public:
    virtual ~UIFactory() = default;
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
};

// Concrete factories
class WindowsUIFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};

class MacUIFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacCheckbox>();
    }
};

// Usage
std::unique_ptr<UIFactory> factory = std::make_unique<WindowsUIFactory>();
auto button = factory->createButton();
auto checkbox = factory->createCheckbox();
```

### Builder Pattern
```cpp
class Pizza {
private:
    std::string dough;
    std::string sauce;
    std::vector<std::string> toppings;
    
public:
    void setDough(const std::string& d) { dough = d; }
    void setSauce(const std::string& s) { sauce = s; }
    void addTopping(const std::string& topping) { toppings.push_back(topping); }
    
    void show() const {
        std::cout << "Pizza with " << dough << " dough, " << sauce << " sauce";
        if (!toppings.empty()) {
            std::cout << " and toppings: ";
            for (const auto& topping : toppings) {
                std::cout << topping << " ";
            }
        }
        std::cout << std::endl;
    }
};

class PizzaBuilder {
protected:
    std::unique_ptr<Pizza> pizza;
    
public:
    PizzaBuilder() : pizza(std::make_unique<Pizza>()) {}
    virtual ~PizzaBuilder() = default;
    
    Pizza* getPizza() { return pizza.release(); }
    
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildToppings() = 0;
};

class HawaiianPizzaBuilder : public PizzaBuilder {
public:
    void buildDough() override { pizza->setDough("cross"); }
    void buildSauce() override { pizza->setSauce("mild"); }
    void buildToppings() override {
        pizza->addTopping("ham");
        pizza->addTopping("pineapple");
    }
};

class PizzaDirector {
public:
    std::unique_ptr<Pizza> makePizza(PizzaBuilder& builder) {
        builder.buildDough();
        builder.buildSauce();
        builder.buildToppings();
        return std::unique_ptr<Pizza>(builder.getPizza());
    }
};

// Usage
PizzaDirector director;
HawaiianPizzaBuilder hawaiianBuilder;
auto pizza = director.makePizza(hawaiianBuilder);
pizza->show();
```

### Singleton Pattern (Thread-Safe)
```cpp
class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex mutex;
    std::ofstream logFile;
    
    Logger() {
        logFile.open("app.log", std::ios::app);
    }
    
public:
    static Logger& getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!instance) {
            instance = std::unique_ptr<Logger>(new Logger());
        }
        return *instance;
    }
    
    void log(const std::string& message) {
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }
    
    // Prevent copying
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

std::unique_ptr<Logger> Logger::instance = nullptr;
std::mutex Logger::mutex;

// Usage
Logger::getInstance().log("Application started");
```

## 🏗️ Structural Patterns

### Adapter Pattern
```cpp
// Target interface
class Target {
public:
    virtual ~Target() = default;
    virtual void request() = 0;
};

// Adaptee (incompatible interface)
class Adaptee {
public:
    void specificRequest() {
        std::cout << "Adaptee specific request" << std::endl;
    }
};

// Adapter
class Adapter : public Target {
private:
    std::unique_ptr<Adaptee> adaptee;
    
public:
    Adapter() : adaptee(std::make_unique<Adaptee>()) {}
    
    void request() override {
        adaptee->specificRequest();
    }
};

// Usage
std::unique_ptr<Target> target = std::make_unique<Adapter>();
target->request();
```

### Decorator Pattern
```cpp
// Component interface
class Coffee {
public:
    virtual ~Coffee() = default;
    virtual double cost() const = 0;
    virtual std::string description() const = 0;
};

// Concrete component
class SimpleCoffee : public Coffee {
public:
    double cost() const override { return 1.0; }
    std::string description() const override { return "Simple coffee"; }
};

// Decorator base class
class CoffeeDecorator : public Coffee {
protected:
    std::unique_ptr<Coffee> coffee;
    
public:
    CoffeeDecorator(std::unique_ptr<Coffee> c) : coffee(std::move(c)) {}
    
    double cost() const override { return coffee->cost(); }
    std::string description() const override { return coffee->description(); }
};

// Concrete decorators
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    
    double cost() const override { return CoffeeDecorator::cost() + 0.5; }
    std::string description() const override { 
        return CoffeeDecorator::description() + ", milk"; 
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    
    double cost() const override { return CoffeeDecorator::cost() + 0.2; }
    std::string description() const override { 
        return CoffeeDecorator::description() + ", sugar"; 
    }
};

// Usage
auto coffee = std::make_unique<SimpleCoffee>();
auto milkCoffee = std::make_unique<MilkDecorator>(std::move(coffee));
auto sweetMilkCoffee = std::make_unique<SugarDecorator>(std::move(milkCoffee));

std::cout << sweetMilkCoffee->description() << ": $" 
          << sweetMilkCoffee->cost() << std::endl;
```

### Composite Pattern
```cpp
// Component interface
class FileSystemItem {
public:
    virtual ~FileSystemItem() = default;
    virtual void display(int indent = 0) const = 0;
    virtual void add(std::unique_ptr<FileSystemItem> item) {}
    virtual void remove(FileSystemItem* item) {}
};

// Leaf class
class File : public FileSystemItem {
private:
    std::string name;
    
public:
    File(const std::string& n) : name(n) {}
    
    void display(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "- " << name << std::endl;
    }
};

// Composite class
class Directory : public FileSystemItem {
private:
    std::string name;
    std::vector<std::unique_ptr<FileSystemItem>> children;
    
public:
    Directory(const std::string& n) : name(n) {}
    
    void display(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "+ " << name << std::endl;
        for (const auto& child : children) {
            child->display(indent + 2);
        }
    }
    
    void add(std::unique_ptr<FileSystemItem> item) override {
        children.push_back(std::move(item));
    }
    
    void remove(FileSystemItem* item) override {
        children.erase(
            std::remove_if(children.begin(), children.end(),
                [item](const std::unique_ptr<FileSystemItem>& child) {
                    return child.get() == item;
                }),
            children.end()
        );
    }
};

// Usage
auto root = std::make_unique<Directory>("root");
auto docs = std::make_unique<Directory>("docs");
auto file1 = std::make_unique<File>("readme.txt");
auto file2 = std::make_unique<File>("config.txt");

docs->add(std::move(file1));
docs->add(std::move(file2));
root->add(std::move(docs));

root->display();
```

## 🎭 Behavioral Patterns

### Observer Pattern
```cpp
// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

// Subject interface
class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify(const std::string& message) = 0;
};

// Concrete subject
class NewsAgency : public Subject {
private:
    std::vector<std::weak_ptr<Observer>> observers;
    
public:
    void attach(std::shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }
    
    void detach(std::shared_ptr<Observer> observer) override {
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [observer](const std::weak_ptr<Observer>& obs) {
                    return obs.lock() == observer;
                }),
            observers.end()
        );
    }
    
    void notify(const std::string& message) override {
        for (auto it = observers.begin(); it != observers.end();) {
            if (auto observer = it->lock()) {
                observer->update(message);
                ++it;
            } else {
                it = observers.erase(it);
            }
        }
    }
    
    void publishNews(const std::string& news) {
        notify(news);
    }
};

// Concrete observers
class NewsChannel : public Observer {
private:
    std::string name;
    
public:
    NewsChannel(const std::string& n) : name(n) {}
    
    void update(const std::string& message) override {
        std::cout << name << " received: " << message << std::endl;
    }
};

// Usage
auto agency = std::make_shared<NewsAgency>();
auto channel1 = std::make_shared<NewsChannel>("CNN");
auto channel2 = std::make_shared<NewsChannel>("BBC");

agency->attach(channel1);
agency->attach(channel2);

agency->publishNews("Breaking news: C++ is awesome!");
```

### Strategy Pattern
```cpp
// Strategy interface
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<int>& data) = 0;
};

// Concrete strategies
class BubbleSortStrategy : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data.size() - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

class QuickSortStrategy : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::sort(data.begin(), data.end());
    }
};

// Context
class Sorter {
private:
    std::unique_ptr<SortStrategy> strategy;
    
public:
    void setStrategy(std::unique_ptr<SortStrategy> s) {
        strategy = std::move(s);
    }
    
    void sort(std::vector<int>& data) {
        if (strategy) {
            strategy->sort(data);
        }
    }
};

// Usage
Sorter sorter;
std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};

sorter.setStrategy(std::make_unique<BubbleSortStrategy>());
sorter.sort(data);

sorter.setStrategy(std::make_unique<QuickSortStrategy>());
sorter.sort(data);
```

### Command Pattern
```cpp
// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Receiver
class Light {
public:
    void turnOn() { std::cout << "Light is ON" << std::endl; }
    void turnOff() { std::cout << "Light is OFF" << std::endl; }
};

// Concrete commands
class LightOnCommand : public Command {
private:
    Light& light;
    
public:
    LightOnCommand(Light& l) : light(l) {}
    
    void execute() override { light.turnOn(); }
    void undo() override { light.turnOff(); }
};

class LightOffCommand : public Command {
private:
    Light& light;
    
public:
    LightOffCommand(Light& l) : light(l) {}
    
    void execute() override { light.turnOff(); }
    void undo() override { light.turnOn(); }
};

// Invoker
class RemoteControl {
private:
    std::vector<std::unique_ptr<Command>> onCommands;
    std::vector<std::unique_ptr<Command>> offCommands;
    std::unique_ptr<Command> lastCommand;
    
public:
    void setCommand(int slot, std::unique_ptr<Command> onCmd, std::unique_ptr<Command> offCmd) {
        if (slot < onCommands.size()) {
            onCommands[slot] = std::move(onCmd);
            offCommands[slot] = std::move(offCmd);
        }
    }
    
    void onButtonPressed(int slot) {
        if (slot < onCommands.size() && onCommands[slot]) {
            onCommands[slot]->execute();
            lastCommand = std::move(onCommands[slot]);
        }
    }
    
    void offButtonPressed(int slot) {
        if (slot < offCommands.size() && offCommands[slot]) {
            offCommands[slot]->execute();
            lastCommand = std::move(offCommands[slot]);
        }
    }
    
    void undoButtonPressed() {
        if (lastCommand) {
            lastCommand->undo();
        }
    }
};

// Usage
Light livingRoomLight;
auto lightOn = std::make_unique<LightOnCommand>(livingRoomLight);
auto lightOff = std::make_unique<LightOffCommand>(livingRoomLight);

RemoteControl remote;
remote.setCommand(0, std::move(lightOn), std::move(lightOff));

remote.onButtonPressed(0);
remote.offButtonPressed(0);
remote.undoButtonPressed();
```

## 🚀 Modern C++ Design Patterns

### RAII (Resource Acquisition Is Initialization)
```cpp
// Smart resource management
class FileHandle {
private:
    FILE* file;
    
public:
    FileHandle(const char* filename, const char* mode) {
        file = fopen(filename, mode);
        if (!file) {
            throw std::runtime_error("Failed to open file");
        }
    }
    
    ~FileHandle() {
        if (file) {
            fclose(file);
        }
    }
    
    FILE* get() const { return file; }
    
    // Prevent copying
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
    
    // Allow moving
    FileHandle(FileHandle&& other) noexcept : file(other.file) {
        other.file = nullptr;
    }
    
    FileHandle& operator=(FileHandle&& other) noexcept {
        if (this != &other) {
            if (file) fclose(file);
            file = other.file;
            other.file = nullptr;
        }
        return *this;
    }
};

// Usage
try {
    FileHandle file("data.txt", "r");
    // File automatically closed when file goes out of scope
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

### Type Erasure
```cpp
// Polymorphic behavior without inheritance
class Drawable {
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
    Drawable(T&& obj) : pimpl(std::make_unique<model<T>>(std::forward<T>(obj))) {}
    
    Drawable(const Drawable& other) : pimpl(other.pimpl->clone()) {}
    Drawable& operator=(const Drawable& other) {
        pimpl = other.pimpl->clone();
        return *this;
    }
    
    void draw() const { pimpl->draw(); }
};
```

### CRTP (Curiously Recurring Template Pattern)
```cpp
// Static polymorphism
template<typename Derived>
class Shape {
public:
    double area() const {
        return static_cast<const Derived*>(this)->area_impl();
    }
    
    double perimeter() const {
        return static_cast<const Derived*>(this)->perimeter_impl();
    }
};

class Circle : public Shape<Circle> {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double area_impl() const {
        return M_PI * radius * radius;
    }
    
    double perimeter_impl() const {
        return 2 * M_PI * radius;
    }
};

class Rectangle : public Shape<Rectangle> {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area_impl() const {
        return width * height;
    }
    
    double perimeter_impl() const {
        return 2 * (width + height);
    }
};

// Usage
Circle circle(5.0);
Rectangle rect(3.0, 4.0);

std::cout << "Circle area: " << circle.area() << std::endl;
std::cout << "Rectangle area: " << rect.area() << std::endl;
```

## 📚 Best Practices

### 1. Favor Composition Over Inheritance
```cpp
// ❌ Bad: Deep inheritance hierarchy
class Animal { /* ... */ };
class Mammal : public Animal { /* ... */ };
class Dog : public Mammal { /* ... */ };

// ✅ Good: Composition with interfaces
class Animal { /* ... */ };
class FlyingAbility { /* ... */ };
class SwimmingAbility { /* ... */ };

class Duck : public Animal {
private:
    FlyingAbility flying;
    SwimmingAbility swimming;
};
```

### 2. Use Smart Pointers
```cpp
// ❌ Bad: Raw pointers
class Widget {
private:
    Button* button;
public:
    Widget() : button(new Button()) {}
    ~Widget() { delete button; }
};

// ✅ Good: Smart pointers
class Widget {
private:
    std::unique_ptr<Button> button;
public:
    Widget() : button(std::make_unique<Button>()) {}
    // No destructor needed
};
```

### 3. Prefer Non-Member Functions
```cpp
// ❌ Bad: Member function for utility
class String {
public:
    void clear();
    void trim();  // Utility function as member
};

// ✅ Good: Non-member function
class String {
public:
    void clear();
};

void trim(String& str);  // Utility function as non-member
```

## 📖 Resources

### Books
- "Design Patterns" by Gang of Four
- "Modern C++ Design" by Andrei Alexandrescu
- "Effective C++" by Scott Meyers

### Online Resources
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Design Patterns Reference](https://refactoring.guru/design-patterns)
- [C++ Patterns](https://cpppatterns.com/)

## 🚀 Practice Problems

### Basic Exercises
1. **Factory Pattern**: Implement a shape factory
2. **Observer Pattern**: Build a simple event system
3. **Decorator Pattern**: Create a coffee ordering system

### Intermediate Exercises
1. **Composite Pattern**: Build a file system tree
2. **Strategy Pattern**: Implement different sorting algorithms
3. **Command Pattern**: Create a text editor with undo/redo

### Advanced Exercises
1. **Type Erasure**: Build a polymorphic container
2. **CRTP**: Implement static polymorphism for shapes
3. **Modern Patterns**: Combine multiple patterns in a game engine

---

*Design patterns are tools, not rules. Use them when they solve real problems, not just for the sake of using patterns. The best code is often the simplest code that solves the problem effectively.*
