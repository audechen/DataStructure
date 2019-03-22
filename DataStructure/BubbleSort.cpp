#include <iostream>
using namespace std;

void bubbleSort(int* parr, int len)
{
    int flag;
    for (int i=len-1; i>0; i--)
    {
        flag = 0;
        for (int j=0; j<i; j++)
        {
            if (parr[j] > parr[j+1])
            {
                int tmp = parr[j];
                parr[j] = parr[j+1];
                parr[j+1] = tmp;
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}

int main()
{
    int arr[] = {20, 40, 30, 10, 60, 50};
    int len = (sizeof(arr)) / (sizeof(arr[0]));
    cout << "before sort: ";
    for (int i=0; i<len; i++)
        cout << arr[i] << " ";
    cout << endl;
    bubbleSort(arr, len);
    cout << "after sort: ";
    for (int i=0; i<len; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}
