#include <iostream>
using namespace std;

template<class T>
class MinHeap
{
private:
    T *mHeap;
    int mCapacity;
    int mSize;
private:
    void filterdown(int start, int end);
    void filterup(int start);
public:
    MinHeap();
    MinHeap(int capacity);
    ~MinHeap();

    int getIndex(T data);
    int remove(T data);
    int insert(T data);
    void print();
};

template<class T>
MinHeap<T>::MinHeap()
{
    new (this)MinHeap(30);
}

template<class T>
MinHeap<T>::MinHeap(int capacity)
{
    mSize = 0;
    mCapacity = capacity;
    mHeap = new T[mCapacity];
}

template<class T>
MinHeap<T>::~MinHeap()
{
    mSize = 0;
    mCapacity = 0;
    delete[] mHeap;
}

template<class T>
int MinHeap<T>::getIndex(T data)
{
    for(int i=0; i<mSize; i++)
    {
        if(data == mHeap[i])
            return i;
    }
    return -1;
}

template<class T>
void MinHeap<T>::filterdown(int start, int end)
{
    int c = start;
    int l = c*2+1;
    T tmp = mHeap[c];
    while(l<=end)
    {
        if(l<end && mHeap[l]>mHeap[l+1])
            l++;
        if(tmp <= mHeap[l])
            break;
        else
        {
            mHeap[c] = mHeap[l];
            c = l;
            l = l*2+1;
        }
    }
    mHeap[c] = tmp;
}

template<class T>
int MinHeap<T>::remove(T data)
{
    int index;
    if(mSize == 0)
        return -1;
    index = getIndex(data);
    if(index == -1)
        return -1;
    mHeap[index] = mHeap[--mSize];
    filterdown(index, mSize-1);
    return 0;
}

template<class T>
void MinHeap<T>::filterup(int start)
{
    int c = start;
    int p = (c-1)/2;
    T tmp = mHeap[c];
    while(c > 0)
    {
        if(mHeap[p] <= tmp)
            break;
        else{
            mHeap[c] = mHeap[p];
            c = p;
            p = (p-1)/2;
        }
    }
    mHeap[c] = tmp;
}

template<class T>
int MinHeap<T>::insert(T data)
{
    if(mSize == mCapacity)
        return -1;
    mHeap[mSize] = data;
    filterup(mSize);
    mSize++;
    return 0;
}

template<class T>
void MinHeap<T>::print()
{
    for(int i=0; i<mSize; i++)
        cout << mHeap[i] << " ";
}

int main()
{
    int a[] = {80,40,30,60,90,70,10,50,20};
    int len = sizeof(a)/sizeof(a[0]);
    MinHeap<int>* tree = new MinHeap<int>();
    cout << "Data in line: ";
    for (int i=0; i<len; i++)
    {
        cout << a[i] << " ";
        tree->insert(a[i]);
    }
    cout << "\nMinHeap: ";
    tree->print();
    int n = 15;
    tree->insert(n);
    cout << "\nInsert: " << n << endl;
    cout << "MinHeap: ";
    tree->print();
    n = 10;
    cout << "\nDelete: " << n << endl;
    tree->remove(n);
    cout << "Min Heap: ";
    tree->print();
    cout << endl;
    return 0;
}
