#include <iostream>

using namespace std;

int choice_input(string prompt = "Wybor") {
    int option;
    cout << endl << prompt << ": ";
    cin >> option;
    return option;
}

string str_choice_input(string prompt = "Wybor") {
    string option;
    cout << endl << prompt << ": ";
    cin >> option;
    return option;
}

bool between(int x, int a, int b){
    return x >= a && x <= b;
}

// [Niedostępna] funkcja logująca kolejne operacje
// auto log(int id, int ops, string name){
//     cout << endl << "[" << id << "/" << ops << "] " << name;
//     return chrono::high_resolution_clock::now();
// }
