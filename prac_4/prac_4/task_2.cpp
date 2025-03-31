#include <iostream>
#include <list>

using namespace std;

int main()
{

    list<int> numList = { 10, 20, 30, 40, 50 };

    list<int>::iterator it = numList.end();

    while (it != numList.begin()) {
        it--;
        cout << *it << ' ';
    }

    return 0;
}