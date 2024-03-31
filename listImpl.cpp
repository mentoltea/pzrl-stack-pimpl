#include "ListImpl.h"

using SI = ListStackImplementation;

void SI::push(const ValueType& value) {
    //std::cout << "LIST PUSH " << list << " " << value << std::endl;
    list->pushBack(value);
}

void SI::pop() {
    list->popBack();
}

const ValueType& SI::top() const {
    return (*list)[list->size()-1];
}

bool SI::isEmpty() const {
    return (list->size()==0);
}

size_t SI::size() const {
    return list->size();
}

SI::~ListStackImplementation() {
    if (list!=nullptr) delete list;
}

SI::ListStackImplementation() {
    list = new List();
    //std::cout << "LIST IMPL C-TOR " << list << std::endl;
}

SI::ListStackImplementation(IStackImplementation& copy) {
    list = new List;
    List* tmp = new List;
    size_t size = copy.size();
    for (int i=0; i<size; i++) {
        tmp->pushBack(copy.top());
        copy.pop();
    }
    for (int i=tmp->size()-1; i>=0; i--) {
        list->pushBack((*tmp)[i]);
        copy.push((*tmp)[i]);
    }
    delete tmp;
}

SI::ListStackImplementation(IStackImplementation&& move) {
    list = new List;
    List* tmp = new List;
    size_t size = move.size();
    for (int i=0; i<size; i++) {
        tmp->pushBack(move.top());
        move.pop();
    }
    for (int i=tmp->size()-1; i>=0; i--) {
        list->pushBack((*tmp)[i]);
    }
    delete tmp, move;
}


SI::ListStackImplementation(const SI& copy) {
    list = new List(*copy.list);
}

SI& SI::operator=(const SI& copy) {
    if (*this!=copy) {
        if (list!=nullptr) delete list;
        list = new List(*copy.list);
    }
    return *this;
}

SI::ListStackImplementation(SI&& move) {
    list = move.list;
    move.list = nullptr;
}

SI& SI::operator=(SI&& move) {
    if (*this!=move) {
        if (list!=nullptr) delete list;
        list = move.list;
        move.list = nullptr;
    }
    return *this;
}

bool SI::operator==(const SI& other) const {
    return *list==*other.list;
}

bool SI::operator!=(const SI& other) const {
    return *list!=*other.list;
}


void SI::print() const {
    list->print();
}
