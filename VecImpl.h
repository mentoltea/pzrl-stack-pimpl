#pragma once

#include "Vector.h"
#include "StackImplementation.h"

class VecStackImplementation: public IStackImplementation {
public:
    VecStackImplementation();
    VecStackImplementation(IStackImplementation& copy);
    VecStackImplementation(IStackImplementation&& move);
    VecStackImplementation(const VecStackImplementation& copy);
    VecStackImplementation& operator=(const VecStackImplementation& copy);
    VecStackImplementation(VecStackImplementation&& move);
    VecStackImplementation& operator=(VecStackImplementation&& move);
    ~VecStackImplementation() override; 

    bool operator==(const VecStackImplementation& other) const;
    bool operator!=(const VecStackImplementation& other) const;
    void push(const ValueType& value) override;
    void pop() override;
    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;
    void print() const override;
private:
    Vector* vector = nullptr;
};