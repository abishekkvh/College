#include<iostream>
using namespace std;

int main()
{
	int n;

	cout << "Enter Number of Elements : ";
	cin >> n;

	int arr[n];

	cout << "Enter Elements of the Array : " << endl;
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


	for(int i = 0; i < n; i++)
	{
		int minIndex = i;
		for(int j = i+1; j < n; j++)
		{
			if(arr[j] < arr[minIndex])
			{
				minIndex = j;
			}
		}

		if(minIndex != i)
		{
			swap(arr[minIndex] , arr[i]);
		}

	}

	cout << "Array after Sorting : " << endl;
	for(int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl;
	return 0;
}
