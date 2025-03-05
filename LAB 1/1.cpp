#include <iostream>
using namespace std;

int main() {
    int num = 25;  
    int* ptr = &num;  
    
    cout << "Initial State:" << endl;
    cout << "Number: " << num << endl;
    cout << "Memory Address: " << ptr << endl;
    cout << "Pointer Value: " << *ptr << endl;

    *ptr = 75;  

    cout << "\nAfter Modification:" << endl;
    cout << "Updated Number: " << num << endl;
    cout << "Memory Address (unchanged): " << ptr << endl;
    cout << "Pointer New Value: " << *ptr << endl;

    return 0;
}

