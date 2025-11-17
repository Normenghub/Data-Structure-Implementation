#include <iterator>
#include <vector>
using namespace std;

template <typename E>

class vectorCompleteTree{
public:
    vectorCompleteTree(): V(1) {}
    typedef typename vector<E>::iterator Position;
private:
    vector<E> V;
protected:
    Position pos(int i){ return V.begin() + i ;}
    int idx(const Position& p) const { return p - V.begin();}
public:
    
    int size() const {return V.size() - 1;}
    Position left(const Position& p) {return pos(2*idx(p));}
    Position right(const Position& p) {return pos(2*idx(p) + 1);}
    Position parent(const Position& p)  {return pos(idx(p) / 2);}
    bool hasLeft(const Position& p) const {return 2 * idx(p) <= size();}
    bool hasRight(const Position& p) const {return 2 * idx(p) + 1 <= size();}
    bool isRoot(const Position& p) const {return idx(p) == 1;}
    Position root() {return pos(1);}
    Position last() {return pos(size());}
    void addLast(const E& e) {V.push_back(e);}
    void removeLast() {V.pop_back();}
    void swap(const Position& p, const Position& q) {E e = *q; *q = *p; *p = e;}
    

    
};
