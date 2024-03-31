#pragma once
#include <cstdlib>
using ValueType = double;



// интерфейс для конкретных реализаций контейнера для стека
class IStackImplementation {
public:
    // добавление в хвос
    //IStackImplementation() = default;
    //IStackImplementation(IStackImplementation& copy) {std::cout << "IMPL IMPL COPY" << std::endl;};
    //IStackImplementation& operator=(const IStackImplementation& copy) = default;
    //IStackImplementation(IStackImplementation&& move) = default;
    //IStackImplementation& operator=(IStackImplementation&& move) = default;

    virtual void push(const ValueType& value) =0;
    // удаление с хвоста
    virtual void pop() =0;
    // посмотреть элемент в хвосте
    virtual const ValueType& top() const =0;
    // проверка на пустоту
    virtual bool isEmpty() const =0;
    // размер 
    virtual size_t size() const =0;
    // виртуальный деструктор
    virtual ~IStackImplementation() = default;

    virtual void print() const =0;
};

#include "VecImpl.h"
#include "ListImpl.h"