#include <iostream>
using namespace std;

class CircleList;

typedef string Elem;

class CNode{
private:
    Elem elem;
    CNode * next;
    
    friend class CircleList;
};

class CircleList{
public:
    CircleList();
    ~CircleList();
    bool empty() const;
    const Elem& front() const;
    const Elem& back() const;
    void advance();
    void add(const Elem& e);
    void remove();
    
private:
    CNode* cursor;
};

CircleList:: CircleList() : cursor(NULL){}

CircleList::~CircleList(){
    while(!empty()) remove();
}

bool CircleList::empty() const{
    return cursor == NULL;
}
const Elem& CircleList::back() const{
    return cursor->elem;
}

const Elem& CircleList::front() const{
    return cursor->next -> elem;
}
void CircleList::advance(){
    cursor = cursor->next;
}
void CircleList::add(const Elem& e){
    CNode* c = new CNode;
    c->elem = e;
    if(cursor == NULL){
        c->next = c;
        cursor = c;
    }else{
        c->next = cursor->next;
        cursor-> next = c;
    }
    
}

void CircleList::remove(){
    CNode* old = cursor ->next;
    if(old == cursor){
        cursor = NULL;
    }else{
        cursor->next = old -> next;
    }
    
    delete old;
}


class LinkedQueue{
public:
    LinkedQueue();
    int size() const;
    bool empty() const;
    const Elem& front() const; //throw
    void enqueue(const Elem& e);
    void dequeue(); // throw
private:
    CircleList C;
    int n;
};

LinkedQueue::LinkedQueue() : C(), n(0){}

int LinkedQueue::size() const{
    return n;
}

bool LinkedQueue::empty() const{
    return n==0;
}

const Elem& LinkedQueue::front() const{
    if(empty()){ }// throw
    return C.front();
}

void LinkedQueue::enqueue(const Elem& e){
    C.add(e);
    C.advance();
    n++;
}

void LinkedQueue::dequeue(){
    if(empty()){} // throw;
    C.remove();
    n--;
}
