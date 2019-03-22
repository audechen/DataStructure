#include <iostream>
#include "BinomialHeap.h"
using namespace std;


int main()
{
    int a[] = {12,7,25,15,28,33,41};
    int b[] = {18,35,20,42,9,31,25,6,48,11,24,52,13};
    BinomialHeap<int>* ha = new BinomialHeap<int>();
    BinomialHeap<int>* hb = new BinomialHeap<int>();
    int alen = sizeof(a)/sizeof(a[0]);
    int blen = sizeof(b)/sizeof(b[0]);
    cout << "Data in line for heap A: ";
    for(int i=0; i<alen; i++)
    {
        cout << a[i] << " ";
        ha->insert(a[i]);
    }
    cout << endl;
    cout << "Heap A: " << endl;
    ha->print();
    cout << "Data in line for heap B: ";
    for(int i=0; i<blen; i++)
    {
        cout << b[i] << " ";
        hb->insert(b[i]);
    }
    cout << endl;
    cout << "Heap B: " << endl;
    hb->print();
    hb->remove(20);
    cout << "Remove 20 from heap B:" << endl;
    hb->print();
    hb->update(18, 2);
    cout << "Update 18 in Heap B to 2:" << endl;
    hb->print();
    hb->update(11, 44);
    cout << "Update 11 in Heap B to 44:" << endl;
    hb->print();
    ha->combine(hb);
    cout << "Combine Heap A & Heap B:" << endl;
    ha->print();
}
