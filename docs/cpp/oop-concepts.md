# 🚀 C++ Object-Oriented Programming: Complete Guide

## 📚 Overview

Object-Oriented Programming (OOP) is a programming paradigm that organizes code into objects containing data and behavior. C++ provides powerful OOP features that enable you to write modular, reusable, and maintainable code.

## 🎯 Key Concepts

### What is OOP?
- **Objects**: Instances of classes containing data and methods
- **Classes**: Blueprints for creating objects
- **Encapsulation**: Bundling data and methods that operate on that data
- **Inheritance**: Creating new classes from existing ones
- **Polymorphism**: Using objects of different types through a common interface

### OOP Principles
- **Encapsulation**: Hide internal state and require all interaction through methods
- **Inheritance**: Establish relationships between classes
- **Polymorphism**: Allow objects to be treated as instances of their parent class
- **Abstraction**: Hide complex implementation details

## 🏗️ Classes and Objects

### Basic Class Definition
```cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    // Private members (encapsulation)
    string name;
    int age;
    
public:
    // Public interface
    Person() : name(""), age(0) {}  // Default constructor
    
    Person(const string& n, int a) : name(n), age(a) {}  // Parameterized constructor
    
    // Copy constructor
    Person(const Person& other) : name(other.name), age(other.age) {}
    
    // Destructor
    ~Person() {
        cout << "Person " << name << " destroyed" << endl;
    }
    
    // Member functions
    void setName(const string& n) { name = n; }
    string getName() const { return name; }
    
    void setAge(int a) { 
        if (a >= 0) age = a; 
    }
    int getAge() const { return age; }
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main() {
    // Create objects
    Person person1;                    // Default constructor
    Person person2("Alice", 25);       // Parameterized constructor
    Person person3 = person2;          // Copy constructor
    
    // Use objects
    person1.setName("Bob");
    person1.setAge(30);
    
    person1.display();
    person2.display();
    person3.display();
    
    return 0;
}
```

### Access Specifiers
```cpp
class Example {
public:
    // Public members accessible from anywhere
    int publicVar;
    void publicFunction() {}
    
protected:
    // Protected members accessible from this class and derived classes
    int protectedVar;
    void protectedFunction() {}
    
private:
    // Private members accessible only from this class
    int privateVar;
    void privateFunction() {}
};
```

### Constructor Types
```cpp
class Rectangle {
private:
    int width, height;
    
public:
    // Default constructor
    Rectangle() : width(0), height(0) {}
    
    // Parameterized constructor
    Rectangle(int w, int h) : width(w), height(h) {}
    
    // Copy constructor
    Rectangle(const Rectangle& other) : width(other.width), height(other.height) {}
    
    // Move constructor (C++11)
    Rectangle(Rectangle&& other) noexcept 
        : width(other.width), height(other.height) {
        other.width = 0;
        other.height = 0;
    }
    
    // Assignment operator
    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
        }
        return *this;
    }
    
    // Move assignment operator (C++11)
    Rectangle& operator=(Rectangle&& other) noexcept {
        if (this != &other) {
            width = other.width;
            height = other.height;
            other.width = 0;
            other.height = 0;
        }
        return *this;
    }
    
    // Destructor
    ~Rectangle() {}
    
    // Member functions
    int getArea() const { return width * height; }
    int getPerimeter() const { return 2 * (width + height); }
};
```

## 🔄 Inheritance

### Basic Inheritance
```cpp
class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(const string& n, int a) : name(n), age(a) {}
    
    virtual void makeSound() const {
        cout << "Some animal sound" << endl;
    }
    
    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    // Virtual destructor for proper cleanup
    virtual ~Animal() {}
};

class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(const string& n, int a, const string& b) 
        : Animal(n, a), breed(b) {}
    
    void makeSound() const override {
        cout << "Woof! Woof!" << endl;
    }
    
    void display() const override {
        Animal::display();  // Call base class method
        cout << "Breed: " << breed << endl;
    }
    
    void fetch() {
        cout << name << " is fetching the ball" << endl;
    }
};

class Cat : public Animal {
private:
    bool isIndoor;
    
public:
    Cat(const string& n, int a, bool indoor) 
        : Animal(n, a), isIndoor(indoor) {}
    
    void makeSound() const override {
        cout << "Meow!" << endl;
    }
    
    void display() const override {
        Animal::display();
        cout << "Indoor: " << (isIndoor ? "Yes" : "No") << endl;
    }
    
    void purr() {
        cout << name << " is purring" << endl;
    }
};
```

