#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int n;
	cout << "Enter No. Of Elements : ";
	cin >> n;

	int x[n], y[n];

	cout << "Enter Points (x,y) : " << endl;
	for(int i = 0; i < n; i++)
	{
		cin >> x[i] >> y[i];
	}

	float minDist = 100000000;

	int x_1 = 0;
	int x_2 = 0;
	int y_1 = 0;
	int y_2 = 0;

	for(int i = 0; i < n; i++)
	{
		for(int j = i+1; j < n; j++)
		{
			float d = sqrt(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2));

			if(d < minDist)
			{
				minDist = d;
				x_1 = x[i];
				x_2 = x[j];
				y_1 = y[i];
				y_2 = y[j];
			}
		}
	}

	cout << "Minimum Distance : " << minDist << endl;
	cout << "Closest pair : " << "(" << x_1 << ", " << y_1 << ") & (" << x_2 << ", " << y_2 << ")" << endl;

	return 0;
}


