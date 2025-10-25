#include <iostream>

using namespace std;

//Singly Linked Lists

class StringNode{
private:
    string elem;
    StringNode* next;
    
    friend class StringLinkedList;
};

class StringLinkedList{
public:
    StringLinkedList();
    ~StringLinkedList();
    bool empty() const;
    const string& front() const;
    void addFront(const string& e);
    void removeFront();
private:
    StringNode* head;
    
};

StringLinkedList::StringLinkedList() :   head(NULL){}

StringLinkedList::~StringLinkedList(){while(!empty()) removeFront();}

bool StringLinkedList::empty() const{
    return head == NULL;
}

const string& StringLinkedList::front() const{
    return head->elem;
}


void StringLinkedList::addFront(const string& e){
    StringNode* v = new StringNode;
    v->next = head;
    v->elem = e;
    head = v;
}

void StringLinkedList::removeFront(){
    StringNode* v = head;
    head= v->next;
    delete v;
}



// Generic Singly Linked List


/*
 
 template <typename E>
 class SNode{
 pivate:
 E elem;
 Snode<E>* next;
 friend class SLinkedList<E>;
 };
 
 template <typename E>
 class SLinkedList{
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
 
 
 
 
 */
