#include "utils.h" // #include <iostream>
#include "UndirectedIMGraph.h" // #include <iostream> <fstream> <sstream>
#include "UndirectedALGraph.h" // #include <iostream> <fstream> <sstream>

using namespace std;

void problem_selection(){
    cout << endl;
    cout << "1) Minimum Spanning Tree (MST)" << endl;
    cout << "2) Shortest Path [Niedostępne]" << endl;
    cout << "3) Maximum Flow [Niedostępne]" << endl;
    cout << "4) Wyjście z programu" << endl;
}

void MST_MENU(){
    // Inicjalizacja obu reprezentacji grafow
    int mst_choice = 0;
    UndirectedIMGraph IMGraph;
    IMGraph.loadFromFile("input.txt");
    UndirectedALGraph ALGraph;
    ALGraph.loadFromFile("input.txt");
    
    while(mst_choice != 6){
        cout << endl;
        cout << "1) Nowy graf" << endl;
        cout << "2) Wyświetl graf" << endl;
        cout << "3) Algorytm Prima" << endl;
        cout << "4) Algorytm Kruskala" << endl;
        cout << "5) Pełne badanie" << endl;
        cout << "6) Powrot do menu glownego" << endl;
        mst_choice = choice_input();

        if(mst_choice == 1){
            // Dwa nowe grafy (z pliku bądź losowe o podanych parametrach)
        }
        else if(mst_choice == 2){
            // Wyswietlenie obu reprezentacji
            IMGraph.printIncidenceMatrix();
            ALGraph.printGraph();
        }
        else if(mst_choice == 3){
            // Wykonanie porownawcze
            IMGraph.primMST();
        }
        else if(mst_choice == 4){
            // Wykonanie porownawcze
            IMGraph.kruskalMST();
        }
        else if(mst_choice == 5){
            // Rozne stopnie wypelnienia

            // 
        }
        else if(mst_choice == 6) break;
        else cout << endl << "Wybrano nieprawidłową opcję. Sprobuj ponownie." << endl;
    }
}

void SP_MENU(){

}

void MF_MENU(){

}
