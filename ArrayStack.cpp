#include <iostream>

using namespace std;

template <typename E>
class ArrayStack {
    enum {DEF_CAPACITY = 100};
public:
    ArrayStack(int cap = DEF_CAPACITY);
    int size() const;
    bool empty() const;
    const E& top() const;
    void push(const E& e);
    void pop();
    
private:
    E* S;
    int capacity;
    int t;
};

template <typename E> ArrayStack<E>::ArrayStack(int cap) : S(new E[cap]), capacity(cap), t(-1) {}

template <typename E> int ArrayStack<E>::size() const{    return t+1;     }

template <typename E> bool ArrayStack<E>::empty() const{ return t < 0; }

template <typename E> const E& ArrayStack<E>::top() const{
    if(empty()){ }// throw
    else{
        return S[t];
    }
    
}

template <typename E> void ArrayStack<E>::push(const E& e){
    if(size() == capacity){} //throw
    else{
        S[++t] = e;
    }
    
}

template <typename E> void ArrayStack<E>::pop(){
    if(empty()){} // throw
    --t;
}
