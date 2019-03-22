#include <iostream>
using namespace std;

void insertSort(int* parr, int len)
{
    int i, j, k;
    for (i=1; i<len; i++)
    {
        for (j=i-1; j>=0; j--)
        {
            if (parr[j] < parr[i])
                break;
        }
        if (j != i-1)
        {
            int tmp = parr[i];
            for (k=i-1; k>j; k--)
                parr[k+1] = parr[k];
            parr[k+1] = tmp;
        }
    }
}

int main()
{
    int arr[] = {30,40,60,10,20,50};
    int len = sizeof(arr) / sizeof(arr[0]);
    cout << "Before sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    insertSort(arr, len-1);
    cout << "After sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
