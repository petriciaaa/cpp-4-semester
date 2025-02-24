
#include <iostream>

template<typename T>
T max(T arr[],int length) {

	T max = arr[0]
	for (int i = 1; i < length; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
}

int main()
{
    std::cout << "Hello World!\n";
}


