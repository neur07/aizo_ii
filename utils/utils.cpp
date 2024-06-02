#include "utils.h"

void printsep(const char* s) {
    printf("\n%s\n", s);
}

int choice_input(string prompt) {
    int option;
    cout << endl << prompt << ": ";
    cin >> option;
    return option;
}

string str_choice_input(string prompt) {
    string option;
    cout << endl << prompt << ": ";
    cin >> option;
    return option;
}

bool between(int x, int a, int b) {
    return x >= a && x <= b;
}
