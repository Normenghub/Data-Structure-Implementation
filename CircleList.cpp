#include <iostream>

using namespace std;

typedef string Elem;

class CNode{
private:
    Elem elem;
    CNode* next;
    
    friend class CircleList;
};


class CircleList{
    
public:
    CircleList();
    ~CircleList();
    bool empty() const;
    const Elem& back() const;
    const Elem& front() const;
    void advance();
    void add(const Elem& e);
    void remove();
    
private:
    CNode* cursor;
};

CircleList::CircleList() : cursor(NULL){}

CircleList::~CircleList(){
    while(!empty()) remove();
}

bool CircleList::empty() const{
    return cursor == NULL;
}
const Elem& CircleList::back() const{
    return cursor -> elem;
}

const Elem& CircleList::front() const{
    return cursor -> next ->elem;
}

void CircleList::add(const Elem& e){
    CNode* c = new CNode;
    c ->elem = e;
    if(empty()){
        c->next = c;
        cursor = c;
    }else{
        c->next = cursor->next;
        cursor ->next = c;
    }
}

void CircleList::remove(){
    CNode* o = cursor ->next;
    if(o == cursor) cursor=NULL;
    else cursor -> next = o->next;
    delete o;
}

void CircleList::advance() {
    if (!empty()) {
        cursor = cursor->next;
    }
}

