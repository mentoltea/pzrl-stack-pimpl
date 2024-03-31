#pragma once

#include "List.h"
#include "StackImplementation.h"

class ListStackImplementation: public IStackImplementation {
public:
    ListStackImplementation();
    ListStackImplementation(IStackImplementation& copy);
    ListStackImplementation(IStackImplementation&& move);
    ListStackImplementation(const ListStackImplementation& copy);
    ListStackImplementation& operator=(const ListStackImplementation& copy);
    ListStackImplementation(ListStackImplementation&& move);
    ListStackImplementation& operator=(ListStackImplementation&& move);
    ~ListStackImplementation() override;

    bool operator==(const ListStackImplementation& other) const;
    bool operator!=(const ListStackImplementation& other) const;
    void push(const ValueType& value) override;
    void pop() override;
    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;
    void print() const override;
private:
    List* list = nullptr;
};