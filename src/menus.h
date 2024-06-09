#pragma once
#include "IMGraph.h" // #include <iostream> <fstream> <sstream>
#include "ALGraph.h"
#include <chrono>
#include "MST.h"
#include "SP.h"

using namespace std;

void problem_selection(){

    printsep("Problem:");
    cout << endl;
    cout << "1) Minimum Spanning Tree (MST)" << endl;
    cout << "2) Shortest Path (SP)" << endl;
    cout << "3) Maximum Flow (MF)" << endl;
    cout << "4) Wyjście z programu" << endl;
}

void MST_MENU(){
    // Inicjalizacja obu reprezentacji grafow
    int mst_choice = 0;
    IMGraph im_graph;
    ALGraph al_graph;
    
    while(mst_choice != 6){
        printsep("Problem > MST:");
        cout << endl;
        cout << "1) Nowy graf" << endl;
        cout << "2) Wyświetl graf" << endl;
        cout << "3) Algorytm Prima" << endl;
        cout << "4) Algorytm Kruskala" << endl;
        cout << "5) Pełne badanie" << endl;
        cout << "6) Powrot do menu glownego" << endl;
        mst_choice = choice_input();

        if(mst_choice == 1){
            printsep("Problem > MST > Nowy graf:");
            cout << endl;
            cout << "1) Wczytaj z pliku" << endl;
            cout << "2) Wygeneruj losowy graf" << endl;
            int graph_src = choice_input();
            
            if(graph_src == 1) { 
                // Z pliku o wybranej nazwie
                printsep("Problem > MST > Nowy graf > Plik:");
                string name = str_choice_input("Nazwa pliku");
                im_graph.load_from_file("inputs/" + name + ".txt");
                al_graph.load_from_file("inputs/" + name + ".txt");
            }
            else{
                // Losowe o podanych parametrach
                printsep("Problem > MST > Nowy graf > Losowy:");
                int vertices = choice_input("Podaj liczbę wierzchołków");
                int edges = choice_input("Podaj liczbę krawędzi");
                im_graph.generate_random_graph(vertices, edges);
                al_graph.generate_random_graph(vertices, edges);
            }
            
        }
        else if(mst_choice == 2){
            // Wyswietlenie obu reprezentacji
            im_graph.print_graph();
            al_graph.print_graph();
        }
        else if(mst_choice == 3){
            printsep("Problem > MST > Prim:");
            // Wykonanie porownawcze
            auto im_start = chrono::high_resolution_clock::now();
            MST::prim(im_graph);
            auto im_stop = chrono::high_resolution_clock::now();
            cout << endl << "Prim dla Macierzy Incydencji zajął " << chrono::duration_cast<chrono::microseconds>(im_stop - im_start).count() << " ms" << endl;

            auto al_start = chrono::high_resolution_clock::now();
            MST::prim(al_graph);
            auto al_stop = chrono::high_resolution_clock::now();
            cout << endl << "Prim dla Listy Sąsiedztwa zajął " << chrono::duration_cast<chrono::microseconds>(al_stop - al_start).count() << " ms" << endl;
        }
        else if(mst_choice == 4){
            printsep("Problem > MST > Kruskal:");
            // Wykonanie porownawcze
            auto im_start = chrono::high_resolution_clock::now();
            MST::kruskal(im_graph);
            auto im_stop = chrono::high_resolution_clock::now();
            cout << endl << "Kruskal dla Macierzy Incydencji zajął " << chrono::duration_cast<chrono::microseconds>(im_stop - im_start).count() << " ms";
            
            auto al_start = chrono::high_resolution_clock::now();
            MST::kruskal(al_graph);
            auto al_stop = chrono::high_resolution_clock::now();
            cout << endl << "Kruskal dla Listy Sąsiedztwa zajął " << chrono::duration_cast<chrono::microseconds>(al_stop - al_start).count() << " ms" << endl;
        
        }
        else if(mst_choice == 5){
            // Rozne stopnie wypelnienia

            // 
        }
        else if(mst_choice == 6) break;
        else cout << endl << "Wybrano nieprawidłową opcję. Sprobuj ponownie." << endl;
    }
}

