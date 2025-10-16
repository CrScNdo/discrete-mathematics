#include "mtd.h"
#include <iostream>
using namespace std;

int main()
{
    Plenty p;
    int choice;

    do {
        cout << "Menu" << endl;
        cout << "Fill first array [1]" << endl;
        cout << "Fill second array [2]" << endl;
        cout << "Fill third array [3]" << endl;
        cout << "Print first array [4]" << endl;
        cout << "Print second array [5]" << endl;
        cout << "Print third array [6]" << endl;
        cout << "Print all array [7]" << endl;
        cout << "Operations with arrays [8]" << endl;
        cout << "Execute advanced expression (e.g. (A∪B)∩¬C) [9]" << endl;
        cout << "Quit [10]" << endl;
        cin >> choice;

        switch(choice) {
            case 1:
                p.fillFirst(); break;
            case 2:
                p.fillSecond(); break;
            case 3:
                p.fillThird(); break;
            case 4:
                p.printFirst(); break;
            case 5:
                p.printSecond(); break;
            case 6:
                p.printThird(); break;
            case 7:
                p.printAll(); break;
            case 8:
                p.arrayOperations(); break;
            case 9:
                p.executeFunctionAdvanced(); break;
            case 10:
                cout << "Exiting...\n"; break;
            default:
                cout << "Unknown option!\n"; break;
        }
    }
    while(choice != 10);
    
    return 0;
}
