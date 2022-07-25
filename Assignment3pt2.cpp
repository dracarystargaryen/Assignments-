#include <iostream>

using namespace std;

int main() {
    int input;
    int n;
    cout << "Please enter a number: ";
    cin >> input;

    for (int i = 1; i <= n; ++i){
        if (n % i == 0)
            cout << i << " ";
    }
    return 0;
}