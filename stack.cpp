#include "Stack.h"
#include "StackImplementation.h"



Stack::Stack(StackContainer container): _containerType(container) {
    switch (container)
    {
    case StackContainer::Vector:
        _pimpl = new VecStackImplementation;
        break;
    case StackContainer::List:
        _pimpl = new ListStackImplementation;
        break;
    default:
        break;
    }
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, 
            StackContainer container): _containerType(container) {
    switch (container)
    {
    case StackContainer::Vector:
        _pimpl = new VecStackImplementation;
        break;
    case StackContainer::List:
        _pimpl = new ListStackImplementation;
        break;
    default:
        break;
    }

    for (int i=0; i<arraySize; i++) {
        _pimpl->push(valueArray[i]);
    }
}

Stack::Stack(const Stack& copyStack): _containerType(copyStack._containerType) {
    switch (copyStack._containerType)
    {
    case StackContainer::Vector:
        _pimpl = new VecStackImplementation(*copyStack._pimpl);
        break;
    case StackContainer::List:
        _pimpl = new ListStackImplementation(*copyStack._pimpl);
        break;
    default:
        break;
    }
}

Stack& Stack::operator=(const Stack& copyStack) {
    _containerType = copyStack._containerType;
    //std::cout << "COPY OPERATOR" << std::endl;
    if (_pimpl != copyStack._pimpl) {
        if (_pimpl!=nullptr) delete _pimpl;
        switch (copyStack._containerType)
        {
        case StackContainer::Vector:
            //std::cout << "GOTO VEC" << std::endl;
            _pimpl = new VecStackImplementation(*copyStack._pimpl);
            break;
        case StackContainer::List:
            //std::cout << "GOTO LIST" << std::endl;
            _pimpl = new ListStackImplementation(*copyStack._pimpl);
            break;
        default:
            break;
        }
    }
    return *this;
}

Stack::Stack(Stack&& moveStack) noexcept: _containerType(moveStack._containerType) {
    switch (moveStack._containerType)
    {
    case StackContainer::Vector:
        _pimpl = new VecStackImplementation;
        *_pimpl = std::move(*moveStack._pimpl);
        break;
    case StackContainer::List:
        _pimpl = new ListStackImplementation;
        *_pimpl = std::move(*moveStack._pimpl);
        break;
    default:
        break;
    }
}

Stack& Stack::operator=(Stack&& moveStack) noexcept {
    _containerType = moveStack._containerType;
    if (_pimpl != moveStack._pimpl) {
        if (_pimpl!=nullptr) delete _pimpl;
        switch (moveStack._containerType)
            {
            case StackContainer::Vector:
                _pimpl = new VecStackImplementation;
                *_pimpl = std::move(*moveStack._pimpl);
                break;
            case StackContainer::List:
                _pimpl = new ListStackImplementation;
                *_pimpl = std::move(*moveStack._pimpl);
                break;
            default:
                break;
            }
    }
    return *this;
}

Stack::~Stack() {
    if (_pimpl!=nullptr) delete _pimpl;
}




void Stack::push(const ValueType& value) {
    _pimpl->push(value);
}

void Stack::pop() {
    _pimpl->pop();
}

const ValueType& Stack::top() const {
    return _pimpl->top();
}

bool Stack::isEmpty() const {
    return _pimpl->isEmpty();
}

size_t Stack::size() const {
    return _pimpl->size();
}

void Stack::print() const {
    _pimpl->print();
}