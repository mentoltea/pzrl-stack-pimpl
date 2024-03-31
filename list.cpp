#include "List.h"


void List::destroy(Node* node) {
    if (node == nullptr) return;
    Node* ptr = node;
    while(ptr->next != nullptr) {
        ptr = ptr->next;
        delete ptr->prev;
    }
    delete ptr;
}

List::~List() {
    destroy(this->node);
}

List::List(const ValueType* array, const size_t size) {
    if (size==0) return;
    this->node = new Node;
    Node* ptr = this->node;
    
    for (int i=0; i<size; i++) {
        ptr->data = array[i];
        if (i!=size-1) {
            ptr->next = new Node;
            ptr->next->prev = ptr;
            ptr = ptr->next;
        } 
    }
}

List::List(List& other) {
if (other.node==nullptr) return;

    this->node = new Node;
    
    Node* selfptr = this->node;
    Node* otherptr = other.node;
    
    while (otherptr != nullptr) {
        selfptr->data = otherptr->data;

        if (otherptr->next != nullptr) {    
            selfptr->next = new Node;
            selfptr->next->prev = selfptr;
            selfptr = selfptr->next;
        }
        
        otherptr = otherptr->next;
    }
}

List::List(const List& other) {
    if (other.node==nullptr) return;

    this->node = new Node;
    
    Node* selfptr = this->node;
    Node* otherptr = other.node;
    
    while (otherptr != nullptr) {
        selfptr->data = otherptr->data;

        if (otherptr->next != nullptr) {    
            selfptr->next = new Node;
            selfptr->next->prev = selfptr;
            selfptr = selfptr->next;
        }
        
        otherptr = otherptr->next;
    }
}

List& List::operator=(const List& other) {
    if (*this != other) {
        if (other.node==nullptr) {
            destroy(this->node);
            return *this;
        }

        if (this->node != nullptr){
            if (this->node->next!= nullptr) {
                destroy(this->node->next);
                this->node->next = nullptr;
            }
        } else {this->node = new Node;}
        
        Node* selfptr = this->node;
        Node* otherptr = other.node;
        
        while (otherptr != nullptr) {
            selfptr->data = otherptr->data;

            if (otherptr->next != nullptr) {    
                selfptr->next = new Node;
                selfptr->next->prev = selfptr;
                selfptr = selfptr->next;
            }
            
            otherptr = otherptr->next;
        }
    }
    return *this;
}


List::List(List&& other) noexcept {
    if (other.node==nullptr) return;

    this->node = new Node;

    this->node->data = other.node->data;

    this->node->next = other.node->next;
    this->node->next->prev = this->node;

    delete other.node;
    other.node = nullptr;
}

List& List::operator=(List&& other) noexcept {
    if (*this!=other) {
        if (other.node==nullptr) {
            destroy(this->node);
            return *this;
        }
        if (this->node != nullptr){
            if (this->node->next!= nullptr) {
                destroy(this->node->next);
                this->node->next = nullptr;
            }
        } else {this->node = new Node;}

        this->node->data = other.node->data;

        this->node->next = other.node->next;
        this->node->next->prev = this->node;

        delete other.node;
        other.node = nullptr;
    }
    return *this;
}

List::List(Node* node) {
    this->node = node;
}





bool List::operator==(const List& other) const {
    Node* selfptr = this->node;
    Node* otherptr = other.node;

    while (selfptr!= nullptr && otherptr != nullptr)
    {
        if (selfptr->data != otherptr->data) return false;
        selfptr = selfptr->next;
        otherptr = otherptr->next;
    }

    if ((selfptr==nullptr && otherptr!=nullptr) 
    || (selfptr!=nullptr && otherptr==nullptr)) return false;

    return true;
}

bool List::operator!=(const List& other) const {
    return !(*this==other);
}


void List::pushBack(const ValueType& value) {
    if (this->node == nullptr) {
        this->node = new Node;
        this->node->data = value;
        return;
    }

    Node* ptr = this->node;

    while(ptr->next != nullptr) {
        ptr = ptr->next;
    }

    ptr->next = new Node;
    ptr->next->prev = ptr;
    ptr = ptr->next;
    
    ptr->data = value;
}

