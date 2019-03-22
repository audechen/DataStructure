#include <iostream>
using namespace std;

void SelectSort(int* parr, int len)
{
    for (int i=0; i<len; i++)
    {
        int idxOfMin = i;
        for (int j=i+1; j<len; j++)
        {
            if (parr[j] < parr[idxOfMin])
                idxOfMin = j;
        }
        if (idxOfMin != i)
            swap(parr[i], parr[idxOfMin]);
    }
}

int main()
{
    int arr[] = {30,30,40,60,10,10,20,50};
    int len = sizeof(arr) / sizeof(arr[0]);
    cout << "Before select-sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    SelectSort(arr, len);
    cout << "After select-sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
