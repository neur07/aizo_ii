#include "menus.h" // #include <iostream> <fstream> <sstream> "utils.h" "UndirectedIMGraph.h"

using namespace std;

int main() {
    cout << endl;
    cout << "II Projekt AIZO. Kamil Sobierajski 2024." << endl;
    int menu_choice = 0;
    while(menu_choice != 4){
        problem_selection();
        menu_choice = choice_input();

        if(menu_choice == 1) MST_MENU();
        // else if(menu_choice == 2) SP_MENU();
        // else if(menu_choice == 3) MF_MENU();
        else if(menu_choice == 4) cout << endl << "Zamykanie programu..." << endl;
        else cout << endl << "Wybrano nieprawidłową opcję. Sprobuj ponownie." << endl;
    }
    return 0;
}
