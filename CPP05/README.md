# C++ Exceptions

A comprehensive educational guide to C++ exception handling covering theory, syntax, mechanisms, and best practices.

## Table of Contents

1. [Introduction and Theory](#introduction-and-theory)
2. [Basic Syntax and Usage](#basic-syntax-and-usage)
3. [Exception Handling Mechanisms](#exception-handling-mechanisms)
4. [Standard Exceptions](#standard-exceptions)
5. [Custom Exceptions](#custom-exceptions)
6. [Exception Specifications](#exception-specifications)
7. [Stack Unwinding](#stack-unwinding)
8. [RAII and Exception Safety](#raii-and-exception-safety)
9. [Best Practices](#best-practices)
10. [Common Pitfalls](#common-pitfalls)
11. [Advanced Concepts](#advanced-concepts)

---

## Introduction and Theory

### What Are Exceptions?

Exceptions in C++ are objects that represent exceptional circumstances—error conditions that prevent a program from continuing its normal execution flow. They provide a structured way to handle errors that is superior to traditional approaches like return codes or global error variables.

### Why Exceptions Exist

**Problems with traditional error handling:**

```cpp
// Traditional C-style error handling
int divide(int a, int b, int* result) {
    if (b == 0) return ERROR_DIVIDE_BY_ZERO;
    *result = a / b;
    return SUCCESS;
}

// Usage requires constant checking - error-prone and cluttered
int result;
int status = divide(10, 2, &result);
if (status != SUCCESS) {
    handle_error(status);
    return status;
}
```

**Advantages of exceptions:**

1. **Separation of concerns** - Normal logic is separate from error handling
2. **Automatic propagation** - Errors automatically bubble up the call stack
3. **Rich information** - Exception objects can carry detailed error context
4. **Cannot be ignored** - Unlike return codes, exceptions must be handled

```cpp
// Exception-based approach - cleaner and safer
try {
    auto data = readFile(filename);
    auto processed = processData(data);
    return computeResult(processed);
} 
catch (const FileError& e) {
    log("File error: " + e.what());
    return defaultValue;
}
```

### Exception Philosophy

**Use exceptions for:**
- Constructor failures (no way to return error codes)
- Resource acquisition failures  
- Postcondition violations (function can't deliver promised result)
- Invariant violations

**Don't use exceptions for:**
- Regular control flow
- Expected conditions that occur frequently (>1% of cases)
- Performance-critical loops where exceptions might be thrown regularly

---

## Basic Syntax and Usage

### Core Exception Handling Structure

```cpp
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // Code that might throw an exception
        throw std::runtime_error("Something went wrong!");
    }
    catch (const std::runtime_error& e) {
        // Handle specific exception type
        std::cout << "Caught runtime_error: " << e.what() << std::endl;
    }
    catch (...) {
        // Catch-all handler for any other exception type
        std::cout << "Caught unknown exception" << std::endl;
    }
    
    return 0;
}
```

### Throwing Different Types

```cpp
try {
    throw 42;               // Throw integer
    throw "Error message";  // Throw C-string
    throw 3.14;            // Throw double
}
catch (int error_code) {
    std::cout << "Integer exception: " << error_code << std::endl;
}
catch (const char* msg) {
    std::cout << "String exception: " << msg << std::endl;
}
catch (double d) {
    std::cout << "Double exception: " << d << std::endl;
}
```

### Multiple Catch Blocks

```cpp
void processValue(int value) {
    try {
        if (value < 0) {
            throw std::invalid_argument("Negative value");
        }
        if (value == 0) {
            throw std::domain_error("Zero value");
        }
        if (value > 1000) {
            throw std::overflow_error("Value too large");
        }
        
        std::cout << "Processing value: " << value << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::domain_error& e) {
        std::cout << "Domain error: " << e.what() << std::endl;
    }
    catch (const std::overflow_error& e) {
        std::cout << "Overflow error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Other standard exception: " << e.what() << std::endl;
    }
}
```

---

## Exception Handling Mechanisms

### Exception Propagation

When an exception is thrown, the C++ runtime system:

1. **Creates exception object** - Exception is copied/moved to exception handling mechanism
2. **Begins stack unwinding** - Normal execution stops immediately
3. **Searches for handlers** - Examines catch blocks in reverse order of call stack
4. **Calls destructors** - Automatic objects are destroyed during unwinding
5. **Transfers control** - First matching catch block handles the exception

```cpp
void function_c() {
    std::cout << "In function_c, about to throw" << std::endl;
    throw std::runtime_error("Error from function_c");
}

void function_b() {
    std::cout << "In function_b, calling function_c" << std::endl;
    function_c();  // Exception will propagate through this function
    std::cout << "This line won't execute" << std::endl;
}

void function_a() {
    try {
        std::cout << "In function_a, calling function_b" << std::endl;
        function_b();
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught in function_a: " << e.what() << std::endl;
    }
}
```

### Exception Matching Rules

Exception handlers match based on:

1. **Exact type match**
2. **Derived-to-base conversion**
3. **Pointer/reference conversions** (adding const/volatile)
4. **No other implicit conversions**

```cpp
class Base {};
class Derived : public Base {};

try {
    throw Derived{};
}
catch (Base& e) {        // Matches: derived-to-base conversion
    // Handles Derived as Base
}
catch (Derived& e) {     // Would never be reached - dead code
    // Base handler above catches first
}
```

### Rethrowing Exceptions

```cpp
void partialHandler() {
    try {
        riskyOperation();
    }
    catch (const std::runtime_error& e) {
        std::cout << "Partial handling: " << e.what() << std::endl;
        
        // Log error, cleanup resources, etc.
        logError(e.what());
        
        // Rethrow the same exception object
        throw;  // Don't use 'throw e;' - that creates a new object!
    }
}

void fullHandler() {
    try {
        partialHandler();
    }
    catch (const std::runtime_error& e) {
        std::cout << "Final handling: " << e.what() << std::endl;
    }
}
```

---

## Standard Exceptions

### Exception Hierarchy

```
std::exception
├── std::logic_error
│   ├── std::domain_error
│   ├── std::invalid_argument
│   ├── std::length_error
│   └── std::out_of_range
├── std::runtime_error
│   ├── std::range_error
│   ├── std::overflow_error
│   └── std::underflow_error
├── std::bad_alloc
├── std::bad_cast
├── std::bad_typeid
└── std::bad_exception
```

### Common Standard Exceptions

```cpp
#include <iostream>
#include <stdexcept>
#include <vector>

void demonstrateStandardExceptions() {
    try {
        // std::out_of_range example
        std::vector<int> vec = {1, 2, 3};
        std::cout << vec.at(10); // Throws std::out_of_range
    }
    catch (const std::out_of_range& e) {
        std::cout << "Out of range: " << e.what() << std::endl;
    }
    
    try {
        // std::invalid_argument example
        int value = std::stoi("not_a_number");
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    }
    
    try {
        // std::runtime_error example
        throw std::runtime_error("Runtime error occurred");
    }
    catch (const std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
}
```

### Key Standard Exception Categories

**Logic Errors (Programming Mistakes):**
- `std::logic_error` - Base for logic errors
- `std::domain_error` - Mathematical domain errors
- `std::invalid_argument` - Invalid function arguments
- `std::length_error` - Length exceeds maximum size
- `std::out_of_range` - Index/key out of valid range

**Runtime Errors (External Conditions):**
- `std::runtime_error` - Base for runtime errors
- `std::range_error` - Internal computation range error
- `std::overflow_error` - Arithmetic overflow
- `std::underflow_error` - Arithmetic underflow

**System Errors:**
- `std::bad_alloc` - Memory allocation failure
- `std::bad_cast` - Invalid dynamic_cast
- `std::bad_typeid` - Invalid typeid usage

---

## Custom Exceptions

### Basic Custom Exception

```cpp
#include <iostream>
#include <exception>
#include <string>

class CustomException : public std::exception {
private:
    std::string message;
    
public:
    explicit CustomException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Usage
void riskyFunction(int value) {
    if (value < 0) {
        throw CustomException("Negative values not allowed!");
    }
    if (value > 100) {
        throw CustomException("Value too large!");
    }
}
```

### Advanced Custom Exception with Context

```cpp
class MathError : public std::runtime_error {
private:
    int error_code;
    std::string operation;
    
public:
    MathError(const std::string& message, int code, const std::string& op)
        : std::runtime_error(message), error_code(code), operation(op) {}
    
    int getErrorCode() const noexcept { return error_code; }
    const std::string& getOperation() const noexcept { return operation; }
    
    // Override what() to include additional context
    const char* what() const noexcept override {
        static std::string full_message = 
            std::runtime_error::what() + 
            " (Code: " + std::to_string(error_code) + 
            ", Operation: " + operation + ")";
        return full_message.c_str();
    }
};

class DivisionByZero : public MathError {
public:
    DivisionByZero() : MathError("Division by zero", 1001, "divide") {}
};
```

### Inheriting from Standard Exceptions

```cpp
// Simple approach using constructor inheritance (C++11+)
struct FileNotFoundException : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct NetworkError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

// Usage
void connectToNetwork() {
    throw NetworkError("Connection timeout");
}

void openFile(const std::string& filename) {
    throw FileNotFoundException("File not found: " + filename);
}
```

### Exception Hierarchy Best Practices

```cpp
// Design logical hierarchies based on error categories
class ApplicationError : public std::runtime_error {
public:
    ApplicationError(const std::string& msg) : std::runtime_error(msg) {}
};

class ConfigurationError : public ApplicationError {
public:
    ConfigurationError(const std::string& msg) 
        : ApplicationError("Configuration error: " + msg) {}
};

class ResourceError : public ApplicationError {
public:
    ResourceError(const std::string& msg) 
        : ApplicationError("Resource error: " + msg) {}
};

class FileError : public ResourceError {
public:
    FileError(const std::string& msg) 
        : ResourceError("File error: " + msg) {}
};
```

---

## Exception Specifications

### noexcept Specifier (C++11+)

The `noexcept` specifier indicates that a function will not throw exceptions that escape to the caller.

```cpp
// Function promises not to throw exceptions
void safeFunction() noexcept {
    // This function will never throw
    std::cout << "Safe operation" << std::endl;
}

// Conditional noexcept
template<typename T>
void conditionalFunction() noexcept(std::is_nothrow_move_constructible_v<T>) {
    T obj{};
    // noexcept depends on T's move constructor
}

// Explicit boolean parameter
void explicitNoexcept() noexcept(true) {  // Same as noexcept
    // Won't throw
}

void mightThrow() noexcept(false) {       // Same as no specification
    // Might throw
}
```

### noexcept Operator

```cpp
#include <iostream>
#include <type_traits>

void throwingFunction() {
    throw std::runtime_error("Error");
}

void nonThrowingFunction() noexcept {
    std::cout << "Safe" << std::endl;
}

int main() {
    // noexcept operator - compile-time check
    std::cout << "throwingFunction is noexcept: " 
              << noexcept(throwingFunction()) << std::endl;  // false
    
    std::cout << "nonThrowingFunction is noexcept: " 
              << noexcept(nonThrowingFunction()) << std::endl; // true
    
    // Using in template conditions
    std::cout << "int move constructor is noexcept: "
              << std::is_nothrow_move_constructible_v<int> << std::endl;
    
    return 0;
}
```

### What Happens When noexcept is Violated

```cpp
void violateNoexcept() noexcept {
    // If an exception tries to escape a noexcept function,
    // std::terminate is called immediately
    throw std::runtime_error("This will call std::terminate!");
}

// This program will terminate
int main() {
    try {
        violateNoexcept();
    }
    catch (...) {
        // This catch block will never be reached
        std::cout << "Never printed" << std::endl;
    }
    return 0;
}
```

### Historical Context: Dynamic Exception Specifications

```cpp
// OLD WAY (deprecated in C++11, removed in C++17)
void oldStyleSpec() throw(std::runtime_error, std::logic_error) {
    // Could only throw these specific types
}

void oldNoThrow() throw() {
    // Equivalent to noexcept
}

// MODERN WAY (C++11+)
void modernSpec() noexcept {
    // Won't throw any exceptions
}

void modernMightThrow() {
    // Might throw (default behavior)
}
```

---

## Stack Unwinding

### What is Stack Unwinding?

Stack unwinding is the process that occurs when an exception is thrown and propagates up the call stack. The C++ runtime systematically destroys all automatic objects that were constructed between the throw point and the catch point.

### Stack Unwinding Process

1. **Exception is thrown** - Exception object is created
2. **Search for handler** - Runtime examines each function in call stack
3. **Stack frame removal** - Each function's stack frame is removed
4. **Destructor invocation** - All fully-constructed automatic objects have destructors called in reverse order
5. **Handler execution** - Control transfers to matching catch block

```cpp
class Resource {
    std::string name;
public:
    Resource(const std::string& n) : name(n) {
        std::cout << "Constructing " << name << std::endl;
    }
    
    ~Resource() {
        std::cout << "Destroying " << name << std::endl;
    }
};

void function_c() {
    Resource res3("Resource C");
    throw std::runtime_error("Error in function C");
}

void function_b() {
    Resource res2("Resource B");
    function_c();
}

void function_a() {
    Resource res1("Resource A");
    function_b();
}

int main() {
    try {
        function_a();
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
    return 0;
}

/* Output:
Constructing Resource A
Constructing Resource B
Constructing Resource C
Destroying Resource C
Destroying Resource B
Destroying Resource A
Caught: Error in function C
*/
```

### Critical Stack Unwinding Rules

1. **Only fully-constructed objects are destroyed**
2. **Objects are destroyed in reverse order of construction**
3. **Destructors must not throw during unwinding** (causes `std::terminate`)
4. **Only automatic storage objects are cleaned up**
5. **Dynamic memory must be managed explicitly (use RAII)**

---

## RAII and Exception Safety

### RAII Fundamentals

**Resource Acquisition Is Initialization (RAII)** is a programming technique that binds resource management to object lifetime:

1. **Encapsulate resources in classes**
2. **Acquire resources in constructor**
3. **Release resources in destructor**
4. **Use via automatic storage**

### RAII and Exception Safety

```cpp
// Poor approach - not exception safe
void badExample() {
    FILE* file = fopen("data.txt", "r");
    processFile(file);  // If this throws, file is never closed
    fclose(file);       // May never be reached
}

// RAII approach - exception safe
class FileHandle {
    FILE* file;
public:
    FileHandle(const char* filename, const char* mode) 
        : file(fopen(filename, mode)) {
        if (!file) throw std::runtime_error("Failed to open file");
    }
    
    ~FileHandle() {
        if (file) fclose(file);
    }
    
    FILE* get() const { return file; }
    
    // Prevent copying for simplicity
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
};

void goodExample() {
    FileHandle file("data.txt", "r");
    processFile(file.get());  // Even if this throws, 
                             // FileHandle destructor closes file
}
```

### Modern RAII with Smart Pointers

```cpp
#include <memory>
#include <mutex>

void modernRAII() {
    // Automatic memory management
    auto ptr = std::make_unique<MyClass>(args);
    
    // Automatic mutex management
    std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    
    // Even if exceptions are thrown, resources are cleaned up
    riskyOperation();
} // All resources automatically released here
```

### Exception Safety Levels

**1. No-throw (No-fail) Guarantee:**
- Function will never throw exceptions
- Required for destructors and cleanup operations

```cpp
class SafeContainer {
public:
    // No-throw guarantee
    void swap(SafeContainer& other) noexcept {
        data_.swap(other.data_);
    }
    
    ~SafeContainer() noexcept = default;  // Required for destructors
private:
    std::vector<int> data_;
};
```

**2. Strong Exception Guarantee:**
- Either succeeds completely or has no effect (commit-or-rollback)

```cpp
class StrongGuaranteeExample {
    std::string data_;
    
public:
    // Strong guarantee using copy-and-swap idiom
    StrongGuaranteeExample& operator=(const StrongGuaranteeExample& other) {
        StrongGuaranteeExample temp(other); // May throw
        swap(temp);                        // No-throw
        return *this;
    } // If construction throws, *this is unchanged
    
    void swap(StrongGuaranteeExample& other) noexcept {
        data_.swap(other.data_);
    }
};
```

**3. Basic Exception Guarantee:**
- Program remains in valid state, no resource leaks, but data may be modified

```cpp
class BasicGuaranteeExample {
    std::vector<std::string> data_;
    
public:
    void addItems(const std::vector<std::string>& items) {
        // Basic guarantee: if insertion fails partway through,
        // some items may be added, but no resources leak
        for (const auto& item : items) {
            data_.push_back(item); // May throw
        }
    }
};
```

---

## Best Practices

### Exception Design Principles

**1. Use exceptions for exceptional conditions only**

```cpp
// Good - exceptional condition
if (file_size > MAX_ALLOWED_SIZE) {
    throw std::runtime_error("File size exceeds limit");
}

// Bad - using exceptions for control flow
try {
    return container.at(index);
} catch (std::out_of_range&) {
    return default_value; // Don't use exceptions for expected cases
}
```

**2. Throw by value, catch by const reference**

```cpp
// Correct approach
void function() {
    throw MyException("Error occurred"); // Throw by value
}

void caller() {
    try {
        function();
    } catch (const MyException& e) { // Catch by const reference
        handle_error(e);
    }
}
```

**3. Order catch blocks from specific to general**

```cpp
try {
    riskyOperation();
}
catch (const DerivedError& e) {    // Most specific first
    handle_derived_error(e);
}
catch (const BaseError& e) {       // More general
    handle_base_error(e);
}
catch (const std::exception& e) {  // Very general
    handle_standard_error(e);
}
catch (...) {                      // Catch-all must be last
    handle_unknown_error();
}
```

**4. Provide meaningful error information**

```cpp
class DetailedException : public std::runtime_error {
    std::string operation_;
    std::string context_;
    int error_code_;
    
public:
    DetailedException(const std::string& operation, 
                     const std::string& context,
                     int error_code)
        : std::runtime_error(format_message(operation, context, error_code))
        , operation_(operation)
        , context_(context) 
        , error_code_(error_code) {}
    
    const std::string& operation() const { return operation_; }
    const std::string& context() const { return context_; }
    int error_code() const { return error_code_; }
};
```

**5. Use RAII consistently**

```cpp
void goodResourceManagement() {
    std::unique_ptr<Resource> res1(new Resource());
    std::shared_ptr<Resource> res2 = std::make_shared<Resource>();
    std::lock_guard<std::mutex> lock(mutex_);
    
    // All resources automatically cleaned up on exception
    riskyOperation();
}
```

**6. Write exception-safe constructors**

```cpp
class SafeConstructor {
    std::unique_ptr<Resource1> res1_;
    std::unique_ptr<Resource2> res2_;
    std::string name_;
    
public:
    SafeConstructor(const std::string& name) : name_(name) {
        if (name.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        
        // Use RAII for all resource acquisition
        res1_ = std::make_unique<Resource1>();
        
        // If this throws, res1_ is automatically cleaned up
        res2_ = std::make_unique<Resource2>();
    }
    
    // Destructor only called if constructor succeeds
    ~SafeConstructor() = default;
};
```

---

## Common Pitfalls

### Major Exception Antipatterns

**1. Exception Swallowing**

```cpp
// Antipattern - swallowing exceptions
bool badFunction() {
    try {
        riskyOperation();
        return true;
    } catch (...) {
        return false; // Information lost!
    }
}

// Better approach
bool betterFunction() {
    try {
        riskyOperation();
        return true;
    } catch (const std::exception& e) {
        log_error("Operation failed: " + std::string(e.what()));
        return false;
    }
}
```

**2. Raw Pointer Management**

```cpp
// Dangerous - not exception safe
void dangerousPattern() {
    Widget* widget = new Widget();
    riskyOperation(); // If this throws, widget leaks
    delete widget;
}

// Safe approach using RAII
void safePattern() {
    auto widget = std::make_unique<Widget>();
    riskyOperation(); // widget automatically cleaned up on exception
}
```

**3. Throwing from Destructors**

```cpp
// Antipattern - throwing from destructor
class BadClass {
public:
    ~BadClass() {
        if (cleanup_failed()) {
            throw std::runtime_error("Cleanup failed"); // DON'T DO THIS
        }
    }
};

// Correct approach
class GoodClass {
public:
    ~GoodClass() noexcept {
        try {
            if (cleanup_failed()) {
                log_error("Cleanup failed");
                // Handle error without throwing
            }
        } catch (...) {
            // Absorb any unexpected exceptions
            log_error("Unexpected error in destructor");
        }
    }
};
```

**4. Overly Broad Exception Catching**

```cpp
// Antipattern - catching everything blindly
void badCatchAll() {
    try {
        complexOperation();
    } catch (...) {
        // What error occurred? How should we handle it?
        std::cout << "Something went wrong\n";
    }
}

// Better approach - specific catching
void goodExceptionHandling() {
    try {
        complexOperation();
    } catch (const NetworkException& e) {
        handleNetworkError(e);
    } catch (const DatabaseException& e) {
        handleDatabaseError(e);
    } catch (const std::bad_alloc& e) {
        handleMemoryError(e);
    } catch (const std::exception& e) {
        handleUnexpectedError(e);
        throw; // Re-throw if we can't handle it
    }
}
```

**5. Using Exceptions for Control Flow**

```cpp
// Antipattern - exceptions for control flow
int findElementBad(const std::vector<int>& vec, int target) {
    try {
        for (size_t i = 0; i < vec.size(); ++i) {
            if (vec.at(i) == target) {
                throw static_cast<int>(i); // DON'T DO THIS
            }
        }
        return -1;
    } catch (int index) {
        return index;
    }
}

// Correct approach
int findElementGood(const std::vector<int>& vec, int target) {
    auto it = std::find(vec.begin(), vec.end(), target);
    return (it != vec.end()) ? std::distance(vec.begin(), it) : -1;
}
```

---

## Advanced Concepts

### Exception Handling in Constructors and Destructors

**Constructor Exception Handling:**

```cpp
class SafeClass {
    std::unique_ptr<Resource1> res1_;
    std::unique_ptr<Resource2> res2_;
    std::string name_;
    
public:
    SafeClass(const std::string& name) : name_(name) {
        if (name.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        
        // Use RAII for all resource acquisition
        res1_ = std::make_unique<Resource1>();
        
        // If this throws, res1_ is automatically cleaned up
        res2_ = std::make_unique<Resource2>();
        
        // If we reach here, object is fully constructed
    }
    
    // Destructor only called if constructor completes successfully
    ~SafeClass() = default;
};
```

**Function Try Blocks for Constructors:**

```cpp
class DerivedClass : public BaseClass {
    std::unique_ptr<Resource> resource_;
    
public:
    DerivedClass(int value) 
    try : BaseClass(value), resource_(std::make_unique<Resource>()) {
        // Constructor body
        if (value < 0) {
            throw std::invalid_argument("Negative value");
        }
    } catch (const BaseException& e) {
        // Can catch base class constructor exceptions
        throw DerivedConstructorException("Failed to construct derived", e);
    }
};
```

**Destructor Best Practices:**

```cpp
class ProperDestructor {
    std::vector<std::unique_ptr<Resource>> resources_;
    
public:
    // Destructors should be noexcept (implicit in C++11+)
    ~ProperDestructor() noexcept {
        // Handle cleanup errors without throwing
        for (auto& resource : resources_) {
            try {
                if (resource) {
                    resource->cleanup();
                }
            } catch (const std::exception& e) {
                // Log error but don't throw
                log_error("Resource cleanup failed: " + std::string(e.what()));
            } catch (...) {
                log_error("Unknown error during resource cleanup");
            }
        }
    }
};
```

### Performance Considerations

**Zero-Cost Exception Model:**
- No runtime overhead when exceptions are NOT thrown
- All costs are paid when exceptions ARE thrown
- Exceptions can be 50-250x slower than normal returns when thrown
- Try blocks add virtually no overhead (0-3%)

**When to Consider Alternatives:**
- Tight loops where exceptions might be thrown frequently
- Performance-critical code where even small overhead matters
- Expected error conditions (>1% occurrence rate)

### Modern C++ Exception Features

**noexcept in Templates:**

```cpp
template<typename T>
void conditionalNoexcept(T&& t) noexcept(noexcept(std::forward<T>(t).operation())) {
    std::forward<T>(t).operation();
}

// Move operations should be noexcept when possible
class ModernClass {
public:
    ModernClass(ModernClass&& other) noexcept 
        : data_(std::move(other.data_)) {}
    
    ModernClass& operator=(ModernClass&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }
    
private:
    std::string data_;
};
```

**Exception-Safe Factory Patterns:**

```cpp
template<typename T, typename... Args>
std::unique_ptr<T> makeSafe(Args&&... args) {
    try {
        return std::make_unique<T>(std::forward<Args>(args)...);
    } catch (...) {
        log_error("Failed to construct object");
        throw; // Re-throw for caller to handle
    }
}
```

**RAII Guards for Complex Operations:**

```cpp
class TransactionGuard {
    bool committed_ = false;
    std::function<void()> rollback_;
    
public:
    template<typename F>
    TransactionGuard(F&& rollback) : rollback_(std::forward<F>(rollback)) {}
    
    void commit() noexcept { committed_ = true; }
    
    ~TransactionGuard() noexcept {
        if (!committed_ && rollback_) {
            try {
                rollback_();
            } catch (...) {
                log_error("Rollback failed");
            }
        }
    }
};

void complexOperation() {
    TransactionGuard guard([&] { cleanupPartialState(); });
    
    step1();
    step2();
    step3();
    
    guard.commit(); // Success - no rollback needed
}
```

---

## Summary

C++ exceptions provide a powerful, structured approach to error handling that:

- **Separates normal logic from error handling**
- **Automatically propagates errors up the call stack**
- **Integrates seamlessly with RAII for resource safety**
- **Provides rich contextual information about errors**
- **Enables clean, maintainable code when used properly**

### Key Takeaways

1. **Use exceptions for exceptional conditions** - not regular control flow
2. **Embrace RAII** - automatic resource management prevents leaks
3. **Understand exception safety guarantees** - basic, strong, and no-throw
4. **Design exception hierarchies logically** - based on error categories
5. **Follow modern practices** - use `noexcept`, smart pointers, and proper catching
6. **Avoid common pitfalls** - don't swallow exceptions or throw from destructors
7. **Test exception paths** - ensure your error handling actually works

Exception handling is a fundamental skill for writing robust C++ applications. When combined with RAII and modern language features, it enables developers to write code that is both safe and maintainable, handling error conditions gracefully while preserving program correctness.
