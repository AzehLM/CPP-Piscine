# C++98 Templates: Comprehensive Learning Guide

*This guide is designed to help you understand C++ template fundamentals through the lens of C++98.
## Introduction: Templates as Code Generators

Templates in C++ are not code themselves - they're instructions for generating code. Think of them as blueprints that the compiler uses to create actual functions or classes when you provide specific types. This happens entirely at compile time, which means you get the benefits of code reuse without any runtime performance penalty.

The power of templates lies in their ability to write type-safe, generic code that works with any compatible type. Unlike macros, templates are fully integrated into C++'s type system, participating in overload resolution and respecting scope rules.

## Function Templates: Your First Step into Generic Programming

Function templates allow you to write a single function that works with multiple types. The compiler generates a new version of the function for each type you use it with - a process called instantiation.

```cpp
// A simple function template
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// When you call it:
int x = maximum(5, 3);      // Compiler generates: int maximum(int, int)
double y = maximum(2.5, 1.7); // Compiler generates: double maximum(double, double)
```

The beauty here is that the compiler performs **template argument deduction** - it figures out what `T` should be based on the arguments you pass. This is why you don't need to write `maximum<int>(5, 3)` (though you can if you want to be explicit).

### Understanding Template Parameters and Arguments

It's crucial to distinguish between template parameters (the placeholders in your template definition) and template arguments (the actual types or values you provide):

```cpp
template<typename T>  // T is a template parameter
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Usage:
int p = 5, q = 10;
maximum(p, q);          // int is the template argument (deduced)
maximum<int>(p, q);     // int is the template argument (explicit)
```

## The Two-Phase Compilation Model

Understanding how templates compile is essential for debugging. The compiler processes templates in two phases:

**Phase 1** occurs when the compiler first sees the template definition. It checks syntax and resolves names that don't depend on template parameters (non-dependent names).

**Phase 2** happens during instantiation when you actually use the template with specific types. This is when dependent names are resolved and type-specific code is generated.

```cpp
template<typename T>
class Container {
    void method() {
        int x = 5;           // Non-dependent: checked in phase 1
        T value;             // Dependent on T: checked in phase 2
        value.doSomething(); // Dependent: only checked when T is known
    }
};
```

This two-phase model explains why template definitions typically need to be in header files - the compiler needs to see the full definition whenever it instantiates the template.

## Class Templates: Building Generic Data Structures

Class templates extend the concept to entire classes, allowing you to create data structures that work with any type:

```cpp
template<typename T>
class Array {
private:
    T* data;
    size_t size_;

public:
    explicit Array(size_t n) : size_(n), data(new T[n]) {}

    ~Array() { delete[] data; }

    // Copy constructor - crucial for proper resource management
    Array(const Array& other) : size_(other.size_), data(new T[size_]) {
        for (size_t i = 0; i < size_; ++i)
            data[i] = other.data[i];
    }

    T& operator[](size_t index) {
        return data[index];
    }

    size_t size() const { return size_; }
};

// Usage:
Array<int> intArray(10);     // Array of integers
Array<double> doubleArray(5); // Array of doubles
```

Notice how resource management (RAII) becomes critical in template contexts. Your template must work correctly for any type `T`, whether it's a simple type like `int` or a complex class with its own resources.

## The typename Keyword: A Common Source of Confusion

One of the most frequent errors in template programming involves dependent types. When you refer to a type that depends on a template parameter, you must use the `typename` keyword to tell the compiler it's a type:

```cpp
template<typename T>
class Example {
    // Without typename, compiler assumes T::value_type is a static member
    // typename T::value_type item;  // Correct
    // T::value_type item;           // Error!

    void process() {
        typename T::iterator it;  // typename required for dependent type
    }
};
```

This requirement stems from the two-phase compilation model. During phase 1, the compiler doesn't know what `T` is, so it can't determine whether `T::something` is a type, a static member variable, or something else.

## Non-Type Template Parameters: Beyond Types

Templates can accept compile-time constant values as parameters, not just types:

```cpp
template<typename T, int SIZE>
class FixedArray {
    T data[SIZE];  // SIZE must be known at compile time

public:
    T& operator[](int index) {
        return data[index];
    }

    int size() const { return SIZE; }
};

// Creates different classes for different sizes
FixedArray<int, 10> small;
FixedArray<int, 100> large;
// These are completely different types!
```

This feature enables compile-time optimization and type safety for fixed-size containers.

## Template Specialization: Handling Special Cases

Sometimes you need different implementations for specific types. Template specialization allows you to provide custom implementations:

```cpp
// Primary template
template<typename T>
class Storage {
    T value;
public:
    void store(T v) { value = v; }
    T retrieve() { return value; }
};

// Full specialization for bool (optimize for space)
template<>
class Storage<bool> {
    unsigned char value;  // Store as single byte
public:
    void store(bool v) { value = v ? 1 : 0; }
    bool retrieve() { return value != 0; }
};
```

This technique is used extensively in the STL - for example, `std::vector<bool>` is a specialization that packs bools into bits for space efficiency.

## Implicit Interfaces and Compile-Time Polymorphism

Templates provide compile-time polymorphism through implicit interfaces. Unlike inheritance-based polymorphism, there's no explicit interface declaration:

