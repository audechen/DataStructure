#ifndef DOUBLELINK_H_INCLUDED
#define DOUBLELINK_H_INCLUDED
#include <iostream>
using namespace std;

template<class T>
struct DNode{
public:
    T value;
    DNode *prev;
    DNode *next;
public:
    DNode(){}
    DNode(T t, DNode *p, DNode *n):
        value(t), prev(p), next(n){}
};

template<class T>
class DoubleLink{
public:
    DoubleLink();
    ~DoubleLink();

    int size();
    int is_empty();

    T get(int idx);
    T get_first();
    T get_last();

    int insert(int idx, T t);
    int insert_first(T t);
    int insert_last(T t);

    int del(int idx);
    int del_first();
    int del_last();
private:
    int count;
    DNode<T> *phead;
    DNode<T> *get_node(int idx);
};

template<class T>
DoubleLink<T>::DoubleLink():count(0){
    phead = new DNode<T>();
    phead->next = phead->prev = phead;
    count = 0;
}

template<class T>
DoubleLink<T>::~DoubleLink(){
    DNode<T> *ptmp;
    DNode<T> *pnode = phead->next;
    while(pnode != phead){
        ptmp = pnode;
        pnode = pnode->next;
        delete ptmp;
    }
    delete phead;
    phead = NULL;
}

template<class T>
int DoubleLink<T>::size(){
    return count;
}

template<class T>
int DoubleLink<T>::is_empty(){
    return count == 0;
}

template<class T>
DNode<T>* DoubleLink<T>::get_node(int idx)
{
    if(idx<0 || idx>=count){
        cerr << "Out of boundary!!" << endl;
        return NULL;
    }

    if(idx<=count/2){
        int i = 0;
        DNode<T> *pidx = phead->next;
        while (i++ < idx){
            pidx = pidx->next;
        }
        return pidx;
    }

    int j = 0;
    int reverse_idx = count - idx - 1;
    DNode<T> *reverse_pidx = phead->prev;
    while(j++ < reverse_idx){
        reverse_pidx = reverse_pidx->prev;
    }
    return reverse_pidx;
}

template<class T>
T DoubleLink<T>::get(int idx)
{
    return get_node(idx)->value;
}

template<class T>
T DoubleLink<T>::get_first()
{
    return get_node(0)->value;
}

template<class T>
T DoubleLink<T>::get_last()
{
    return get_node(count-1)->value;
}

template<class T>
int DoubleLink<T>::insert(int idx, T t)
{
    if(idx == 0)
    {
        return insert_first(t);
    }
    DNode<T> *pidx = get_node(idx);
    DNode<T> *pnode = new DNode<T>(t, pidx->prev, pidx);
    pidx->prev->next = pnode;
    pidx->prev = pnode;
    count++;
    return 0;
}

template<class T>
int DoubleLink<T>::insert_first(T t)
{
    DNode<T> *pnode = new DNode<T>(t, phead, phead->next);
    phead->next->prev = pnode;
    phead->next = pnode;
    count++;
    return 0;
}

template<class T>
int DoubleLink<T>::insert_last(T t)
{
    DNode<T> *pnode = new DNode<T>(t, phead->prev, phead);
    phead->prev->next = pnode;
    phead->prev = pnode;
    count++;
    return 0;
}

template<class T>
int DoubleLink<T>::del(int idx)
{
    DNode<T> *pidx = get_node(idx);
    pidx->next->prev = pidx->prev;
    pidx->prev->next = pidx->next;
    delete pidx;
    count--;
    return 0;
}

template<class T>
int DoubleLink<T>::del_first()
{
    return del(0);
}

template<class T>
int DoubleLink<T>::del_last()
{
    return del(count-1);
}


#endif // DOUBLELINK_H_INCLUDED
