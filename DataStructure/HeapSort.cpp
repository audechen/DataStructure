#include <iostream>
using namespace std;

void MaxHeap(int* parr, int startPos, int endPos)
{
    int currentPos = startPos;
    int leftchild = 2*currentPos + 1;
    int tmp = parr[currentPos];
    for (; leftchild<=endPos; currentPos=leftchild, leftchild=2*leftchild+1)
    {
        if (leftchild<endPos && parr[leftchild]<parr[leftchild+1])
            leftchild++;
        if (tmp >= parr[leftchild])
            break;
        else
        {
            parr[currentPos] = parr[leftchild];
            parr[leftchild] = tmp;
        }
    }
}

void MaxHeapSort(int* parr, int len)
{
    for (int i=len/2-1; i>=0; i--)
        MaxHeap(parr, i, len-1);
    for (int i=len-1; i>0; i--)
    {
        swap(parr[0], parr[i]);
        MaxHeap(parr, 0, i-1);
    }
}

void MinHeap(int* parr, int startPos, int endPos)
{
    int currentPos = startPos;
    int leftchild = 2*currentPos+1;
    int tmp = parr[currentPos];
    for (; leftchild<=endPos; currentPos=leftchild, leftchild=2*leftchild+1)
    {
        if (leftchild<endPos && parr[leftchild+1]<parr[leftchild])
            leftchild++;
        if (tmp <= parr[leftchild])
            break;
        else
        {
            parr[currentPos] = parr[leftchild];
            parr[leftchild] = tmp;
        }
    }
}

void MinHeapSort(int* parr, int len)
{
    for (int i=len/2-1; i>=0; i--)
        MinHeap(parr, i, len-1);
    for (int i=len-1; i>0; i--)
    {
        swap(parr[0], parr[i]);
        MinHeap(parr, 0, i-1);
    }
}

int main()
{
    int arr[] = {30,30,40,60,10,10,20,50};
    int len = sizeof(arr) / sizeof(arr[0]);
    cout << "Before sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    MaxHeapSort(arr, len);
    cout << "After max-heap-sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    MinHeapSort(arr, len);
    cout << "After min-heap-sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