```cpp
template<typename T>
void process(T& obj) {
    obj.doWork();    // T must have a doWork() method
    obj.getValue();  // T must have a getValue() method
}

// Any type with the required methods works:
class Worker {
public:
    void doWork() { /* ... */ }
    int getValue() { return 42; }
};

class Robot {
public:
    void doWork() { /* ... */ }
    double getValue() { return 3.14; }
};

// Both work with the template
Worker w;
Robot r;
process(w);  // OK
process(r);  // OK
```

This is powerful but requires careful documentation of what operations your template expects from its type parameters.

## Template Definition Organization: The Header-Only Reality

Due to the instantiation model, template definitions typically must be visible where they're used:

```cpp
// array.hpp - Everything in the header
template<typename T>
class Array {
public:
    Array(size_t n);
    T& operator[](size_t i);
    // ...
};

// Definitions must be in the header too
template<typename T>
Array<T>::Array(size_t n) {
    // Implementation here
}

template<typename T>
T& Array<T>::operator[](size_t i) {
    // Implementation here
}
```

This requirement often surprises newcomers who try to separate declarations and definitions as they would with regular classes. The compiler needs the complete template definition to instantiate it for specific types.

## Static Polymorphism: The Zero-Cost Abstraction

Templates enable static (compile-time) polymorphism, providing abstraction without virtual function overhead:

```cpp
// Runtime polymorphism (virtual functions)
class Shape {
public:
    virtual double area() = 0;  // Virtual function overhead
};

// Static polymorphism (templates)
template<typename Shape>
double calculateTotalArea(Shape* shapes, int count) {
    double total = 0;
    for (int i = 0; i < count; ++i) {
        total += shapes[i].area();  // No virtual call overhead
    }
    return total;
}
```

The template version generates specialized code for each shape type, eliminating virtual function calls while maintaining polymorphic behavior.

## Common Pitfalls and Their Solutions

### Dependent Name Lookup

When inheriting from template base classes, you must explicitly qualify base class members:

```cpp
template<typename T>
class Base {
protected:
    void helper() { }
};

template<typename T>
class Derived : public Base<T> {
    void method() {
        // helper();           // Error: not found
        this->helper();        // OK: tells compiler it's dependent
        Base<T>::helper();     // OK: explicitly qualified
    }
};
```

### Template Instantiation Errors

Template errors often produce verbose, difficult-to-read messages. The key is to read from the bottom up, looking for the actual error before examining the instantiation chain:

```cpp
template<typename T>
void requiresSize(T& container) {
    size_t s = container.size();  // T must have size() method
}

struct NoSize {};
NoSize ns;
// requiresSize(ns);  // Error: NoSize has no member 'size'
```

## Performance Considerations: Code Bloat vs. Optimization

Templates generate separate code for each instantiation, which can lead to larger executables:

```cpp
// Each instantiation creates new code
Array<int> intArr(10);     // Generates Array<int> code
Array<double> dblArr(10);   // Generates Array<double> code
Array<char> charArr(10);    // Generates Array<char> code
```

However, this also enables perfect optimization for each type. The compiler can inline functions, optimize for specific type sizes, and eliminate unnecessary operations.

## Best Practices for Template Design

When designing templates, think carefully about the requirements you're placing on type parameters. Document these requirements clearly, as they form the implicit interface:

```cpp
// Document requirements clearly
template<typename T>
class Stack {
    // Requirements for T:
    // - Must be copy-constructible
    // - Must be assignable
    // - Should have a default constructor for some operations

private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(0) {}
    };

    Node* top;

public:
    Stack() : top(0) {}

    void push(const T& item) {
        Node* newNode = new Node(item);  // T must be copy-constructible
        newNode->next = top;
        top = newNode;
    }

    ~Stack() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};
```

## From C++98 constraints to modern features

Understanding the evolution toward modern C++ helps appreciating template programming's trajectory. **C++11's auto keyword**, **C++14's variable templates**, **C++17's template argument deduction**, and **C++20's concepts** are all build upon the fundamental principles.

Modern features like **constexpr**, **perfect forwarding**, and **variadic templates** extend the basic template concepts and prepares them for professional C++ development.

### Concept-driven design principles

**Concept-driven thinking** helps writing better template code. Teaching how to think about **implicit interfaces** (what operations a type must support) rather than just explicit interfaces (inheritance hierarchies) prepares for advanced template programming.

## Advanced template patterns preview

### CRTP and static polymorphism

The **Curiously Recurring Template Pattern** enables **compile-time polymorphism** without virtual function overhead. Understanding CRTP prepares for advanced design patterns used in high-performance C++ libraries.

### Policy-based design

**Policy-based design** allows orthogonal template parameters to control different aspects of class behavior independently. This advanced pattern demonstrates the compositional power of templates for creating flexible, reusable designs.

## Conclusion: Templates as a Foundation

Templates in C++98 establish the foundation for generic programming that continues to evolve in modern C++. They provide zero-cost abstraction, enabling you to write code that's both generic and efficient. The concepts you master here - instantiation, specialization, dependent names, and implicit interfaces - remain fundamental even as the language adds new features.

Understanding templates deeply means understanding how the compiler thinks about your code. It means recognizing that templates are patterns for generating code, not code themselves. This mental model helps you write better templates, debug template errors more effectively, and design more flexible software architectures.

The journey from writing your first `swap` function template to designing complex generic data structures mirrors the evolution of C++ itself - from a language with classes to one of the most powerful tools for generic programming. Your understanding of these C++98 template fundamentals provides the solid foundation needed for any advanced C++ development.
