#include<iostream>
using namespace std;

void merge(int B[], int C[], int A[], int p, int q)
{
	int i = 0, j = 0, k = 0;

	while(i < p && j < q)
	{
		if(B[i] <= C[j])
		{
			A[k] = B[i];
			i++;
		}
		else
		{
			A[k] = C[j];
			j++;
		}
		k++;
	}

	while(i < p)
	{
		A[k++] = B[i++];
	}

	while(j < q)
	{
		A[k++] = C[j++];
	}

}

void mergeSort(int A[], int n)
{
	if(n < 2)
	{
		return;
	}

	int B[100], C[100];

	int mid = n / 2;

	for(int i = 0; i < mid; i++)
	{
		B[i] = A[i];
	}

	for(int i = mid; i < n; i++)
	{
		C[i - mid] = A[i];
	}

	mergeSort(B, mid);
	mergeSort(C, n-mid);

	merge(B, C, A, mid, n - mid);
}


int main()
{
	int n;

	cout << "Enter No. of Elements : ";
	cin >> n;

	int arr[n];

	cout << "Enter Array Elements : " << endl;
	for(int i = 0; i < n; i++)
	{
		cout << "Enter Element " << i+1 << " : ";
		cin >> arr[i];
	}

	cout << "Array before Sorting : ";
	for(int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	mergeSort(arr, n);

	cout << "Array after Sorting : ";
	for(int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl;
	return 0;
}