### Inheritance Types
```cpp
// Public inheritance (most common)
class PublicDerived : public Base {
    // Public members of Base become public in Derived
    // Protected members of Base become protected in Derived
    // Private members of Base remain inaccessible
};

// Protected inheritance
class ProtectedDerived : protected Base {
    // Public and protected members of Base become protected in Derived
    // Private members of Base remain inaccessible
};

// Private inheritance
class PrivateDerived : private Base {
    // Public and protected members of Base become private in Derived
    // Private members of Base remain inaccessible
};
```

### Multiple Inheritance
```cpp
class Flyable {
public:
    virtual void fly() = 0;  // Pure virtual function
    virtual ~Flyable() {}
};

class Swimmable {
public:
    virtual void swim() = 0;  // Pure virtual function
    virtual ~Swimmable() {}
};

class Duck : public Animal, public Flyable, public Swimmable {
public:
    Duck(const string& n, int a) : Animal(n, a) {}
    
    void makeSound() const override {
        cout << "Quack! Quack!" << endl;
    }
    
    void fly() override {
        cout << name << " is flying" << endl;
    }
    
    void swim() override {
        cout << name << " is swimming" << endl;
    }
};
```

## 🎭 Polymorphism

### Virtual Functions
```cpp
class Shape {
public:
    virtual double getArea() const = 0;      // Pure virtual function
    virtual double getPerimeter() const = 0; // Pure virtual function
    virtual void display() const = 0;        // Pure virtual function
    
    virtual ~Shape() {}  // Virtual destructor
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double getArea() const override {
        return 3.14159 * radius * radius;
    }
    
    double getPerimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void display() const override {
        cout << "Circle - Radius: " << radius 
             << ", Area: " << getArea() 
             << ", Perimeter: " << getPerimeter() << endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double getArea() const override {
        return width * height;
    }
    
    double getPerimeter() const override {
        return 2 * (width + height);
    }
    
    void display() const override {
        cout << "Rectangle - Width: " << width 
             << ", Height: " << height
             << ", Area: " << getArea() 
             << ", Perimeter: " << getPerimeter() << endl;
    }
};
```

### Runtime Polymorphism
```cpp
void processShape(const Shape& shape) {
    shape.display();  // Calls appropriate derived class method
}

int main() {
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);
    
    // Polymorphic behavior
    processShape(circle);      // Calls Circle::display()
    processShape(rectangle);   // Calls Rectangle::display()
    
    // Array of shapes
    Shape* shapes[] = {&circle, &rectangle};
    
    for (Shape* shape : shapes) {
        shape->display();  // Polymorphic calls
    }
    
    return 0;
}
```

### Function Overriding vs Overloading
```cpp
class Base {
public:
    // Function overloading (same name, different parameters)
    void display() const {
        cout << "Base display()" << endl;
    }
    
    void display(int value) const {
        cout << "Base display(" << value << ")" << endl;
    }
    
    // Virtual function for overriding
    virtual void show() const {
        cout << "Base show()" << endl;
    }
};

class Derived : public Base {
public:
    // Function overriding (same signature, different implementation)
    void show() const override {
        cout << "Derived show()" << endl;
    }
    
    // Function overloading in derived class
    void display(const string& message) const {
        cout << "Derived display: " << message << endl;
    }
};
```

## 🔒 Encapsulation

