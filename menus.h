#include "utils.h" // #include <iostream>
#include "UndirectedIMGraph.h" // #include <iostream> <fstream> <sstream>
#include "UndirectedALGraph.h" // #include <iostream> <fstream> <sstream>
#include <chrono>

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
    UndirectedALGraph ALGraph;
    
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
            // Z pliku o wybranej nazwie

            string name = str_choice_input("Nazwa pliku");
            IMGraph.loadFromFile(name + ".txt");
            ALGraph.loadFromFile(name + ".txt");

            // Losowe o podanych parametrach [Niedostępne]
        }
        else if(mst_choice == 2){
            // Wyswietlenie obu reprezentacji
            IMGraph.printGraph();
            ALGraph.printGraph();
        }
        else if(mst_choice == 3){
            // Wykonanie porownawcze
            auto im_start = chrono::high_resolution_clock::now();
            IMGraph.primMST();
            auto im_stop = chrono::high_resolution_clock::now();
            cout << endl << "Prim dla Macierzy Incydencji zajął " << chrono::duration_cast<chrono::microseconds>(im_stop - im_start).count() << " ms" << endl;
        }
        else if(mst_choice == 4){
            // Wykonanie porownawcze
            auto im_start = chrono::high_resolution_clock::now();
            IMGraph.kruskalMST();
            auto im_stop = chrono::high_resolution_clock::now();
            cout << endl << "Kruskal dla Macierzy Incydencji zajął " << chrono::duration_cast<chrono::microseconds>(im_stop - im_start).count() << " ms";
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
