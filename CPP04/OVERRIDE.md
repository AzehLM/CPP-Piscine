[Why do we need virtual functions in C++](https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c)

# Override keyword

## Why is it

The `override` keyword had been introduced in C++11 to resolve a known problem : silent errors of virtual functions redefinition. Before C++11, if you made a signature error in a virtual function, the compiler wouldn't warn you - it only implemented a new member function.

> *Unfortunatly won't be usable in 42 projets because of the C++ version, but good to know it exists overall. Until then, leaving comments to functions in needs of a redefinition will be our "solution".*
> *The comment  ``/* override */`` vas a convention adopted by some dev teams to show an intention before a solution was introduced years later.*
> C++11 introduced `override` as a keyword specificly because of the **need** of a verification in the deep integration of types by the compiler.

## Problem without override

Consider this problematic situation :


```cpp
class Base {
public:
    virtual void process(int value) {
        std::cout << "Base processing: " << value << std::endl;
    }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    // ERROR: different signature (long instead of int)
    // The compiler does't say anything !
    virtual void process(long value) {
        std::cout << "Derived processing: " << value << std::endl;
    }
};
```

In this example, we thought redefining the `process` function, but the signatures differs and create a new member function. The polymorphism doesn't function as expected.

## Solution without override

`override` explicitly tells the compiler that this function has to redefine a virtual function in the base class :

```cpp
class Base {
public:
    virtual void process(int value) {
        std::cout << "Base processing: " << value << std::endl;
    }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    // COMPILATION ERROR : the signature doesn't match
    void process(long value) override {  // ← Error detected !
        std::cout << "Derived processing: " << value << std::endl;
    }
};
```

## How to use override properly

```cpp
class Shape {
public:
    virtual double getArea() const = 0;
    virtual void draw() const = 0;
    virtual void move(double x, double y) = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape {
private:
    double width, height;
    double posX, posY;

public:
    Rectangle(double w, double h) : width(w), height(h), posX(0), posY(0) {}

    // Correct redefinition with override
    double getArea() const override {
        return width * height;
    }

    void draw() const override {
        std::cout << "Drawing rectangle at (" << posX << "," << posY
                  << ") with size " << width << "x" << height << std::endl;
    }

    void move(double x, double y) override {
        posX = x;
        posY = y;
    }
};
```

## Advantages of override keyword

The keywork `override` provides several important benefits for code quality. Firstly, it offers a **security at compile time** by identifying the signatures errors. Secondly, it enhance the **code visibility** by explicitly showing the intention to redefine a virtual function. Lastly, it is easier to **maintain** because the modifications of the base class are automaticaly verified un the derived class.