void List::pushFront(const ValueType& value) {
    Node* new_node = new Node;

    new_node->data = value;
    new_node->next = this->node;
    this->node->prev = new_node;

    this->node = new_node;
}



void List::insert(const ValueType& value, size_t pos) {
    if (pos==0) {pushFront(value);return;}

    Node* ptr = this->node;
    for (int i=0; i<pos-1; i++) {
        if (ptr->next == nullptr) throw std::invalid_argument("Index out of range");
        ptr = ptr->next;
    }

    Node* new_node = new Node;
    new_node->data = value;
    new_node->prev = ptr;
    new_node->next = ptr->next;

    if (ptr->next!= nullptr) ptr->next->prev = new_node;
    ptr->next = new_node;
}


void List::insert(const ValueType* value, size_t size, size_t pos) {
    if (size==0) return;

    Node* startptr = new Node;
    Node* ptr = startptr;   
    for (int i=0; i<size; i++) {
        ptr->data = value[i];
        if (i!=size-1) {
            ptr->next = new Node;
            ptr->next->prev = ptr;
            ptr = ptr->next;
        } 
    }
    Node* endptr = ptr;


    if (pos==0) {
        endptr->next = this->node;
        this->node->prev = endptr;
        this->node = startptr;
        return;
    }

    ptr = this->node;
    for (int i=0; i<pos-1; i++) {
        if (ptr->next == nullptr) throw std::invalid_argument("Index out of range");
        ptr = ptr->next;
    }

    if (ptr->next != nullptr) ptr->next->prev = endptr;
    endptr->next = ptr->next;

    ptr->next = startptr;
    startptr->prev = ptr;
}


void List::insert(const List& list, size_t pos) {
    Node* ptrlist = list.node;
    Node* startptr = new Node;
    Node* ptrnew = startptr;
    while (ptrlist!=nullptr) {
        ptrnew->data = ptrlist->data;

        if (ptrlist->next != nullptr) {
            ptrnew->next = new Node;
            ptrnew->next->prev = ptrnew;
            ptrnew = ptrnew->next;
        }
        ptrlist = ptrlist->next;
    }
    Node* endptr = ptrnew;
    
    if (pos==0) {
        endptr->next = this->node;
        this->node->prev = endptr;
        this->node = startptr;
        return;
    }

    Node* ptr = this->node;
    for (int i=0; i<pos-1; i++) {
        if (ptr->next == nullptr) throw std::invalid_argument("Index out of range");
        ptr = ptr->next;
    }

    if (ptr->next != nullptr) ptr->next->prev = endptr;
    endptr->next = ptr->next;

    ptr->next = startptr;
    startptr->prev = ptr;
}


void List::popBack() {
    if (this->node == nullptr) throw std::runtime_error("Empty list"); 
    Node* ptr = this->node;
    while (ptr->next!=nullptr) ptr=ptr->next;
    if (ptr == this->node) {delete ptr; this->node = nullptr; return;}
    ptr->prev->next = nullptr;
    delete ptr;
}

void List::popFront() {
    if (this->node == nullptr) throw std::runtime_error("Empty list"); 
    if (this->node->next!=nullptr) {    
        delete this->node;
        this->node = nullptr;    
        return;
    } 
    this->node = this->node->next;
    delete this->node->prev;
    this->node->prev = nullptr;
}

void List::erase(size_t pos, size_t count) {
    if (count==0) return;
    if (this->node==nullptr) throw std::runtime_error("List is empty");
    if (pos==0) {
        int i;
        for (i=0; i<count; i++) {
            if (this->node->next == nullptr) break;
            this->node = this->node->next;
            delete this->node->prev;
        }
        this->node->prev = nullptr;
        if (i!=count-1) {
            delete this->node;
            this->node = nullptr;
        }
        return;
    }

    Node* ptr = this->node;
    for (int i=0; i<pos-1; i++) {
        if (ptr->next == nullptr) throw std::invalid_argument("Index out of range");
        ptr = ptr->next;
    }
    Node* startptr = ptr;
    Node* tmp = ptr;
    ptr = ptr->next;
    for (int i=0; i<count; i++) {
        if (ptr == nullptr) break;
        tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }
    Node* endptr = ptr;

    startptr->next = endptr;
    if (endptr != nullptr) endptr->prev = startptr;
}

