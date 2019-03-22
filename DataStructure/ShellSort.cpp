#include <iostream>
using namespace std;

void GroupSort(int* parr, int len, int i, int gap)
{
    for (int j=i+gap; j<len; j+=gap)
    {
        if (parr[j] < parr[j-gap])
        {
            int tmp = parr[j];
            int k = j-gap;
            while (k>=0 && parr[k]>tmp)
            {
                parr[k+gap] = parr[k];
                k -= gap;
            }
            parr[k+gap] = tmp;
        }
    }
}

void ShellSort(int* parr, int len)
{
    for (int gap=len/2; gap>0; gap/=2)
    {
        for (int i=0; i<gap; i++)
            GroupSort(parr, len, i, gap);
    }
}

int main()
{
    int arr[] = {30,30,40,60,10,10,20,50};
    int len = sizeof(arr) / sizeof(arr[0]);
    cout << "Before shell-sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    ShellSort(arr, len);
    cout << "After shell-sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
