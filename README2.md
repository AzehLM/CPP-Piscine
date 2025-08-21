# C++ Templates Mastery Guide - CPP07 Module

## Table of Contents
1. [Template Fundamentals](#template-fundamentals)
2. [Function Templates](#function-templates)
3. [Class Templates](#class-templates)
4. [Template Specialization](#template-specialization)
5. [Template Argument Deduction](#template-argument-deduction)
6. [SFINAE and Concepts](#sfinae-and-concepts)
7. [Advanced Template Techniques](#advanced-template-techniques)
8. [Template Instantiation Process](#template-instantiation-process)
9. [Modern C++ Template Features](#modern-cpp-template-features)
10. [Performance and Best Practices](#performance-and-best-practices)
11. [Common Pitfalls and Debugging](#common-pitfalls-and-debugging)
12. [Real-World Applications](#real-world-applications)

---

## Template Fundamentals

### Understanding generic programming

Templates are C++'s mechanism for **generic programming** - writing code that works with multiple types without sacrificing type safety or performance. Unlike macros, templates are fully integrated into the type system and participate in overload resolution, scope rules, and all other language features.

**Why templates matter:**
- **Zero-cost abstraction**: Templates generate optimized code for each type used
- **Type safety**: All type checking happens at compile time
- **Code reuse**: Write algorithms once, use with any compatible type
- **Performance**: No runtime overhead compared to hand-written type-specific code

### The template instantiation model

Templates are not code - they're **instructions for generating code**. When you use a template with specific types, the compiler creates a new function or class through **instantiation**.

```cpp
template<typename T>
T add(T a, T b) {
    return a + b;    // Template definition
}

int main() {
    int x = add(5, 3);        // Instantiates add<int>
    double y = add(2.5, 1.5); // Instantiates add<double>

    // Compiler generates:
    // int add(int a, int b) { return a + b; }
    // double add(double a, double b) { return a + b; }
}
```

This happens at **compile time** - no runtime performance cost.

### Template syntax and terminology

```cpp
template<typename T>        // Template parameter declaration
//        ^^^^^^^^^
//        Template parameter (T is a type parameter)

T function_name(T param) {  // Template definition
// ^
// Return type uses template parameter
    return param;
}

// Usage:
function_name<int>(42);     // Explicit instantiation
//            ^^^
//            Template argument

function_name(42);          // Implicit instantiation (deduction)
```

**Key terminology:**
- **Template parameter**: The placeholder in the template definition (`T`)
- **Template argument**: The actual type/value provided (`int`)
- **Instantiation**: Process of generating concrete code from template
- **Specialization**: Providing custom implementation for specific types

---

## Function Templates

### Basic function template syntax

Function templates allow you to write generic functions that work with multiple types:

```cpp
#include <iostream>
#include <string>

// Basic function template
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Multiple template parameters
template<typename T, typename U>
auto add_different_types(T a, U b) -> decltype(a + b) {
    return a + b;
}

int main() {
    // Type is deduced from arguments
    std::cout << maximum(10, 20) << std::endl;           // int version
    std::cout << maximum(3.14, 2.71) << std::endl;      // double version
    std::cout << maximum('a', 'z') << std::endl;        // char version

    // Multiple types
    std::cout << add_different_types(42, 3.14) << std::endl;  // int + double

    return 0;
}
```

### Template argument deduction

The compiler can automatically deduce template parameters from function arguments:

```cpp
template<typename T>
void process_value(T value) {
    std::cout << "Processing: " << value << std::endl;
}

template<typename Container>
void print_container(const Container& c) {
    for (const auto& element : c) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    process_value(42);        // T deduced as int
    process_value(3.14);      // T deduced as double
    process_value("hello");   // T deduced as const char*

    std::vector<int> vec = {1, 2, 3, 4, 5};
    print_container(vec);     // Container deduced as std::vector<int>

    return 0;
}
```

### Non-type template parameters

Templates can accept values as well as types:

```cpp
#include <array>
#include <iostream>

// Non-type template parameter for array size
template<typename T, size_t N>
class FixedArray {
private:
    T data[N];

public:
    constexpr size_t size() const { return N; }

    T& operator[](size_t index) {
        if (index >= N) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= N) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    // Range-based for support
    T* begin() { return data; }
    T* end() { return data + N; }
    const T* begin() const { return data; }
    const T* end() const { return data + N; }
};

// Function with non-type parameter
template<int Power>
constexpr int power_of_two() {
    static_assert(Power >= 0, "Power must be non-negative");
    return 1 << Power;  // 2^Power
}

int main() {
    FixedArray<int, 5> arr;
    arr[0] = 10;
    arr[1] = 20;

    std::cout << "Array size: " << arr.size() << std::endl;

    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = i * i;
    }

    for (const auto& element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Compile-time computation
    constexpr int result = power_of_two<4>();  // 16
    std::cout << "2^4 = " << result << std::endl;

    return 0;
}
```

---

## Class Templates

### Basic class template structure

Class templates define blueprints for classes that can work with different types:

```cpp
#include <iostream>
#include <stdexcept>

template<typename T>
class Stack {
private:
    static const size_t DEFAULT_CAPACITY = 10;
    T* data;
    size_t capacity;
    size_t current_size;

    void resize() {
        capacity *= 2;
        T* new_data = new T[capacity];

        // Move existing elements
        for (size_t i = 0; i < current_size; ++i) {
            new_data[i] = std::move(data[i]);
        }

        delete[] data;
        data = new_data;
    }

public:
    // Constructor
    explicit Stack(size_t initial_capacity = DEFAULT_CAPACITY)
        : data(new T[initial_capacity])
        , capacity(initial_capacity)
        , current_size(0) {
        std::cout << "Stack created with capacity: " << capacity << std::endl;
    }

    // Destructor
    ~Stack() {
        delete[] data;
        std::cout << "Stack destroyed" << std::endl;
    }

    // Copy constructor
    Stack(const Stack& other)
        : data(new T[other.capacity])
        , capacity(other.capacity)
        , current_size(other.current_size) {
        for (size_t i = 0; i < current_size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Assignment operator
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] data;

            capacity = other.capacity;
            current_size = other.current_size;
            data = new T[capacity];

            for (size_t i = 0; i < current_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Push element
    void push(const T& item) {
        if (current_size >= capacity) {
            resize();
        }
        data[current_size++] = item;
    }

    // Pop element
    T pop() {
        if (empty()) {
            throw std::runtime_error("Cannot pop from empty stack");
        }
        return data[--current_size];
    }

    // Top element (without removing)
    T& top() {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data[current_size - 1];
    }

    const T& top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data[current_size - 1];
    }

    // Utility functions
    bool empty() const { return current_size == 0; }
    size_t size() const { return current_size; }

    // Debug function
    void print() const {
        std::cout << "Stack contents (bottom to top): ";
        for (size_t i = 0; i < current_size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};
```

### Member function templates

Class members can themselves be templates:

```cpp
template<typename T>
class Container {
private:
    std::vector<T> data;

public:
    // Regular member function
    void add(const T& item) {
        data.push_back(item);
    }

    // Member function template for type conversion
    template<typename U>
    void add_converted(const U& item) {
        data.push_back(static_cast<T>(item));
    }

    // Member function template for iterator ranges
    template<typename Iterator>
    void assign_from_range(Iterator first, Iterator last) {
        data.clear();
        while (first != last) {
            data.push_back(static_cast<T>(*first));
            ++first;
        }
    }

    void print() const {
        std::cout << "Container: ";
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    size_t size() const { return data.size(); }
};
```

---

## Template Specialization

### Full template specialization

Sometimes you need different implementations for specific types:

```cpp
// Primary template
template<typename T>
class TypeInfo {
public:
    static void print_info() {
        std::cout << "Generic type, size: " << sizeof(T) << " bytes" << std::endl;
    }

    static bool is_numeric() {
        return false;
    }

    static const char* type_name() {
        return "unknown";
    }
};

// Full specialization for int
template<>
class TypeInfo<int> {
public:
    static void print_info() {
        std::cout << "Integer type, size: " << sizeof(int)
                  << " bytes, range: " << INT_MIN << " to " << INT_MAX << std::endl;
    }

    static bool is_numeric() {
        return true;
    }

    static const char* type_name() {
        return "integer";
    }
};

// Full specialization for const char*
template<>
class TypeInfo<const char*> {
public:
    static void print_info() {
        std::cout << "C-style string (const char*)" << std::endl;
    }

    static bool is_numeric() {
        return false;
    }

    static const char* type_name() {
        return "c_string";
    }
};
```

### Partial template specialization

Partial specialization allows you to specialize templates for patterns of types:

```cpp
// Primary template
template<typename T, typename U>
class Converter {
public:
    static U convert(const T& value) {
        std::cout << "Generic conversion" << std::endl;
        return static_cast<U>(value);
    }
};

// Partial specialization: when both types are the same
template<typename T>
class Converter<T, T> {
public:
    static T convert(const T& value) {
        std::cout << "Identity conversion (same type)" << std::endl;
        return value;
    }
};

// Partial specialization: converting from any type to string
template<typename T>
class Converter<T, std::string> {
public:
    static std::string convert(const T& value) {
        std::cout << "Converting to string" << std::endl;
        return std::to_string(value);
    }
};
```

---

## Template Argument Deduction

### How template argument deduction works

Template argument deduction is the process by which the compiler automatically determines template parameters from function arguments:

```cpp
// Simple deduction examples
template<typename T>
void print_type_info(T value) {
    std::cout << "Type: " << typeid(T).name()
              << ", Value: " << value
              << ", Size: " << sizeof(T) << " bytes" << std::endl;
}

template<typename T>
void analyze_reference(T& ref) {
    std::cout << "Reference parameter - Type: " << typeid(T).name() << std::endl;
}

template<typename T>
void analyze_const_reference(const T& ref) {
    std::cout << "Const reference parameter - Type: " << typeid(T).name() << std::endl;
}

// Deduction with multiple parameters
template<typename T, typename U>
void compare_types(T first, U second) {
    std::cout << "First type: " << typeid(T).name()
              << ", Second type: " << typeid(U).name();

    if (std::is_same_v<T, U>) {
        std::cout << " (same types)";
    } else {
        std::cout << " (different types)";
    }
    std::cout << std::endl;
}

// Deduction with return type
template<typename T, typename U>
auto add_values(T a, U b) -> decltype(a + b) {
    auto result = a + b;
    std::cout << "Adding " << typeid(T).name() << " and " << typeid(U).name()
              << " -> " << typeid(decltype(result)).name() << std::endl;
    return result;
}
```

---

## SFINAE and Concepts

### SFINAE (Substitution Failure Is Not An Error)

SFINAE is a fundamental principle that allows template code to gracefully handle type mismatches:

```cpp
// Basic SFINAE example with enable_if
template<typename T>
typename std::enable_if_t<std::is_integral_v<T>, void>
process_number(T value) {
    std::cout << "Processing integer: " << value << std::endl;
}

template<typename T>
typename std::enable_if_t<std::is_floating_point_v<T>, void>
process_number(T value) {
    std::cout << "Processing floating point: " << value << std::endl;
}

// SFINAE with return type
template<typename T>
auto get_size(T&& container) -> decltype(container.size()) {
    std::cout << "Container has size() method" << std::endl;
    return container.size();
}

template<typename T>
auto get_size(...) -> size_t {
    std::cout << "Container doesn't have size() method, returning 0" << std::endl;
    return 0;
}
```

### C++20 Concepts - Modern Alternative to SFINAE

Concepts provide a cleaner, more expressive way to constrain templates:

```cpp
// Basic concepts
template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<typename T>
concept Numeric = Integral<T> || FloatingPoint<T>;

// More complex concepts
template<typename T>
concept Printable = requires(T t) {
    std::cout << t;  // T must be printable to cout
};

template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
};

// Using concepts
template<Integral T>
void process_integer(T value) {
    std::cout << "Processing integer: " << value << std::endl;
}

template<FloatingPoint T>
void process_float(T value) {
    std::cout << "Processing float: " << value << std::endl;
}
```

---

## Advanced Template Techniques

### Variadic Templates and Parameter Packs

Variadic templates allow functions and classes to accept a variable number of arguments:

```cpp
// Basic variadic function template
template<typename... Args>
void print_values(Args... args) {
    // C++17 fold expression
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}

// Variadic class template - tuple implementation
template<typename... Types>
class MyTuple;

// Specialization for empty tuple
template<>
class MyTuple<> {
public:
    static constexpr size_t size() { return 0; }
};

// Recursive specialization
template<typename Head, typename... Tail>
class MyTuple<Head, Tail...> {
private:
    Head head;
    MyTuple<Tail...> tail;

public:
    MyTuple() = default;
    MyTuple(const Head& h, const Tail&... t) : head(h), tail(t...) {}

    static constexpr size_t size() { return 1 + MyTuple<Tail...>::size(); }

    Head& get_head() { return head; }
    const Head& get_head() const { return head; }

    MyTuple<Tail...>& get_tail() { return tail; }
    const MyTuple<Tail...>& get_tail() const { return tail; }
};
```

### CRTP (Curiously Recurring Template Pattern)

CRTP enables static polymorphism and compile-time interface enforcement:

```cpp
// Basic CRTP example - Adding functionality to derived classes
template<typename Derived>
class Countable {
private:
    static size_t count;

public:
    Countable() { ++count; }
    Countable(const Countable&) { ++count; }

    virtual ~Countable() { --count; }

    static size_t get_count() { return count; }

    // CRTP method - calls derived class implementation
    void print_info() const {
        std::cout << "Object count: " << count << ", ";
        static_cast<const Derived*>(this)->print_details();
    }
};

// Static member definition
template<typename Derived>
size_t Countable<Derived>::count = 0;

// Derived classes
class Widget : public Countable<Widget> {
private:
    std::string name;

public:
    Widget(const std::string& n) : name(n) {}

    void print_details() const {
        std::cout << "Widget: " << name << std::endl;
    }
};
```

---

## Modern C++ Template Features

### C++11/14/17/20 Template Improvements

Modern C++ has dramatically improved template usability and power:

```cpp
// C++11: Auto and decltype
template<typename Container>
auto get_first_element(Container&& c) -> decltype(c.front()) {
    return c.front();
}

// C++14: Auto return type deduction
template<typename Container>
auto get_last_element(Container&& c) {
    return c.back();  // Return type automatically deduced
}

// C++14: Variable templates
template<typename T>
constexpr bool is_integral_v = std::is_integral<T>::value;

// C++17: Class Template Argument Deduction (CTAD)
template<typename T>
class Wrapper {
private:
    T value;

public:
    Wrapper(T v) : value(v) {}
    T get() const { return value; }
};

// C++17: constexpr if
template<typename T>
auto process_type(T&& value) {
    if constexpr (std::is_integral_v<std::decay_t<T>>) {
        std::cout << "Processing integer: " << value << std::endl;
        return value * 2;
    } else if constexpr (std::is_floating_point_v<std::decay_t<T>>) {
        std::cout << "Processing float: " << value << std::endl;
        return value * 3.14;
    } else {
        std::cout << "Processing other type" << std::endl;
        return value;
    }
}

// C++17: Fold expressions
template<typename... Args>
auto sum_all(Args... args) {
    return (... + args);  // Unary left fold
}

// C++20: Abbreviated function templates
void print_value(auto value) {
    std::cout << "Value: " << value << std::endl;
}
```

---

## Performance and Best Practices

### Template performance considerations

Templates can provide zero-cost abstraction, but understanding performance implications is crucial:

```cpp
// Performance consideration: Template instantiation cost
template<typename T>
class HeavyTemplate {
private:
    T data[1000];  // Large static array

public:
    void process() {
        // Heavy computation for each instantiation
        for (int i = 0; i < 1000; ++i) {
            data[i] = T{};
        }
        std::cout << "Processing " << typeid(T).name() << std::endl;
    }
};

// Better approach: Factor out common functionality
class HeavyTemplateBase {
protected:
    void* data;
    size_t element_size;
    size_t count;

    void process_impl();

public:
    HeavyTemplateBase(size_t elem_size, size_t cnt);
    virtual ~HeavyTemplateBase();
};

template<typename T>
class OptimizedHeavyTemplate : private HeavyTemplateBase {
public:
    OptimizedHeavyTemplate() : HeavyTemplateBase(sizeof(T), 1000) {}

    void process() {
        process_impl();  // Shared implementation
        std::cout << "Processing " << typeid(T).name() << std::endl;
    }
};
```

### Template best practices and guidelines

Essential practices for effective template programming:

```cpp
// Best Practice 1: Use meaningful names and clear interfaces
template<typename ValueType>
class ThreadSafeContainer {
private:
    std::vector<ValueType> data;
    mutable std::mutex mutex_;

public:
    void add_item(const ValueType& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        data.push_back(item);
    }

    ValueType get_item(size_t index) const {
        std::lock_guard<std::mutex> lock(mutex_);
        return data.at(index);
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return data.size();
    }
};

// Best Practice 2: Provide clear error messages
template<typename T>
class Matrix {
    static_assert(std::is_arithmetic_v<T>,
                  "Matrix can only be instantiated with arithmetic types");
    static_assert(!std::is_same_v<T, bool>,
                  "Matrix cannot use bool as element type");

private:
    std::vector<T> data;
    size_t rows, cols;

public:
    Matrix(size_t r, size_t c) : data(r * c), rows(r), cols(c) {}

    T& operator()(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return data[row * cols + col];
    }
};
```

---

## Common Pitfalls and Debugging

### Template compilation errors and how to fix them

Template errors can be cryptic. Here's how to understand and fix common issues:

```cpp
// Common Pitfall 1: Two-phase name lookup
template<typename T>
class Base {
public:
    void base_method() {
        std::cout << "Base method" << std::endl;
    }

protected:
    T base_member;
};

// WRONG: This won't compile
template<typename T>
class Derived_Wrong : public Base<T> {
public:
    void some_method() {
        // Error: base_method not found (dependent name lookup)
        // base_method();  // Compilation error
    }
};

// CORRECT: Proper dependent name lookup
template<typename T>
class Derived_Correct : public Base<T> {
public:
    void some_method() {
        // Solution 1: Use this->
        this->base_method();
        this->base_member = T{};

        // Solution 2: Qualified name
        Base<T>::base_method();
        Base<T>::base_member = T{};
    }

    // Solution 3: Using declaration
    using Base<T>::base_method;
    using Base<T>::base_member;

    void another_method() {
        base_method();  // Now works due to using declaration
    }
};
```

### Debugging techniques and tools

Essential debugging approaches for template code:

```cpp
// Debugging Technique 1: Static assertions for validation
template<typename T>
class DebuggedContainer {
    // Validate template arguments at compile time
    static_assert(std::is_default_constructible_v<T>,
                  "T must be default constructible");
    static_assert(!std::is_same_v<T, void>,
                  "T cannot be void");
    static_assert(sizeof(T) > 0,
                  "T must be a complete type");

private:
    std::vector<T> data;

public:
    void add(const T& item) {
        data.push_back(item);
        debug_print("Added item");
    }

private:
    void debug_print(const char* message) const {
        #ifdef DEBUG_TEMPLATES
        std::cout << "[DEBUG] " << message << " for type "
                  << typeid(T).name() << std::endl;
        #endif
    }
};

// Debugging Technique 2: Type trait debugging
template<typename T>
void debug_type_properties() {
    std::cout << "\n=== Type Properties for " << typeid(T).name() << " ===" << std::endl;
    std::cout << "Size: " << sizeof(T) << " bytes" << std::endl;
    std::cout << "Alignment: " << alignof(T) << " bytes" << std::endl;
    std::cout << "Is fundamental: " << std::is_fundamental_v<T> << std::endl;
    std::cout << "Is arithmetic: " << std::is_arithmetic_v<T> << std::endl;
    std::cout << "Is integral: " << std::is_integral_v<T> << std::endl;
    std::cout << "Is default constructible: " << std::is_default_constructible_v<T> << std::endl;
}
```

---

## Real-World Applications

### Practical template examples for CPP07 exercises

Templates commonly used in 42 school projects and real-world applications:

```cpp
// Real-World Example 1: Generic Iterator Implementation
template<typename T>
class SimpleVector {
private:
    T* data;
    size_t size_;
    size_t capacity_;

public:
    // Iterator implementation
    class iterator {
    private:
        T* ptr;

    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::random_access_iterator_tag;

        iterator(T* p) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++ptr; return tmp; }

        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }

        reference operator[](difference_type n) const { return ptr[n]; }
    };

    // Container interface
    SimpleVector() : data(nullptr), size_(0), capacity_(0) {}

    ~SimpleVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
            T* new_data = new T[capacity_];

            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = std::move(data[i]);
            }

            delete[] data;
            data = new_data;
        }
        data[size_++] = value;
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    // Iterator interface
    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + size_); }
};

// Real-World Example 2: Function Template with Algorithm
template<typename Iterator, typename Predicate>
Iterator find_if_custom(Iterator first, Iterator last, Predicate pred) {
    while (first != last) {
        if (pred(*first)) {
            return first;
        }
        ++first;
    }
    return last;
}

template<typename Iterator, typename Function>
Function for_each_custom(Iterator first, Iterator last, Function func) {
    while (first != last) {
        func(*first);
        ++first;
    }
    return func;
}
```

### Template-based design patterns

Common design patterns implemented with templates:

```cpp
// Pattern 1: Template Method Pattern
template<typename Derived>
class GameTemplate {
public:
    void play() {
        initialize();
        start_play();
        end_play();
    }

private:
    void initialize() {
        std::cout << "Game initialized" << std::endl;
        static_cast<Derived*>(this)->initialize_impl();
    }

    void start_play() {
        std::cout << "Game started" << std::endl;
        static_cast<Derived*>(this)->start_play_impl();
    }

    void end_play() {
        static_cast<Derived*>(this)->end_play_impl();
        std::cout << "Game ended" << std::endl;
    }
};

class Chess : public GameTemplate<Chess> {
public:
    void initialize_impl() {
        std::cout << "Chess: Setting up board" << std::endl;
    }

    void start_play_impl() {
        std::cout << "Chess: Players making moves" << std::endl;
    }

    void end_play_impl() {
        std::cout << "Chess: Checkmate!" << std::endl;
    }
};

// Pattern 2: Template Singleton
template<typename T>
class Singleton {
private:
    static std::unique_ptr<T> instance;
    static std::once_flag once_flag;

public:
    static T& get_instance() {
        std::call_once(once_flag, []() {
            instance = std::unique_ptr<T>(new T());
        });
        return *instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

template<typename T>
std::unique_ptr<T> Singleton<T>::instance = nullptr;

template<typename T>
std::once_flag Singleton<T>::once_flag;
```

---

## Conclusion

This comprehensive guide covers the essential aspects of C++ templates for the CPP07 module. Templates are a powerful feature that enables generic programming while maintaining type safety and performance. Key takeaways include:

**Fundamental Concepts:**
- Templates provide zero-cost abstraction through compile-time code generation
- Understanding the instantiation model is crucial for effective template usage
- Template argument deduction reduces boilerplate but has specific rules

**Modern Features:**
- C++11/14/17/20 have dramatically improved template usability
- Concepts provide cleaner alternatives to SFINAE
- Features like CTAD, constexpr if, and fold expressions simplify template code

**Best Practices:**
- Use clear, descriptive names and constrain templates appropriately
- Prefer composition over inheritance in template design
- Factor out common functionality to reduce instantiation overhead
- Provide clear error messages through static assertions

**Advanced Techniques:**
- CRTP enables static polymorphism and compile-time interfaces
- Variadic templates and perfect forwarding handle variable arguments elegantly
- Template metaprogramming enables powerful compile-time computations

**Practical Applications:**
- Templates form the backbone of the STL and most modern C++ libraries
- Common patterns like iterators, factories, and observers benefit from templates
- Real-world usage spans from containers to algorithms to design patterns

Templates represent one of C++'s most distinctive and powerful features. While they have a learning curve, mastering them opens the door to writing highly reusable, performant, and type-safe code. The evolution from basic function templates to modern concepts shows the language's commitment to making generic programming more accessible and expressive.

For CPP07 exercises, focus on understanding instantiation, implementing proper iterators, and using templates to create flexible, reusable components. The patterns and techniques covered in this guide provide a solid foundation for both academic exercises and professional C++ development.