### Data Hiding
```cpp
class BankAccount {
private:
    string accountNumber;
    double balance;
    string password;
    
    // Private helper methods
    bool isValidPassword(const string& pwd) const {
        return pwd == password;
    }
    
    void logTransaction(const string& type, double amount) {
        // Internal logging logic
        cout << "Transaction: " << type << " $" << amount << endl;
    }
    
public:
    BankAccount(const string& accNum, const string& pwd, double initialBalance = 0.0)
        : accountNumber(accNum), password(pwd), balance(initialBalance) {}
    
    // Public interface
    bool deposit(double amount, const string& pwd) {
        if (!isValidPassword(pwd) || amount <= 0) {
            return false;
        }
        
        balance += amount;
        logTransaction("Deposit", amount);
        return true;
    }
    
    bool withdraw(double amount, const string& pwd) {
        if (!isValidPassword(pwd) || amount <= 0 || amount > balance) {
            return false;
        }
        
        balance -= amount;
        logTransaction("Withdrawal", amount);
        return true;
    }
    
    double getBalance(const string& pwd) const {
        if (!isValidPassword(pwd)) {
            return -1;  // Invalid password
        }
        return balance;
    }
    
    string getAccountNumber() const {
        return accountNumber;
    }
};
```

### Getters and Setters
```cpp
class Student {
private:
    string name;
    int age;
    double gpa;
    
public:
    // Constructor
    Student(const string& n, int a, double g) : name(n), age(a), gpa(g) {}
    
    // Getters (const methods)
    string getName() const { return name; }
    int getAge() const { return age; }
    double getGPA() const { return gpa; }
    
    // Setters with validation
    void setName(const string& n) {
        if (!n.empty()) {
            name = n;
        }
    }
    
    void setAge(int a) {
        if (a >= 0 && a <= 120) {
            age = a;
        }
    }
    
    void setGPA(double g) {
        if (g >= 0.0 && g <= 4.0) {
            gpa = g;
        }
    }
};
```

## 🚀 Advanced OOP Features

### Static Members
```cpp
class Counter {
private:
    static int totalCount;  // Static member variable
    int instanceCount;
    
public:
    Counter() : instanceCount(0) {
        totalCount++;
    }
    
    ~Counter() {
        totalCount--;
    }
    
    // Static member function
    static int getTotalCount() {
        return totalCount;
    }
    
    void increment() {
        instanceCount++;
    }
    
    int getInstanceCount() const {
        return instanceCount;
    }
};

// Define static member variable
int Counter::totalCount = 0;

int main() {
    Counter c1, c2, c3;
    
    cout << "Total counters: " << Counter::getTotalCount() << endl;  // 3
    
    c1.increment();
    c2.increment();
    c2.increment();
    
    cout << "C1 count: " << c1.getInstanceCount() << endl;  // 1
    cout << "C2 count: " << c2.getInstanceCount() << endl;  // 2
    cout << "C3 count: " << c3.getInstanceCount() << endl;  // 0
    
    return 0;
}
```

### Friend Functions and Classes
```cpp
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Friend function (can access private members)
    friend Complex add(const Complex& a, const Complex& b);
    
    // Friend class
    friend class ComplexCalculator;
    
    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

// Friend function implementation
Complex add(const Complex& a, const Complex& b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}

// Friend class
class ComplexCalculator {
public:
    static Complex multiply(const Complex& a, const Complex& b) {
        double real = a.real * b.real - a.imag * b.imag;
        double imag = a.real * b.imag + a.imag * b.real;
        return Complex(real, imag);
    }
};
```

### Abstract Classes and Interfaces
```cpp
// Abstract base class (interface)
class Drawable {
public:
    virtual void draw() const = 0;  // Pure virtual function
    virtual void resize(double factor) = 0;
    virtual ~Drawable() {}
};

class Circle : public Drawable {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    void draw() const override {
        cout << "Drawing circle with radius " << radius << endl;
    }
    
    void resize(double factor) override {
        radius *= factor;
    }
};

class Square : public Drawable {
private:
    double side;
    
public:
    Square(double s) : side(s) {}
    
    void draw() const override {
        cout << "Drawing square with side " << side << endl;
    }
    
    void resize(double factor) override {
        side *= factor;
    }
};
```

## 📝 Best Practices

### 1. Use Virtual Destructors
```cpp
class Base {
public:
    virtual ~Base() {}  // Virtual destructor for proper cleanup
};

class Derived : public Base {
public:
    ~Derived() override {}  // Override destructor
};
```

