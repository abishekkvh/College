#include<iostream>
using namespace std;

int main()
{
	int n;

	cout << "Enter Number of Elements : ";
	cin >> n;

	int arr[n];

	cout << "Enter Elements of the Array:" << endl;

	for(int i = 0; i < n; i++)
	{
		cout << "Enter Element " << i+1 << " : ";
		cin >> arr[i];
	}

	cout << "Array before Sorting : " << endl;
	for(int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl;


	for(int i = 0; i < n-1; i++)
	{
		int flag = 0;
		for(int j = 0; j < n-i-1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				swap(arr[j] , arr[j+1]);
				flag = 1;
			}
		}

		if(!flag)
		{
			break;
		}
	}

	cout << "Array after Sorting : " << endl;
	for(int i = 0; i < n; i++)
	{
		cout << arr[i] << " " ;
	}

	cout << endl;
	return 0;
}


