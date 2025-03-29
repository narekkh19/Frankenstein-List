#include "SOLL.h"

// Default constructor already defined in header

// Destructor: delete all nodes
template <typename T>
frankenstein<T>::~frankenstein() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = ascHead = descHead = nullptr;
}

// Copy constructor: deep copy using push_back
template <typename T>
frankenstein<T>::frankenstein(const frankenstein<T>& other)
    : head{nullptr}, tail{nullptr}, ascHead{nullptr}, descHead{nullptr} {
    for (Node* curr = other.head; curr != nullptr; curr = curr->next) {
        push_back(curr->val);
    }
}

// Copy assignment operator
template <typename T>
frankenstein<T>& frankenstein<T>::operator=(const frankenstein<T>& other) {
    if (this != &other) {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = ascHead = descHead = nullptr;
        for (Node* curr = other.head; curr != nullptr; curr = curr->next) {
            push_back(curr->val);
        }
    }
    return *this;
}

// Move constructor
template <typename T>
frankenstein<T>::frankenstein(frankenstein<T>&& other) noexcept
    : head(other.head), tail(other.tail), ascHead(other.ascHead), descHead(other.descHead) {
    other.head = other.tail = other.ascHead = other.descHead = nullptr;
}

// Move assignment operator
template <typename T>
frankenstein<T>& frankenstein<T>::operator=(frankenstein<T>&& other) noexcept {
    if (this != &other) {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        head = other.head;
        tail = other.tail;
        ascHead = other.ascHead;
        descHead = other.descHead;
        other.head = other.tail = other.ascHead = other.descHead = nullptr;
    }
    return *this;
}

// Insert new node in sorted order based on val
template <typename T>
void frankenstein<T>::PutInSortedOrder(Node* curr) {
    Node dummy;
    dummy.asc = ascHead;
    dummy.desc = nullptr;
    // Link dummy to the start of asc order list
    if (ascHead) ascHead->desc = &dummy;
    Node* sorted = &dummy;
    while (sorted->asc && curr->val > sorted->asc->val) {
        sorted = sorted->asc;
    }
    if (!sorted->asc) { // Insert at the end
        sorted->asc = curr;
        curr->asc = nullptr;
        curr->desc = sorted;
        descHead = curr;
    } else {
        curr->asc = sorted->asc;
        sorted->asc->desc = curr;
        curr->desc = sorted;
        sorted->asc = curr;
        if (!sorted->desc) { // Update ascHead if needed
            ascHead = sorted->asc;
        }
    }
    if (ascHead) ascHead->desc = nullptr;
}

// Adjust sorted order pointers after removal of a node
template <typename T>
void frankenstein<T>::ReorderafterPop(Node* curr) {
    Node* tmp = ascHead;
    while (tmp) {
        if (tmp == curr) {
            if (!curr->desc && !curr->asc) { 
                ascHead = nullptr;
                descHead = nullptr;
            } else if (!curr->desc) { 
                ascHead = ascHead->asc;
                if (ascHead) ascHead->desc = nullptr;
            } else if (!curr->asc) { 
                descHead = descHead->desc;
                if (descHead) descHead->asc = nullptr;
            } else { 
                curr->desc->asc = curr->asc;
                curr->asc->desc = curr->desc;
            }
            break;
        }
        tmp = tmp->asc;
    }
}

// Append value to the end of the list
template <typename T>
void frankenstein<T>::push_back(T val) {
    if (!tail) {
        head = tail = ascHead = descHead = new Node(val, nullptr, nullptr);
    } else {
        tail->next = new Node(val, tail, nullptr);
        tail = tail->next;
        PutInSortedOrder(tail);
    }
}

// Prepend value to the front of the list
template <typename T>
void frankenstein<T>::push_front(T val) {
    if (!head) {
        head = tail = new Node(val, nullptr, nullptr);
        ascHead = descHead = head;
    } else {
        Node* tmp = new Node(val, nullptr, head);
        head->prev = tmp;
        head = tmp;
        PutInSortedOrder(head);
    }
}

// Remove the last element
template <typename T>
void frankenstein<T>::pop_back() {
    if (!tail) {
        throw std::runtime_error("pop_back(): List is empty");
    } else if (!tail->prev) {
        Node* tmp = tail;
        head = tail = nullptr;
        ReorderafterPop(tmp);
        delete tmp;
    } else {
        Node* tmp = tail;
        tail = tail->prev;
        ReorderafterPop(tmp);
        delete tmp;
        tail->next = nullptr;
    }
}

// Remove the first element
template <typename T>
void frankenstein<T>::pop_front() {
    if (!head) {
        throw std::runtime_error("pop_front(): List is empty");
    } else if (!head->next) {
        Node* tmp = head;
        head = tail = nullptr;
        ReorderafterPop(tmp);
        delete tmp;
    } else {
        Node* tmp = head;
        head = head->next;
        ReorderafterPop(tmp);
        delete tmp;
        head->prev = nullptr;
    }
}

// Insert a value at a given position (0-based index)
template <typename T>
void frankenstein<T>::insert(T val, int pos) {
    if (pos < 0) {
        throw std::runtime_error("insert(): Negative position is invalid");
    }
    Node* insertNode = new Node(val, nullptr, nullptr);
    Node* tmp = head;
    if (!head) {
        push_front(val);
        PutInSortedOrder(insertNode);
        return;
    }
    while (tmp->next && pos-- > 0) {
        tmp = tmp->next;
    }
    if (!tmp->prev) {
        push_front(val);
        return;
    } else if (!tmp->next) {
        push_back(val);
        return;
    } else {
        tmp->next->prev = insertNode;
        insertNode->next = tmp->next;
        tmp->next = insertNode;
        insertNode->prev = tmp;
        PutInSortedOrder(insertNode);
    }
}

// Erase an element at a given position (0-based index)
template <typename T>
void frankenstein<T>::erase(int pos) {
    if (pos < 0) {
        throw std::runtime_error("erase(): Negative position is invalid");
    }
    if (pos == 0) {
        pop_front();
    } else {
        Node* tmp = head;
        if (!head) {
            throw std::runtime_error("erase(): Cannot erase from an empty list");
        }
        while (tmp && pos-- > 0) {
            tmp = tmp->next;
        }
        if (!tmp) {
            throw std::runtime_error("erase(): Position out of range");
        }
        if (!tmp->next) {
            pop_back();
        } else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            ReorderafterPop(tmp);
            delete tmp;
        }
    }
}

// Print the list from head to tail
template <typename T>
void frankenstein<T>::printfrom_head() {
    Node* tmp = head;
    while (tmp) {
        std::cout << tmp->val << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

// Print the list from tail to head
template <typename T>
void frankenstein<T>::printfrom_tail() {
    Node* tmp = tail;
    while (tmp) {
        std::cout << tmp->val << " ";
        tmp = tmp->prev;
    }
    std::cout << std::endl;
}

// Print the list in ascending sorted order
template <typename T>
void frankenstein<T>::printfrom_asc() {
    Node* tmp = ascHead;
    while (tmp) {
        std::cout << tmp->val << " ";
        tmp = tmp->asc;
    }
    std::cout << std::endl;
}

// Print the list in descending sorted order
template <typename T>
void frankenstein<T>::printfrom_desc() {
    Node* tmp = descHead;
    while (tmp) {
        std::cout << tmp->val << " ";
        tmp = tmp->desc;
    }
    std::cout << std::endl;
}
