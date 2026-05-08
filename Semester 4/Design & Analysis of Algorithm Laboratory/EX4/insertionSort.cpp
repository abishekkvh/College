#include<iostream>
using namespace std;

int main()
{
	int n;

	cout << "Enter No. Of Elements : ";
	cin >> n;

	int arr[n];


	for(int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	for(int i = 1 ; i <  n; i++)
	{
		int j = i - 1;
		int v  = arr[i];

		while(j >= 0 && v < arr[j])
		{
			if(arr[j] > arr[j+1])
			{
				swap(arr[j], arr[j+1]);
				j--;
			}
		}
		arr[j] = v;
	}

	for(int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}

	return 0;
}

