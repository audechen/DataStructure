#include <iostream>
#include "LeftHeap.h"
using namespace std;

int main()
{
    int a[] = {10,40,24,30,36,20,12,16};
    int b[] = {17,13,11,15,19,21,23};
    int a_len = sizeof(a)/sizeof(a[0]);
    int b_len = sizeof(b)/sizeof(b[0]);
    LeftHeap<int>* heap_a = new LeftHeap<int>();
    LeftHeap<int>* heap_b = new LeftHeap<int>();
    cout << "Data in line for heap A: ";
    for (int i=0; i<a_len; i++)
    {
        cout << a[i] << " ";
        heap_a->insert(a[i]);
    }
    cout << "\nHeap A: " << endl;
    heap_a->print();
    cout << "\nData in line for heap B: ";
    for (int i=0; i<b_len; i++)
    {
        cout << b[i] << " ";
        heap_b->insert(b[i]);
    }
    cout << "\nHeap B: " << endl;
    heap_b->print();
    heap_a->merge(heap_b);
    cout << "\nAdd heap B to heap A: " << endl;
    heap_a->print();

    heap_a->destory();
    return 0;
}
