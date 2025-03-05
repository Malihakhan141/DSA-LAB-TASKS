#include <iostream>
using namespace std;

int getMaxElement(int arr[], int size) {
    int highest = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > highest) {
            highest = arr[i];
        }
    }
    return highest;
}

int main() {
    int size;
    cout << "Enter the number of elements in the array: ";
    cin >> size;

    int* array = new int[size];

    cout << "Provide " << size << " values: " << endl;
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }

    int maxElement = getMaxElement(array, size);
    cout << "The largest element in the array is: " << maxElement << endl;

    delete[] array;
    return 0;
}

