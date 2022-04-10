
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "handle_terminal.h"
#include "gamewindow.h"

using namespace std;

int Terminal::terminal_menu()
{

    int choice = 0;
    bool end = false;

    std::ifstream t("rsc/ascii/terminal-menu.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();                 // close file handle
 
    cout << buffer.str();
 
    do{  
        cout << "1) Lancer le mode graphique" << endl;
        cout << "2) Lancer le mode console" << endl;
        cout << "3) Quiter\n-> ";
        cin>> choice;

        switch(choice){      
            case 1: case 3: 
            end = true;
            break;

            case 2: 
            terminal_mode();
            break;

            default :
            cout << "Erreur : Choix invalide, merci de reessayer :\n";
            break;
        }
        clear_screen();
    }while(!end);

    if(choice == 1){
        GameWindow menu("AirCompass", 1333, 800);
        menu.launch();
    }
    return 0;

}

void Terminal::terminal_mode()
{
    clear_screen();
    int choice = 0;
    bool end = false;

    std::ifstream t("rsc/ascii/terminal-menu.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();                 // close file handle
    
    cout << buffer.str();

    m_dep = airport_choice(NULL, "depart");
    m_end = airport_choice(&m_dep, "");
    m_airplane = airplane_choice();

    Graph g;
    cout << "\n\n\n\n\n-=-=-=-=- Affichage du graph global -=-=-=-=-\n\n";
    g.load_from_file("graph.txt");
    g.display_graph();
    Graph g2 = g;
    
    g2.limitEdge(m_airplane.get_autonomy());
    cout << "\n\n\n\n\n-=-=-=-=- Affichage du graph pour l'avion -=-=-=-=-\n";
    g2.display_graph();

    cout << "\n\n\n\n\n-=-=-=-=- Coloration anti collision -=-=-=-=-\n\n";
    g2.welsh_powel(m_database.get_airports());

    cout << "\n\n\n\n\n-=-=-=-=- Chemin le plus court pour chaque aeroport d'arrive -=-=-=-=-\n";
    int n = 0;
    for (auto& el : m_database.get_airports()) 
        if (m_dep.get_name() == el.get_name())
            break;
        else 
            n++;
        g2.shortest_path(Vertice(n), m_database.get_airports());
    /* get_graph().load_from_file("graph.txt");
    get_edges() = drawGraph(get_graph()); */
    cout << "\n\n\n\n\n-=-=-=-=- Parcours en BFS -=-=-=-=-\n";
    g2.BFS(Vertice(n));
    cout << "\n\n\n\n\n-=-=-=-=- Parcours en DFS -=-=-=-=-\n";
    g2.DFS();

    cout << "\n\n\n\n\n-=-=-=-=- Arbre couvrant de poids minimal -=-=-=-=-\n";
    g2.primMST(Vertice(n));

    while(1);
}
Airplane Terminal::airplane_choice() {
    int choice, i;
    do {
        i = 1;
        cout << "Veuillez saisir l'avion suivant :\n";
        
        for(auto& el : m_database.get_fleet()){ 
            cout << i << ") "<< el.get_name() << "\n";
            i++;
        }
        cout << "-> ";
        cin >> choice;
        cout << "\n\n";
    } while (!(choice > 0 && choice <=  m_database.get_fleet().size()));

    return  m_database.get_fleet()[choice-1];
}

Airport Terminal::airport_choice(Airport* without, string str) {
    int choice = 0, i =1;
    int n;
    do {
        cout << "Veuillez saisir l'aeroport " << str <<" parmis les aeroports suivant :\n";
        
        for(auto& el : m_database.get_airports()){ 
            if (without != NULL) {
                if (el.get_name() == without->get_name()) {
                    cout << i << ") -------------------\n";
                    n=i;
                } else {
                    cout << i << ") "<< el.get_name() << "\n";
                    i++;
                }
            } else {
                cout << i << ") "<< el.get_name() << "\n";
                i++;

            }
        }
        cout << "-> ";
        cin >> choice;
        cout << "\n\n";
    } while (!(choice > 0 && choice <= m_database.get_airports().size() && choice != n));

    return m_database.get_airports()[choice-1];
}

void Terminal::airport_choice()
{
 
    int choice = 0;
    int departure = 0;
    int i = 1;
    bool continu = true;

    do {
        cout << "Veuillez saisir l'aeroport de départ parmis les aeroports suivant :\n";
        for(auto& el:m_airports){
            cout << i << ") "<< el.get_name() << "\n";
            i++;
        }
        cout << "-> ";
        cin >> choice;
        cout << "\n\n";
        if(choice<1 || choice > (m_airports.size()-1)){
            continu = false;
            i = 1;
        }
    } while (!continu);
    
    departure = choice;
    i=1;

    do {
        cout << "Veuillez choisir l'aeroport d'arrive parmis les aeroports suivant : \n";
        for(auto& el:m_airports){
            if (!( i == departure )){ // We can't display the departure airport
                cout << i << ") "<< el.get_name() << "\n";
                i++;
            } 
        }
        cout << "-> ";
        cin >> choice;
        cout << "\n\n";
        if(choice<1 || choice > (m_airports.size()-1)){ //Choice's shielding
            continu = false;
            i = 1;
        }
    } while(!continu);
}

void Terminal::clear_screen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system ("clear");
#endif
}