### 2. Follow the Rule of Three/Five
```cpp
class ResourceManager {
private:
    int* data;
    size_t size;
    
public:
    // Constructor
    ResourceManager(size_t s) : size(s) {
        data = new int[s];
    }
    
    // Destructor
    ~ResourceManager() {
        delete[] data;
    }
    
    // Copy constructor
    ResourceManager(const ResourceManager& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // Copy assignment operator
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Move constructor (C++11)
    ResourceManager(ResourceManager&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
    
    // Move assignment operator (C++11)
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
};
```

### 3. Use Const Correctness
```cpp
class Calculator {
private:
    mutable int callCount;  // Can be modified even in const methods
    
public:
    Calculator() : callCount(0) {}
    
    // Const method - doesn't modify object state
    int add(int a, int b) const {
        callCount++;  // OK because callCount is mutable
        return a + b;
    }
    
    // Non-const method - can modify object state
    void reset() {
        callCount = 0;
    }
    
    int getCallCount() const {
        return callCount;
    }
};
```

## 🎯 Practice Problems

### Problem 1: Shape Hierarchy
```cpp
class Shape {
public:
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual ~Shape() {}
};

class Triangle : public Shape {
private:
    double a, b, c;
    
public:
    Triangle(double side1, double side2, double side3) 
        : a(side1), b(side2), c(side3) {}
    
    double getArea() const override {
        double s = (a + b + c) / 2;  // Semi-perimeter
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    
    double getPerimeter() const override {
        return a + b + c;
    }
};
```

### Problem 2: Bank Account System
```cpp
class Account {
protected:
    string accountNumber;
    double balance;
    
public:
    Account(const string& accNum, double initialBalance = 0.0)
        : accountNumber(accNum), balance(initialBalance) {}
    
    virtual void deposit(double amount) = 0;
    virtual bool withdraw(double amount) = 0;
    virtual double getBalance() const = 0;
    virtual ~Account() {}
};

class SavingsAccount : public Account {
private:
    double interestRate;
    
public:
    SavingsAccount(const string& accNum, double initialBalance, double rate)
        : Account(accNum, initialBalance), interestRate(rate) {}
    
    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    bool withdraw(double amount) override {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    double getBalance() const override {
        return balance;
    }
    
    void addInterest() {
        balance += balance * interestRate;
    }
};
```

### Problem 3: Employee Management
```cpp
class Employee {
protected:
    string name;
    int id;
    double salary;
    
public:
    Employee(const string& n, int i, double s) 
        : name(n), id(i), salary(s) {}
    
    virtual double calculatePay() const = 0;
    virtual void display() const = 0;
    virtual ~Employee() {}
};

class SalariedEmployee : public Employee {
private:
    double annualSalary;
    
public:
    SalariedEmployee(const string& n, int i, double annual)
        : Employee(n, i, 0), annualSalary(annual) {}
    
    double calculatePay() const override {
        return annualSalary / 12;  // Monthly salary
    }
    
    void display() const override {
        cout << "Salaried Employee: " << name 
             << " (ID: " << id << "), Monthly Pay: $" 
             << calculatePay() << endl;
    }
};

class HourlyEmployee : public Employee {
private:
    double hourlyRate;
    int hoursWorked;
    
public:
    HourlyEmployee(const string& n, int i, double rate, int hours)
        : Employee(n, i, 0), hourlyRate(rate), hoursWorked(hours) {}
    
    double calculatePay() const override {
        return hourlyRate * hoursWorked;
    }
    
    void display() const override {
        cout << "Hourly Employee: " << name 
             << " (ID: " << id << "), Pay: $" 
             << calculatePay() << endl;
    }
};
```

## 📚 Summary

Key takeaways:
- **Classes encapsulate data and behavior** for better organization
- **Inheritance establishes relationships** between classes
- **Polymorphism enables flexible, extensible code**
- **Virtual functions enable runtime binding**
- **Use RAII and smart pointers** for resource management
- **Follow OOP principles** for maintainable code

Master these concepts to write professional, object-oriented C++ code!

---

## 🔗 Related Topics
- [Functions](functions.md)
- [Templates](templates.md)
- [Smart Pointers](smart-pointers.md)
- [Exception Handling](exception-handling.md)
