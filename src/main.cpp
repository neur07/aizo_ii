#include "menus.h" // #include <iostream> <fstream> <sstream> "utils.h" "UndirectedIMGraph.h"
#include "utils.h"

using namespace std;

int main() {
    printf("\nII Projekt AIZO. Kamil Sobierajski 2024.\n");
    int menu_choice = 0;
    while(menu_choice != 4){
        problem_selection();
        menu_choice = choice_input();

        if(menu_choice == 1) MST_MENU();
        else if(menu_choice == 2) SP_MENU();
        else if(menu_choice == 3) MF_MENU();
        else if(menu_choice == 4) printsep("Zamykanie programu...");
        else printsep("Wybrano nieprawidłową opcję. Sprobuj ponownie.");
    }
    return 0;
}
