
#include <iostream>
#include "queue1.h"
#include "distance1.h"
#include <windows.h>


using namespace std;

int main()
{
    SetConsoleOutputCP(1251);

    Queue<float> floatQueue;

    floatQueue.put(11.11);
    floatQueue.put(22.22);
    

    Queue<const char*> stringQueue;

    stringQueue.put("some string");
    stringQueue.put("another string");

 


    Queue<Distance> distanceQueue;

    Distance d1(100,11.1), d2(200, 22.2);

    distanceQueue.put(d1);
    distanceQueue.put(d2);



    for (int i = 1; i < 10; i++) {
        floatQueue.put(i);
    }


    for (int i = 0; i < 15; i++) {
        float value = floatQueue.get();
       
    }

    return 0;
}


