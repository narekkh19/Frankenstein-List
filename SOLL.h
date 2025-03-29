#ifndef SOLL_H
#define SOLL_H
#include <iostream>
#include <stdexcept>

template <typename T>
class frankenstein {
    class Node {
        T val;
        Node* next;
        Node* prev;
        Node* asc;
        Node* desc;        
        
        Node () : val{0}, prev{nullptr}, next{nullptr}, desc{nullptr}, asc{nullptr} {}
        Node (T _val, Node* _prev, Node* _next) : val{_val}, prev{_prev}, next{_next}, desc{nullptr}, asc{nullptr} {};
        friend frankenstein<T>;
    };
    Node* head;
    Node* tail;
    Node* ascHead;
    Node* descHead;

    void ReorderafterPop (Node* curr);
    void PutInSortedOrder (Node* curr);
    public:
        frankenstein () : head{nullptr}, tail{nullptr}, ascHead{nullptr}, descHead{nullptr}{}
        frankenstein (const frankenstein<T>& other);
        frankenstein (frankenstein<T>&& other) noexcept;
        ~frankenstein ();
    
        frankenstein<T>& operator=(const frankenstein<T>& other);
        frankenstein<T>& operator=(frankenstein<T>&& other) noexcept;

        void push_back (T val);
        void push_front (T val);
        void pop_back ();
        void pop_front ();
        void printfrom_head ();
        void printfrom_tail ();
        void printfrom_asc ();
        void printfrom_desc ();
        void insert (T val, int pos);
        void erase (int pos);   
};

#include "SOLL.cpp"
#endif //SOLL_H