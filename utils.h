#include <iostream>

using namespace std;

int choice_input() {
    int option;
    cout << endl << "Wybor: ";
    cin >> option;
    return option;
}

bool between(int x, int a, int b){
    return x >= a && x <= b;
}