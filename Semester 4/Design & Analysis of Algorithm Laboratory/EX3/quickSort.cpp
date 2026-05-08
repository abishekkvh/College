#include<iostream>
using namespace std;


int hoarePartition(int A[], int low, int high)
{
    int pivot = A[low];

    int i = low + 1;
    int j = high;

    while(i <= j)
    {
        while(i <= high && A[i] <= pivot)
        {
            i++;
        }

        while(j >= low && A[j] > pivot)
        {
            j--;
        }

        if(i < j)
        {
            swap(A[i], A[j]);
        }
    }

    swap(A[low], A[j]);

    return j;
}


void quickSort(int A[], int low, int high)
{
    if(low < high)
    {
        int p = hoarePartition(A, low, high);

        quickSort(A, low, p - 1);
        quickSort(A, p + 1, high);
    }
}

int main()
{
    int n;

    cout << "Enter Number of Elements : ";
    cin >> n;

    int A[100];

    cout << "Enter Array Elements : " << endl;

    for(int i = 0; i < n; i++)
    {
        cout << "Enter Element " << i + 1 << " : ";
        cin >> A[i];
    }

    cout << "Array before Sorting : ";

    for(int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }

    cout << endl;

    quickSort(A, 0, n - 1);

    cout << "Array after Sorting : ";

    for(int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }

    cout << endl;

    return 0;
}
