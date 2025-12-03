#include <iostream>
#include <list>
#include <stdexcept>
#include <string>


template <typename K, typename V>
class Entry {
public:
    typedef K Key;
    typedef V Value;
    Entry(const K& k = K(), const V& v = V()) : _key(k), _value(v) { }
    const K& key() const { return _key; }
    const V& value() const { return _value; }
    void setKey(const K& k) { _key = k; }
    void setValue(const V& v) { _value = v; }
private:
    K _key;
    V _value;
};


template <typename E>
class LinkedBinaryTree {
protected:
    // Node struct
    struct Node {
        E elt;
        Node* par;
        Node* left;
        Node* right;
        Node() : elt(), par(NULL), left(NULL), right(NULL) { }
    };

public:
    
    class Position {
    private:
        Node* v; // pointer to the node
    public:
        // Constructor
        Position(Node* _v = NULL) : v(_v) { }
        
        // Dereference operator
        E& operator*() { return v->elt; }
        
        // Navigation methods
        Position left() const { return Position(v->left); }
        Position right() const { return Position(v->right); }
        Position parent() const { return Position(v->par); }
        
        // Status methods
        bool isRoot() const { return v->par == NULL; }
        bool isExternal() const { return v->left == NULL && v->right == NULL; }
        bool isInternal() const { return !isExternal(); }
        
        // Friend declaration to allow Tree access
        friend class LinkedBinaryTree<E>;
        
        // Comparison operators
        bool operator==(const Position& p) const { return v == p.v; }
        bool operator!=(const Position& p) const { return v != p.v; }
    };

    typedef std::list<Position> PositionList;

public:
    // Constructor
    LinkedBinaryTree() : _root(NULL), n(0) { }

    // Standard methods
    int size() const { return n; }
    bool empty() const { return size() == 0; }
    Position root() const { return Position(_root); }
    
    // 트리 조작 함수
    
    // 빈 트리에 루트 추가
    void addRoot() {
        _root = new Node;
        n = 1;
    }
    
    
    // 외부 노드(Leaf)를 내부 노드로 확장 (자식 2개 생성)
    void expandExternal(const Position& p) {
        Node* v = p.v;
        v->left = new Node;
        v->left->par = v;
        v->right = new Node;
        v->right->par = v;
        n += 2;
    }

    
    // 외부 노드 p와 그 부모를 삭제하고, 형제 노드를 부모 자리로 올림
    Position removeAboveExternal(const Position& p) {
        Node* w = p.v;
        Node* v = w->par; // w의 부모 (삭제될 노드)
        Node* sib = (w == v->left ? v->right : v->left); // w의 형제
        
        if (v == _root) {
            _root = sib;
            sib->par = NULL;
        } else {
            Node* gpar = v->par; // 조부모
            if (v == gpar->left) gpar->left = sib;
            else gpar->right = sib;
            sib->par = gpar;
        }
        delete w;
        delete v;
        n -= 2;
        return Position(sib);
    }

protected:
    Node* _root;
    int n;
};


template <typename E>
class SearchTree {
public:
    // Type definitions
    typedef typename E::Key K;
    typedef typename E::Value V;
    typedef LinkedBinaryTree<E> BinaryTree;
    typedef typename BinaryTree::Position TPos;

    
    class Iterator {
    private:
        TPos v;
    public:
        Iterator(const TPos& vv) : v(vv) { }
        const E& operator*() const { return *v; }
        E& operator*() { return *v; }
        bool operator==(const Iterator& p) const { return v == p; }
        bool operator!=(const Iterator& p) const { return v != p; }

        
        Iterator& operator++() {
            TPos w = v.right();
            if (w.isInternal()) {
                do { v = w; w = w.left(); }
                while (w.isInternal());
            }
            else {
                w = v.parent();
                while (v == w.right()) {
                    v = w; w = w.parent();
                }
                v = w;
            }
            return *this;
        }
        friend class SearchTree<E>;
    };

public:
    
    SearchTree() : T(), n(0) {
        T.addRoot();                // 1. Super Root 생성
        T.expandExternal(T.root()); // 2. Super Root 밑에 가상 루트(Virtual Root) 생성
        // 초기 상태: SuperRoot -> Left: VirtualRoot(External), Right: Empty(External)
    }

    int size() const { return n; }
    bool empty() const { return n == 0; }

    // Root: Super Root의 왼쪽 자식을 반환 (Virtual Root)
    TPos root() const { return T.root().left(); }

    // Begin: 가장 왼쪽 노드 (In-order 시작점)
    Iterator begin() {
        TPos v = root();
        while (v.isInternal()) v = v.left();
        return Iterator(v.parent());
    }
    
    // End: Super Root를 반환
    Iterator end() { return Iterator(T.root()); }

    
    // Find
    Iterator find(const K& k) {
        TPos v = finder(k, root());
        if (v.isInternal()) return Iterator(v);
        else return end();
    }

    // Insert
    Iterator insert(const K& k, const V& x) {
        TPos v = inserter(k, x);
        return Iterator(v);
    }

    // Erase
    void erase(const K& k) {
        TPos v = finder(k, root());
        if (v.isExternal()) { // 못 찾음
            throw std::runtime_error("Erase of nonexistent element");
        }
        eraser(v);
    }

protected:
    // Helper Functions (Recursive / Utility)

    // Finder: 키 k를 찾거나, 들어갈 위치(External Node)를 반환
    TPos finder(const K& k, const TPos& v) {
        if (v.isExternal()) return v;
        if (k < (*v).key()) return finder(k, v.left());
        else if ((*v).key() < k) return finder(k, v.right());
        else return v; // Found
    }

    // Inserter
    TPos inserter(const K& k, const V& x) {
        TPos v = finder(k, root());
        while (v.isInternal()) { // 키 중복시 오른쪽으로 이동 (정책에 따라 다름)
            v = finder(k, v.right());
        }
        // v는 현재 External Node임. 이곳을 내부 노드로 확장.
        T.expandExternal(v);
        (*v).setKey(k);
        (*v).setValue(x);
        n++;
        return v;
    }

    // Eraser
    TPos eraser(TPos& v) {
        TPos w;
        // Case 1: 자식 중 하나가 외부 노드인 경우 (쉽게 삭제 가능)
        if (v.left().isExternal()) w = v.left();
        else if (v.right().isExternal()) w = v.right();
        else {
            // Case 2: 두 자식이 모두 내부 노드인 경우 -> 계승자(Successor) 탐색
            w = v.right();
            do { w = w.left(); } while (w.isInternal());
            TPos u = w.parent(); // w는 외부노드이므로 u가 실제 계승자(가장 작은 값)
            
            // 값 복사 (u의 내용을 v로 이동)
            (*v).setKey((*u).key());
            (*v).setValue((*u).value());
            
            // 실제 삭제는 u 위치에서 진행하기 위해 w를 조정
            // w는 u의 왼쪽 자식(External)이므로, removeAboveExternal(w)를 호출하면
            // w와 그 부모 u가 삭제됨.
            w = u.left();
        }
        n--;
        return T.removeAboveExternal(w);
    }

private:
    BinaryTree T; // LinkedBinaryTree를 멤버로 포함 (Composition)
    int n;        // Entry 개수
};
