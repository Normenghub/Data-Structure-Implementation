#include <iostream>
#include <string>
#include <stdexcept>


template<typename K, typename V>
class Entry{
public:
    typedef K Key;
    typedef V Value;
    Entry(const K& k = K(), const V& v = V()) : _key(k), _value(v){}
    const K& key() const{return _key;}
    const V& value() const{return _value;}
    void setKey(const K& k) {_key = k;}
    void setValue(const V& v) {_value = v;}
private:
    K _key;
    V _value;
};

template <typename E>
class LinkedBinaryTree{
    
protected:
    struct Node{
        E elt;
        Node* par;
        Node* left;
        Node* right;
        Node() : elt(), par(NULL), left(NULL), right(NULL){}
    };
public:
    class Position{
        private:
        Node* v;
    public:
        Position(Node* _v = NULL) : v(_v) {}
        E& operator*() {return v->elt;}
        Position left() const {return Position(v->left);}
        Position right() const { return Position(v->right); }
        Position parent() const { return Position(v->par); }
        bool isRoot() const {return v->par == NULL;}
        bool isExternal() const {return v->left == NULL && v->right == NULL;}
        bool isInternal() const {return !isExternal();}
        friend class LinkedBInaryTree;
        bool operator==(const Position& p) const {return v== p.v;}
        bool operator!=(const Position& p) const {return v != p.v;}
    };
public:
    LinkedBinaryTree() : _root(NULL), n(0) {}
    int size() const{return n;}
    bool empty() const{return size() == 0;}
    Position root() const { return Position(_root);}
    
    void addRoot() {_root = new Node; n = 1;}
    
    void expandExternal(const Position& p){
        Node* v = p.v;
        v->left = new Node; v->left->par = v;
        v->right = new Node; v->right->par =v ;
        n+=2;
    }
    
    Position removeAboveExteranl(const Position& p){
        Node* w = p.v;
        Node* v = w->par;
        Node* sib = (w == v->left ? v->right : v->left);
        
        if(v == _root){
            _root = sib;
            sib->par = NULL;
        }else{
            Node* g =v->par;
            if(v == g->left) g->left = sib;
            else g->right = sib;
            sib->par = g;
        }
        delete w;
        delete v;
        n-=2;
        return Position(sib);
    }
    
private:
    Node* _root;
    int n;
};

template<typename K, typename V>
class SearchTree{
public:
    typedef Entry<K,V> E;
    typedef typename LinkedBinaryTree<E>::Position TPos;
        
    class Iterator{
    private:
        TPos v;
    public:
        Iterator(const TPos&& vv) : v(vv){}
        const E& operator*() {return *v;}
        bool operator== (const Iterator& p){return v == p.v;}
        bool operator!= (const Iterator& p){return v != p.v;}
        
        Iterator& operator++(){
            TPos w = v.right();
            if(w.isInternal()){
                do{v = w; w= w.left();} while(w.isInternal());
                
            }else{
                w = v.parent();
                while(v == w.right()) {v = w; w = w.parent();}
                v= w;
            }
            return *this;
        }
        friend class SearchTree;
    };
public:
    SearchTree() : T(), n(0){
        T.addRoot();
        T.expandExternal(T.root());
    }
    TPos root() const {return T.root().left();}
    int size() const {return n;}
    bool empty() const {return size() == 0;}
    
    Iterator begin(){
        TPos v= root();
        while (v.isInternal()) v= v.left();
        return Iterator(v.parent());
    }
    Iterator end() {return Iterator(T.root());}
    Iterator find(const K& k){
        TPos v = finder(k, root());
        if(v.isInternal()) return Iterator(v);
        else return end();
    }
    Iterator insert(const K& k, const V& x) {
            TPos v = inserter(k, x);
            return Iterator(v);
        }


        void erase(const K& k) {
            TPos v = finder(k, root());
            if (v.isExternal()) throw std::runtime_error("Erase of nonexistent");
            eraser(v);
        }
protected:
    TPos finder(const K& k , const TPos & v){
        if(v.isExternal()) return v;
        if(k < (*v).key()) return finder(k, v.left());
        if(k > (*v).key()) return finder(k, v.right());
        else return v;
    }
    TPos inserter(const K& k, const V& x){
        TPos v = finder(k,root());
        while(v.isInternal()) v= finder(k, v.right());
        T.expandExternal(v);
        (*v).setKey(k);
        (*v).setValue(x);
        n++;
        return v;
    }
    TPos eraser(TPos& v) {
        TPos w;
        if(v.left().isExternal()) w = v.left();
        else if(v.right().isExxternal()) w= v.right();
        else{
            w = v.right();
            do{w = w.left();} while(w.isInternal());
            TPos u = w.parent();
            (*v).setKey((*u).key());
            (*v).setValue((*u).value());
            w= w;
        }
        n--;
        return T.removeAboveExteranl(w);
    }
    
private:
    LinkedBinaryTree<E> T;
    int n;
    
};