void SP_MENU() {
    int sp_choice = 0;
    IMGraph im_graph(true);
    ALGraph al_graph(true);

    while (sp_choice != 6) {
        printsep("Problem > Shortest Path:");
        cout << endl;
        cout << "1) Nowy graf" << endl;
        cout << "2) Wyświetl graf" << endl;
        cout << "3) Algorytm Dijkstry" << endl;
        cout << "4) Algorytm Forda-Bellmana" << endl;
        cout << "5) Pełne badanie" << endl;
        cout << "6) Powrót do menu głównego" << endl;
        sp_choice = choice_input();

        if(sp_choice == 1){
            printsep("Problem > Shortest Path > Nowy graf:");
            cout << endl;
            cout << "1) Wczytaj z pliku" << endl;
            cout << "2) Wygeneruj losowy graf" << endl;
            int graph_src = choice_input();
            
            if(graph_src == 1) { 
                // Z pliku o wybranej nazwie
                printsep("Problem > Shortest Path > Nowy graf > Plik:");
                string name = str_choice_input("Nazwa pliku");
                im_graph.load_from_file("inputs/" + name + ".txt");
                al_graph.load_from_file("inputs/" + name + ".txt");
            }
            else{
                // Losowe o podanych parametrach
                printsep("Problem > Shortest Path > Nowy graf > Losowy:");
                int vertices = choice_input("Podaj liczbę wierzchołków");
                int edges = choice_input("Podaj liczbę krawędzi");
                im_graph.generate_random_graph(vertices, edges);
                al_graph.generate_random_graph(vertices, edges);
            }
            
        }
        else if (sp_choice == 2) {
            im_graph.print_graph();
            al_graph.print_graph();
        }
        else if (sp_choice == 3) {
            printsep("Problem > Shortest Path > Dijkstry:");
            int src = choice_input("Podaj wierzchołek początkowy");
            int dest = choice_input("Podaj wierzchołek docelowy");
            auto im_start = chrono::high_resolution_clock::now();
            SP::dijkstra(im_graph, src);
            auto im_stop = chrono::high_resolution_clock::now();
            cout << endl << "Dijkstra dla Macierzy Incydencji zajął " 
                 << chrono::duration_cast<chrono::microseconds>(im_stop - im_start).count() << " ms" << endl;

            auto al_start = chrono::high_resolution_clock::now();
            SP::dijkstra(al_graph, src);
            auto al_stop = chrono::high_resolution_clock::now();
            cout << endl << "Dijkstra dla Listy Sąsiedztwa zajął " 
                 << chrono::duration_cast<chrono::microseconds>(al_stop - al_start).count() << " ms" << endl;
        }
        else if (sp_choice == 4) {
            printsep("Problem > Shortest Path > Bellman-Ford:");
            int src = choice_input("Podaj wierzchołek początkowy");
            int dest = choice_input("Podaj wierzchołek docelowy");
            auto im_start = chrono::high_resolution_clock::now();
            SP::bellman_ford(im_graph, src);
            auto im_stop = chrono::high_resolution_clock::now();
            cout << endl << "Bellman-Ford dla Macierzy Incydencji zajął " 
                 << chrono::duration_cast<chrono::microseconds>(im_stop - im_start).count() << " ms" << endl;

            auto al_start = chrono::high_resolution_clock::now();
            SP::bellman_ford(al_graph, src);
            auto al_stop = chrono::high_resolution_clock::now();
            cout << endl << "Bellman-Ford dla Listy Sąsiedztwa zajął " 
                 << chrono::duration_cast<chrono::microseconds>(al_stop - al_start).count() << " ms" << endl;
        }
        else if (sp_choice == 6) {
            break;
        }
        else {
            cout << endl << "Wybrano nieprawidłową opcję. Spróbuj ponownie." << endl;
        }
    }
}


