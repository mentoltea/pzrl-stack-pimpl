#pragma once

#include <cstring>
#include <tuple>
#include <iostream>

using ValueType = double;


struct Node
{
    ValueType data;
    Node* next = nullptr;
    Node* prev = nullptr;
};



//! \brief Класс, реализующий С++ контейнер List для типа int
class List
{
public:
    //! \note Все конструкторы и операторы присваивания должны создавать вектор, где _capacity равно _size
    //! Конструктор без параметров
    List() = default;
    //! Конструктор с параметрами
    List(const ValueType* rawArray, const size_t size);
    //! Конструктор копирования
    //! \param other - копируемый объект
    List(List& other);
    explicit List(const List& other);
    //! Оператор присваивания копированием
    //! \param other - копируемый объект
    List& operator=(const List& other);
    //! Конструктор перемещения
    //! \param other - перемещаемый объект
    explicit List(List&& other) noexcept;
    //! Оператор присваивания перемещением
    //! \param other - перемещаемый объект
    List& operator=(List&& other) noexcept;
    List(Node* node);
    //! Деструктор
    ~List();

    bool operator==(const List& other) const;
    bool operator!=(const List& other) const;

    static void destroy(Node* node);

	//! Вставка в конец
    void pushBack(const ValueType& value);
	//! Вставка в начало
    void pushFront(const ValueType& value);

	//! Вставка элемента value в позицию pos
    void insert(const ValueType& value, size_t pos);
	//! Вставка массива элементов типа ValueType в позицию pos
    void insert(const ValueType* values, size_t size, size_t pos);
	//! Вставка содержимого вектора в позицию pos
    void insert(const List& list, size_t pos);

	//! Удаление с конца
    void popBack();
	//! Удаление из начала
    void popFront();

    /*!
        \brief Удалить элемент(ы) из вектора
        \param pos: позиция начала удаляемого участка
        \param count: количество удаляемых элементов
        если (pos + count) > size, то элементы интервала [pos, size) должны быть удалены
    */
    void erase(size_t pos, size_t count = 1);

    /*!
        \brief Удалить элемент(ы) из вектора
        \param beginPos: позиция начала удаляемого участка
        \param endPos: позиция окончания удаляемого участка
        Все элементы интервала [beginPos, endPos) должны быть удалены:
            [1, 2, 3, 4] -> erase(1, 3) -> [1, 4]
        если endPos > size, то элементы интервала [beginPos, size) должны быть удалены
    */
    void eraseBetween(size_t beginPos, size_t endPos);

	//! Количество элементов
    size_t size() const;

    //! Доступ к элементу по индексу
    ValueType& operator[](size_t idx);
    //! Доступ к элементу по индексу
    const ValueType& operator[](size_t idx) const;

    //! Поиск первого вхождения значения
    //! \return - индекс элемента
    long long find(const ValueType& value) const;
   
	
	//! Класс, реализующий итератор
    class Iterator
    {
        Node* node;
    public:
        explicit Iterator(Node* ptr);
        ValueType& operator*();
        const ValueType& operator*() const;
        ValueType* operator->();
        const ValueType* operator->() const;
        Iterator operator++();
        Iterator operator++(int);
        Iterator operator--();
        Iterator operator--(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

	//! Получить итератор на начало вектора
    Iterator begin();
	//! Получить итератор на элемент вектора, следующий за последним
    Iterator end();

    void print() const;
    
private:
    Node *node = nullptr;

};

