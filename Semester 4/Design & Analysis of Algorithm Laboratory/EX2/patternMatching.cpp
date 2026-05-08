#include<iostream>
using namespace std;

int main()
{
	string t, p;

	cout << "Enter Text : ";
	cin >> t;

	cout << "Enter Pattern : ";
	cin >> p;

	int n = t.length();
	int m = p.length();

	bool found = false;

	int j = 0;

	for(int i = 0; i < n - m + 1; i++)
	{
		for(j = 0; j < m; j++)
		{
			if(t[i+j] != p[j])
			{
				break;
			}
		}

		if(j == m)
		{
			cout << "Pattern matched Index : " << i << endl;
			found = true;
		}
	}

	if(!found)
	{
		cout << "Pattern Not Matched" << endl;
	}

	return 0;
}