void List::eraseBetween(size_t beginPos, size_t endPos) {
    if (endPos == beginPos) return;
    if (this->node==nullptr) throw std::runtime_error("List is empty");
    if (beginPos==0) {
        int i;
        for (i=0; i<endPos; i++) {
            if (this->node->next == nullptr) break;
            this->node = this->node->next;
            delete this->node->prev;
        }
        this->node->prev = nullptr;
        if (i!=endPos-1) {
            delete this->node;
            this->node = nullptr;
        }
        return;
    }

    Node* ptr = this->node;
    for (int i=0; i<beginPos-1; i++) {
        if (ptr->next == nullptr) throw std::invalid_argument("Index out of range");
        ptr = ptr->next;
    }
    Node* startptr = ptr;
    ptr = ptr->next;
    Node* tmp = ptr;
    for (int i=beginPos; i<endPos; i++) {
        if (ptr == nullptr) break;
        tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }
    Node* endptr = ptr;

    startptr->next = endptr;
    if (endptr != nullptr) endptr->prev = startptr;
}

size_t List::size() const {
    if (this->node == nullptr) {return 0;}
    size_t length = 0;
    Node* ptr = this->node;
    while (ptr!=nullptr) {
        ptr = ptr->next;
        length++;
    }
    return length;
}


ValueType& List::operator[](size_t idx) {
    Node* ptr = this->node;
    for (int i=0; i<idx; i++) {
        if (ptr->next == nullptr) throw std::invalid_argument("Index out of range");
        ptr = ptr->next;
    }
    return ptr->data;
}

const ValueType& List::operator[](size_t idx) const {
    Node* ptr = this->node;
    for (int i=0; i<idx; i++) {
        if (ptr->next == nullptr) throw std::invalid_argument("Index out of range");
        ptr = ptr->next;
    }
    return ptr->data;
}

long long List::find(const ValueType& value) const {
    size_t idx = 0;
    Node* ptr = this->node;
    while (ptr!=nullptr) {
        if (ptr->data == value) return idx;
        ptr = ptr->next;
        idx++;
    }
    return -1;
    throw std::runtime_error("Value not in list");
}  


List::Iterator::Iterator(Node* ptr) {
    node = ptr;
}

ValueType& List::Iterator::operator*() {
    return node->data;
}

const ValueType& List::Iterator::operator*() const {
    return node->data;
}

ValueType* List::Iterator::operator->() {
    return &(node->data);
}

const ValueType* List::Iterator::operator->() const {
    return &(node->data);
}

typename List::Iterator List::Iterator::operator++() {
    node = node->next;
    return *this;
}

typename List::Iterator List::Iterator::operator++(int) {
    node = node->next;
    return *this;
}

typename List::Iterator List::Iterator::operator--() {
    node = node->prev;
    return *this;
}

typename List::Iterator List::Iterator::operator--(int) {
    node = node->prev;
    return *this;
}

bool List::Iterator::operator==(const List::Iterator& other) const {
    if (this->node == other.node) return true;
    return false;
}

bool List::Iterator::operator!=(const List::Iterator& other) const {
    return !(*this == other);
}

typename List::Iterator List::begin() {
    return List::Iterator(this->node);
}

typename List::Iterator List::end() {
    Node* ptr = this->node;
    while(ptr->next!=nullptr) {
        ptr = ptr->next;
    }
    return List::Iterator(ptr);
}



void List::print() const {
    if (this->node == nullptr) {
        std::cout << "Empty" << std::endl;
        return;
    }
    Node* ptr = this->node;
    while (ptr!=nullptr) {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
}