void MF_MENU() {
    int sp_choice = 0;
    IMGraph im_graph(true);
    ALGraph al_graph(true);

    while (sp_choice != 5) {
        printsep("Problem > Maximum Flow:");
        cout << endl;
        cout << "1) Nowy graf" << endl;
        cout << "2) Wyświetl graf" << endl;
        cout << "3) Algorytm Forda-Bellmana" << endl;
        cout << "4) Pełne badanie" << endl;
        cout << "5) Powrót do menu głównego" << endl;
        sp_choice = choice_input();

        if(sp_choice == 1){
            printsep("Problem > Maximum Flow > Nowy graf:");
            cout << endl;
            cout << "1) Wczytaj z pliku" << endl;
            cout << "2) Wygeneruj losowy graf" << endl;
            int graph_src = choice_input();
            
            if(graph_src == 1) { 
                // Z pliku o wybranej nazwie
                printsep("Problem > Maximum Flow > Nowy graf > Plik:");
                string name = str_choice_input("Nazwa pliku");
                im_graph.load_from_file("inputs/" + name + ".txt");
                al_graph.load_from_file("inputs/" + name + ".txt");
            }
            else{
                // Losowe o podanych parametrach
                printsep("Problem > Maximum Flow > Nowy graf > Losowy:");
                int vertices = choice_input("Podaj liczbę wierzchołków");
                int edges = choice_input("Podaj liczbę krawędzi");
                im_graph.generate_random_graph(vertices, edges);
                al_graph.generate_random_graph(vertices, edges);
            }
            
        }
        else if (sp_choice == 2) {
            im_graph.print_graph();
            al_graph.print_graph();
        }
        else if (sp_choice == 3) {
            printsep("Problem > Maximum Flow > Ford-Fulkerson:");
            int src = choice_input("Podaj wierzchołek początkowy");
            int dest = choice_input("Podaj wierzchołek docelowy");
            auto im_start = chrono::high_resolution_clock::now();
            // SP::dijkstra(im_graph, src, dest);
            auto im_stop = chrono::high_resolution_clock::now();
            cout << endl << "Dijkstra dla Macierzy Incydencji zajął " 
                 << chrono::duration_cast<chrono::microseconds>(im_stop - im_start).count() << " ms" << endl;

            auto al_start = chrono::high_resolution_clock::now();
            // SP::dijkstra(al_graph, src, dest);
            auto al_stop = chrono::high_resolution_clock::now();
            cout << endl << "Dijkstra dla Listy Sąsiedztwa zajął " 
                 << chrono::duration_cast<chrono::microseconds>(al_stop - al_start).count() << " ms" << endl;
        }
        else if (sp_choice == 4) {
            int src = choice_input("Podaj wierzchołek początkowy");
            int dest = choice_input("Podaj wierzchołek docelowy");
            auto im_start = chrono::high_resolution_clock::now();
            // SP::bellman_ford(im_graph, src, dest);
            auto im_stop = chrono::high_resolution_clock::now();
            cout << endl << "Bellman-Ford dla Macierzy Incydencji zajął " 
                 << chrono::duration_cast<chrono::microseconds>(im_stop - im_start).count() << " ms" << endl;

            auto al_start = chrono::high_resolution_clock::now();
            // SP::bellman_ford(al_graph, src, dest);
            auto al_stop = chrono::high_resolution_clock::now();
            cout << endl << "Bellman-Ford dla Listy Sąsiedztwa zajął " 
                 << chrono::duration_cast<chrono::microseconds>(al_stop - al_start).count() << " ms" << endl;
        }
        else if (sp_choice == 5) {
            break;
        }
        else {
            cout << endl << "Wybrano nieprawidłową opcję. Spróbuj ponownie." << endl;
        }
    }
}

