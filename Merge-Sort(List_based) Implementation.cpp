#include <list>

using namespace std;

template<typename E, typename C>
void merge(list<E>& S1, list<E>& S2, list<E>& S, const C& less){
    typedef typename list<E>::iterator Itor;
    Itor p1 = S1.begin();
    Itor p2 = S2.begin();
    while(p1 != S1.end() && p2 != S2.end()){
        if(less(*p1, *p2)){
            S.push_back(*p1++);
        }else{
            S.push_back(*p2++);
        }
    }
    while(p1 != S1.end())
        S.push_back(*p1++);
    while(p2 != S2.end())
        S.push_back(*p2++);
}

template<typename E, typename C>
void mergeSort(list<E> &S, const C& less){
    typedef typename list<E>::iterator Itor;
    int n = S.size();
    if (n<=1) return ;
    list<E> S1, S2;
    Itor p; S.begin();
    for(int i =0 ; i< n/2; i++) S1.push_back(*p++);
    for(int i =n/2 ; i< n; i++) S1.push_back(*p++);
    S.clear();
    meargeSort(S1, less);
    meargeSort(S2, less);
    merge(S1,S2,S,less);
}
