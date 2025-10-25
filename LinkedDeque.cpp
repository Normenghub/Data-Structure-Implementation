#include <iostream>

using namespace std;
typedef string Elem;
class DLinkedList;

struct DNode{
    DNode* next;
    DNode* prev;
    Elem elem;
};

class DLinkedList{
public:
    DLinkedList();
    void add(DNode* v, const Elem& e);
    void addFront(const Elem& e);
    void addBack(const Elem& e);
    void remove(DNode* v);
    void removeFront();
    void removeBack();
private:
    DNode* header;
    DNode* trailer;
    int n ;
    
};

DLinkedList::DLinkedList(){
    n = 0;
    header = new DNode;
    trailer = new DNode;
    header->next = trailer;
    trailer->prev = header;
}

void DLinkedList::add(DNode* v , const Elem& e){
    DNode* u = new DNode; u->elem = e;
    u->next = v;
    u->prev = v ->prev;
    u->prev->next = u;
}

void DLinkedList::addFront(const Elem& e){
    add(header->next, e);
}
void DLinkedList::addBack(const Elem& e){
    add(trailer, e);
}

void DLinkedList::remove(DNode* v){
    DNode* u = v->prev;
    DNode* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}


void DLinkedList::removeFront(){
    remove(header->next);
}
void DLinkedList::removeBack(){
    remove(trailer->prev);
}


class LinkedDeque{
public:
    LinkedDeque();
    
    int size() const;
    bool empty() const;
    const Elem& front() const; // throw
    const Elem& back() const; // throw
    void insertFront(const Elem& e); //throw
    void insertBack(const Elem& e); //throw
    void removeFront(); //throw
    void removeBack(); //throw
private:
    DLinkedList D;
    int n;
};
LinkedDeque::LinkedDeque() : n(0),D(){}

bool LinkedDeque::empty() const{
    return n == 0;
}
int LinkedDeque::size() const{
    return n;
}

void LinkedDeque::insertFront(const Elem& e){
    D.addFront(e);
    n++;
}

void LinkedDeque::insertBack(const Elem& e){
    D.addBack(e);
    n++;
}

void LinkedDeque::removeFront(){
    if(empty()){
        //throw
    }
    D.removeFront();
    n--;
}

void LinkedDeque::removeBack(){
    if(empty()){
        //throw
    }
    D.removeBack();
    n--;
}
