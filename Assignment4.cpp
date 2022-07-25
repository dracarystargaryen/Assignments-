#include <iostream>

using namespace std;

int main(){
    int x, i;
    float array[10];

    //User prompt for an array
    cout << "Enter an array: ";
    cin >> x;
    cout << endl;

    //User prompt to enter numbers
    for (int i = 0; i < x; ++i){
        cout << "Enter your numbers: " << i + 1 << endl;
        cin >> array[i];
    }

    //Loop to find largest number in array
    for (int i = 1; i < x; ++i){
        if (array[0] < array[i])
            array[0] = array[i];
        }
        cout << endl << "Largest number in the array is: " << array[0];
        return 0;
    }

