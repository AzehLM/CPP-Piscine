# Polymorphism, Abstract Classes

## Table of Contents
1. [Subtype Polymorphism](#subtype-polymorphism)
2. [Abstract Classes](#abstract-classes)
3. [Interfaces in C++](#interfaces-in-c)
4. [Polymorphism vs Subtyping](#polymorphism-vs-subtyping)
5. [Shallow Copy vs Deep Copy](#shallow-copy-vs-deep-copy)
6. [Common Pitfalls](#common-pitfalls)
---

## Subtype Polymorphism

**Subtype polymorphism** allows objects of different types to be treated uniformly through a common interface. The correct function is selected at runtime based on the actual object type, not the pointer type.

### Key Characteristics
- **Runtime Resolution**: Function calls resolved at runtime through vtable lookup
- **Dynamic Dispatch**: Correct function selected based on actual object type
- **Inheritance-Based**: Requires inheritance relationships with virtual functions

### Basic Example: Animal Hierarchy
```cpp
#include <iostream>
#include <memory>
#include <vector>

class Animal {
public:
	virtual void makeSound() = 0;  // Pure virtual function
	virtual ~Animal() = default;
};

class Dog : public Animal {
public:
	void makeSound() override {
		std::cout << "Woof! Woof!" << std::endl;
	}
};

class Cat : public Animal {
public:
	void makeSound() override {
		std::cout << "Meow! Meow!" << std::endl;
	}
};

// Function using polymorphism
void animalSound(Animal* animal) {
	animal->makeSound();  // Calls appropriate derived class method
}

int main() {
	Dog dog;
	Cat cat;

	animalSound(&dog);  // Output: Woof! Woof!
	animalSound(&cat);  // Output: Meow! Meow!

	// Using with containers
	std::vector<std::unique_ptr<Animal>> animals;
	animals.push_back(std::make_unique<Dog>());
	animals.push_back(std::make_unique<Cat>());

	for (const auto& animal : animals) {
		animal->makeSound();
	}

	return 0;
}
```

### Polymorphic Object Behavior
When you call a virtual function on a base class pointer:
1. **Runtime Type Identification**: The vtable pointer determines the actual object type
2. **Dynamic Dispatch**: The correct derived class function is called
3. **Memory Safety**: Virtual destructors ensure proper cleanup

---

## Abstract Classes

**Abstract classes** contain at least one pure virtual function and cannot be instantiated directly. They serve as base classes that define interfaces for derived classes.

### Implementation Pattern
```cpp
class Shape {
protected:
	double width, height;

public:
	Shape(double w, double h) : width(w), height(h) {}

	// Pure virtual functions - must be implemented by derived classes
	virtual double getArea() = 0;
	virtual double getPerimeter() = 0;
	virtual void display() = 0;

	// Regular virtual function with default implementation
	virtual void printInfo() {
		std::cout << "Shape with width: " << width
				  << " and height: " << height << std::endl;
	}

	// Non-virtual function
	void setDimensions(double w, double h) {
		width = w;
		height = h;
	}

	virtual ~Shape() = default;
};

class Rectangle : public Shape {
public:
	Rectangle(double w, double h) : Shape(w, h) {}

	double getArea() override {
		return width * height;
	}

	double getPerimeter() override {
		return 2 * (width + height);
	}

	void display() override {
		std::cout << "Rectangle: " << width << " x " << height << std::endl;
	}
};
```

### Abstract Class Characteristics
- **Cannot be instantiated**: `Shape shape;` causes compilation error
- **Can have constructors**: Used by derived classes
- **Can have data members**: Both public and protected
- **Can mix pure virtual and regular functions**: Provides flexibility
- **Derived classes must implement all pure virtual functions**: Or they become abstract too

### Best Practices
1. **Always include virtual destructor** for proper cleanup
2. **Use pure virtual functions** to enforce interface contracts
3. **Provide meaningful default implementations** for non-pure virtual functions
4. **Keep interfaces minimal** - follow single responsibility principle

---

## Interfaces in C++

C++ doesn't have a dedicated `interface` keyword, but interfaces are implemented using **pure abstract classes** containing only pure virtual functions.

### Interface vs Abstract Class

| **Interface (Pure Abstract Class)** | **Abstract Class** |
|-------------------------------------|-------------------|
| All methods are pure virtual | Mix of pure virtual and regular methods |
| No data members (by convention) | Can have data members |
| No implementation | Can have some implementation |
| Multiple inheritance friendly | More complex with multiple inheritance |

### Interface Implementation Example
```cpp
// Interface definitions
class IDrawable {
public:
	virtual void draw() = 0;
	virtual void resize(double factor) = 0;
	virtual ~IDrawable() = default;
};

class IMovable {
public:
	virtual void move(double x, double y) = 0;
	virtual void rotate(double angle) = 0;
	virtual ~IMovable() = default;
};

// Class implementing multiple interfaces
class GraphicObject : public IDrawable, public IMovable {
private:
	double x, y, width, height, rotation;

public:
	GraphicObject(double x, double y, double w, double h)
		: x(x), y(y), width(w), height(h), rotation(0) {}

	// Implement IDrawable interface
	void draw() override {
		std::cout << "Drawing object at (" << x << ", " << y
				  << ") with size " << width << "x" << height << std::endl;
	}

	void resize(double factor) override {
		width *= factor;
		height *= factor;
	}

	// Implement IMovable interface
	void move(double dx, double dy) override {
		x += dx;
		y += dy;
	}

	void rotate(double angle) override {
		rotation += angle;
	}
};
```

### When to Use Interfaces
- **Unrelated classes need common behavior**
- **Multiple inheritance scenarios** (safer than abstract classes)
- **Dependency injection** for loose coupling
- **Plugin architectures** for extensibility

---

## Polymorphism vs Subtyping

**Polymorphism** is broader and includes multiple forms, while **subtyping** specifically concerns type relationships and substitutability.

### Two of The Four Types of Polymorphism

#### 1. Subtype Polymorphism (Runtime)
```cpp
class Base {
public:
	virtual void func() = 0;
};

class Derived : public Base {
public:
	void func() override {
		std::cout << "Derived implementation" << std::endl;
	}
};

void useBase(Base* b) {
	b->func();  // Runtime dispatch
}
```

#### 2. Parametric Polymorphism (Templates)
```cpp
template<typename T>
T maximum(T a, T b) {
	return a > b ? a : b;
}

int main() {
	std::cout << maximum(10, 20) << std::endl;        // int version
	std::cout << maximum(3.14, 2.71) << std::endl;    // double version
}
```

### When to Use Each Approach

**Use Subtype Polymorphism when:**
- You need runtime flexibility
- Objects have an "is-a" relationship
- You want to store different types in the same container

**Use Parametric Polymorphism when:**
- You need compile-time performance
- Type safety is crucial
- You're working with generic algorithms

---

## Shallow Copy vs Deep Copy

Understanding copy semantics is crucial for memory management in polymorphic hierarchies.

### Shallow Copy
**Definition**: Copies only the addresses of dynamically allocated memory, not the actual data.

**Problems:**
- Both objects share the same memory location
- Changes to one object affect the other
- **Double deletion** when both objects try to free the same memory
- **Dangling pointers** when one object is destroyed

### Deep Copy
**Definition**: Creates separate memory for all dynamically allocated data, copying actual values.

**Benefits:**
- Each object has independent memory
- Changes to one object don't affect the other
- Safe destruction - each object manages its own memory

### Implementation Example
```cpp
class MyString {
private:
	char* m_data;
	int m_length;

public:
	// Constructor
	MyString(const char* source = "") {
		m_length = std::strlen(source) + 1;
		m_data = new char[m_length];
		std::strcpy(m_data, source);
	}

	// Deep copy constructor
	MyString(const MyString& other) {
		m_length = other.m_length;
		if (other.m_data) {
			m_data = new char[m_length];
			std::strcpy(m_data, other.m_data);
		} else {
			m_data = nullptr;
		}
	}

	// Deep copy assignment operator
	MyString& operator=(const MyString& other) {
		if (this != &other) {  // Self-assignment check
			delete[] m_data;    // Free existing memory

			m_length = other.m_length;
			if (other.m_data) {
				m_data = new char[m_length];
				std::strcpy(m_data, other.m_data);
			} else {
				m_data = nullptr;
			}
		}
		return *this;
	}

	~MyString() {
		delete[] m_data;
	}
};
```

### Rule of Three/Five/Zero

**Rule of Three**: If you need custom destructor, copy constructor, or copy assignment, you need all three.

**Rule of Five**: With C++11 move semantics, also implement move constructor and move assignment.

**Rule of Zero**: Prefer using RAII types (smart pointers, STL containers) to avoid manual memory management.

---

### Shallow vs Deep Copy Memory
```
Shallow Copy:
Original:  [obj1] → [data pointer] → [actual data]
									    ↑
Shallow:   [obj2] → [data pointer] ─────┘
					  (same address)

Deep Copy:
Original:  [obj1] → [data pointer] → [actual data]

Deep Copy: [obj2] → [data pointer] → [copied data]
				  (different addr)   (separate memory)
```

---


### Common CPP04 Exercises

#### Exercise 00: Basic Polymorphism
- Create `Animal` base class with virtual `makeSound()`
- Implement `Cat` and `Dog` derived classes
- Test polymorphic behavior

#### Exercise 01: Brain Class and Deep Copy
- Introduce `Brain` class with dynamic memory
- `Cat` and `Dog` classes contain `Brain` objects
- **Critical**: Implement proper deep copy semantics

#### Exercise 02: Abstract Classes
- Make `Animal` class abstract using pure virtual functions
- Prevent direct instantiation
- Ensure virtual destructor implementation

#### Exercise 03: Interfaces (AMateria)
- Implement `AMateria` abstract base class
- Create `ICharacter` and `IMateriaSource` interfaces
- Develop concrete classes with complex inheritance

---

## Common Pitfalls

### Memory Management Issues
1. **Forgetting virtual destructors** in base classes
2. **Shallow copy problems** with dynamic memory
3. **Double deletion** from improper copy semantics
4. **Self-assignment** not checked in assignment operators

### Polymorphism Mistakes
1. **Object slicing** when copying derived objects to base
2. **Missing virtual keyword** for functions meant to be overridden
3. **Calling virtual functions in constructors/destructors**
4. **Pure virtual function calls** in abstract classes

### Design Problems
1. **Overly complex inheritance hierarchies**
2. **Mixing interfaces and implementation in abstract classes**
3. **Improper use of multiple inheritance**
4. **Violating Liskov Substitution Principle**

### Prevention Strategies
- Always use virtual destructors in polymorphic hierarchies
- Implement proper deep copy for classes with dynamic memory
- Follow Rule of Three/Five/Zero consistently
- Test polymorphic behavior thoroughly
- Use smart pointers when possible for automatic memory management
