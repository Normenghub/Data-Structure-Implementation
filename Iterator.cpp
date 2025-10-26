#include <iostream>
using namespace std;

typedef int Elem;
struct Node{
    Elem elem;
    Node* next;
    Node* prev;
};

class Iterator{
public:
    Elem& operator*();
    bool operator==(const Iterator& p) const;
    bool operator!=(const Iterator& p) const;
    Iterator& operator++();
    Iterator& operator--();
    friend class NodeList;
private:
    Node* v;
    Iterator(Node* u);
};

class NodeList{
public:
    NodeList();
    int size() const;
    bool empty() const;
    Iterator begin() const;
    Iterator end() const;
    void insertFront(const Elem& e);
    void insertBack(const Elem& e);
    void insert(const Iterator& p, const Elem& e);
    void eraseFront();
    void eraseBack();
    void erase(const Iterator& p);
private:
    int n;
    Node* header;
    Node* trailer;
};

NodeList::NodeList(){
    n = 0;
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;
}
int NodeList::size() const{
    return n;
}
bool NodeList::empty() const{
    return n == 0;
}

Iterator NodeList::begin() const{
    return Iterator(header -> next);
}
Iterator NodeList::end() const{
    return Iterator(trailer);
}

void NodeList::insert(const Iterator& p, const Elem& e){
    Node* w = p.v;
    Node* u = w->prev;
    Node* v = new Node;
    v ->elem = e;
    v ->next = w; w->prev = v;
    v -> prev = u; u->next = v;
    n++;
}
void NodeList::insertFront(const Elem& e){
    insert(begin(), e);
}

void NodeList::insertBack(const Elem& e){
    insert(end(), e);
}

void NodeList::erase(const Iterator &p){
    Node* v = p.v;
    Node* w = v->next;
    Node* u = v->prev;
    u->next = w; w->prev = u;
    delete v;
    n--;
    
}


void NodeList::eraseFront(){
    erase(begin());
}
void NodeList::eraseBack(){
    erase(--end());
}
