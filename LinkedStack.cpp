#include <iostream>

using namespace std;

template <typename E>
class SLinkedList;

template <typename E>
class SNode{
private:
    E elem;
    SNode<E>* next;
    friend class SLinkedList<E>;
};

template <typename E>
class SLinkedList {
public:
    SLinkedList();
    ~SLinkedList();
    bool empty() const;
    const E& front() const;
    void addFront(const E& e);
    void removeFront();
private:
    SNode<E>* head;
};

template <typename E> void SLinkedList<E>::addFront(const E& e){
    SNode<E>* v = new SNode<E>;
    v->elem = e;
    v->next = head;
    head= v;
    
}

template <typename E> void SLinkedList<E>::removeFront(){
    SNode<E> old = head;
    head = old->next;
    delete old;
}

template <typename E> const E& SLinkedList<E>::front() const{
    if (!empty()){
        return head ->elem;
    }else {} // throw
}

typedef string Elem;
class LinkedStack{
public:
    LinkedStack();
    int size() const;
    bool empty() const;
    const Elem& top() const; // throw;
    void push(const Elem& e);
    void pop(); // throw;
private:
    SLinkedList<Elem> S;
    int n;
    
};

LinkedStack::LinkedStack() : n(0), S(){}

int LinkedStack::size() const{ return n; }
bool LinkedStack::empty() const{ return n == 0; }
const Elem& LinkedStack::top() const{
    if(empty()){} // throw;
    return S.front();
}

void LinkedStack::push(const Elem& e){
    n++;
    S.addFront(e);
}

void LinkedStack::pop(){
    
    if(empty()){} // throw;
    n--;
    S.removeFront();
}
