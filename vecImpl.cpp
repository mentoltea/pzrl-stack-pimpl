#include "VecImpl.h"

using SI = VecStackImplementation;

void SI::push(const ValueType& value) {
    //std::cout << "VECTOR PUSH " << vector << " " << value << std::endl;
    vector->pushBack(value);
}

void SI::pop() {
    vector->popBack();
}

const ValueType& SI::top() const {
    return (*vector)[vector->size()-1];
}

bool SI::isEmpty() const {
    return (vector->size()==0);
}

size_t SI::size() const {
    return vector->size();
}

SI::~VecStackImplementation() {
     if (vector!=nullptr) delete vector;
}

SI::VecStackImplementation() {
    //std::cout << "NEW VEC" << std::endl;
    vector = new Vector;
    //std::cout << "VECTOR IMPL C-TOR " << vector << std::endl;
}

SI::VecStackImplementation(IStackImplementation& copy) {
    //std::cout << "VEC IMPL COPY" << std::endl;
    vector = new Vector;
    Vector* tmp = new Vector;
    size_t size = copy.size();
    for (int i=0; i<size; i++) {
        tmp->pushBack(copy.top());
        copy.pop();
    }
    for (int i=tmp->size()-1; i>=0; i--) {
        vector->pushBack((*tmp)[i]);
        copy.push((*tmp)[i]);
    }
    delete tmp;
}

SI::VecStackImplementation(IStackImplementation&& move) {
    //std::cout << "VEC IMPL MOVE" << std::endl;
    vector = new Vector;
    Vector* tmp = new Vector;
    size_t size = move.size();
    for (int i=0; i<size; i++) {
        tmp->pushBack(move.top());
        move.pop();
    }
    for (int i=tmp->size()-1; i>=0; i--) {
        vector->pushBack((*tmp)[i]);
    }
    delete tmp, move;
}


SI::VecStackImplementation(const SI& copy) {
    //std::cout << "VEC COPY" << std::endl;
    vector = new Vector(*copy.vector);
}

SI& SI::operator=(const SI& copy) {
    //std::cout << "VEC COPY OPER" << std::endl;
    if (*this!=copy) {
        if (vector!=nullptr) delete vector;
        vector = new Vector(*copy.vector);
    }
    return *this;
}

SI::VecStackImplementation(SI&& move) {
    //std::cout << "VEC MOVE" << std::endl;
    vector = move.vector;
    move.vector = nullptr;
}

SI& SI::operator=(SI&& move) {
    //std::cout << "VEC MOVE OPER" << std::endl;
    if (*this!=move) {
        if (vector!=nullptr) delete vector;
        vector = move.vector;
        move.vector = nullptr;
    }
    return *this;
}

bool SI::operator==(const SI& other) const {
    return *vector==*other.vector;
}

bool SI::operator!=(const SI& other) const {
    return *vector!=*other.vector;
}

void SI::print() const {
    //std::cout << vector->array() << std::endl;
    vector->print();
}