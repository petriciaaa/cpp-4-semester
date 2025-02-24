
#include <iostream>
#include "queue2.h"
#include "distance1.h"
#include <windows.h>


using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    
    Queue<float> floatQueue;
    Queue<const char*> stringQueue;
    Queue<Distance> distanceQueue;

    try
    {
        floatQueue.put(11.11);
        floatQueue.put(22.22);

    }
    catch (const std::exception& e){
        cout << e.what() << endl;
    }
    
    try
    {

        stringQueue.put("some string");
        stringQueue.put("another string");

    }
    catch (const std::exception& e){
        cout << e.what() << endl;

    }
    
    try
    {
        Distance d1(100, 11.1), d2(200, 22.2);

        distanceQueue.put(d1);
        distanceQueue.put(d2);


        cout << "Достанем 5 элементов:" << endl;
        distanceQueue.get();
        distanceQueue.get();
        distanceQueue.get();
        distanceQueue.get();
        distanceQueue.get();


    }
    catch (const std::exception& e) {
        cout << e.what() << endl;
    }
   
    try
    {
        for (int i = 1; i < 10; i++) {
            floatQueue.put(i);
        }

    }
    catch (const std::exception& e ){
        cout << e.what() << endl;

    } 
    
    try
    {
        for (int i = 0; i < 15; i++) {
            float value = floatQueue.get();

        }
    }
    catch (const std::exception& e){
        cout << e.what() << endl;
    }

    return 0;
}


