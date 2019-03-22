#include <iostream>
#include <iomanip>>
using namespace std;

template<class T>
class MaxHeap
{
private:
    T* mHeap;
    int mCapacity;
    int mSize;
private:
    void filterdown(int start, int end);
    void filterup(int start);
public:
    MaxHeap();
    MaxHeap(int capacity);
    ~MaxHeap();

    int getIndex(T data);
    int remove(T data);
    int insert(T data);
    void print();
};

template<class T>
MaxHeap<T>::MaxHeap()
{
    new (this)MaxHeap(30);
}

template<class T>
MaxHeap<T>::MaxHeap(int capacity)
{
    mSize = 0;
    mCapacity = capacity;
    mHeap = new T[mCapacity];
}

template<class T>
MaxHeap<T>::~MaxHeap()
{
    mSize = 0;
    mCapacity = 0;
    delete[] mHeap;
}

template<class T>
int MaxHeap<T>::getIndex(T data)
{
    for(int i=0; i<mSize; i++)
    {
        if(data == mHeap[i])
            return i;
    }
    return -1;
}

template<class T>
void MaxHeap<T>::filterdown(int start, int end)
{
    int c = start;
    int l = 2*c+1;
    T tmp = mHeap[c];
    while(l <= end)
    {
        if(l<end && mHeap[l]<mHeap[l+1])
            l++;
        if(tmp >= mHeap[l])
            break;
        else
        {
            mHeap[c] = mHeap[l];
            c = l;
            l = 2*l+1;
        }
    }
    mHeap[c] = tmp;
}

template<class T>
int MaxHeap<T>::remove(T data)
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
void MaxHeap<T>::filterup(int start)
{
    int c = start;
    int p = (c-1)/2;
    T tmp = mHeap[c];
    while(c > 0)
    {
        if(mHeap[p] >= tmp)
            break;
        else
        {
            mHeap[c] = mHeap[p];
            c = p;
            p = (p-1)/2;
        }
    }
    mHeap[c] = tmp;
}

template<class T>
int MaxHeap<T>::insert(T data)
{
    if(mSize == mCapacity)
        return -1;
    mHeap[mSize] = data;
    filterup(mSize);
    mSize++;

    return 0;
}

template<class T>
void MaxHeap<T>::print()
{
    for(int i=0; i<mSize; i++)
        cout << mHeap[i] << " ";
}

int main()
{
    int a[] = {10,40,30,60,90,70,20,50,80};
    int len = sizeof(a)/sizeof(a[0]);
    MaxHeap<int>* tree = new MaxHeap<int>();
    cout << "Data in line: ";
    for(int i=0; i<len; i++)
    {
        cout << a[i] << " ";
        tree->insert(a[i]);
    }
    cout << "\nThis is a MaxHeap: ";
    tree->print();
    int n = 85;
    tree->insert(n);
    cout << "\nInsert data: " << n;
    cout << "\nResult: ";
    tree->print();
    n = 90;
    cout << "\nRemove data: " << n;
    cout << "\nResult: ";
    tree->print();
    cout << endl;

    return 0;

}














