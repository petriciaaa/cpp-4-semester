
#include <iostream>
using namespace std;

template<typename T>
T max(T arr[],int length) {

	T max = arr[0];
	for (int i = 1; i < length; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}
int main()
{
	int intArr[] = {1, 2, 3, 4, 5 };
	long longArr[] = {11, 22, 33, 44, 55 };
	double doubleArr[] = {111.1, 222.2, 333.3, 444.4, 555.5 };
	char charArr[] = {1, 2, 3, 4, 5 };

	int size = 5;

	cout << "max(intArr)    = " << max(intArr, size) << endl;
	cout << "max(longArr)   = " << max(longArr, size) << endl;
	cout << "max(doubleArr) = " << max(doubleArr, size) << endl;
	cout << "max(charArr)   = " << max(charArr, size) << endl;
}


