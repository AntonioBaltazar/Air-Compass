#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "handle_terminal.h"
#include "gamewindow.h"
#include "database.h"
#include "graph.h"

using namespace std;

int terminal_menu()
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

void terminal_mode()
{
    clear_screen();
    int choice = 0;
    bool end = false;

    std::ifstream t("rsc/ascii/terminal-menu.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();                 // close file handle
    
    cout << buffer.str();
 
    cout << "1) Selection d'aéroports" << endl;
    cout << "2) Selection d'un avion" << endl;
    cout << "3) Retour\n-> ";
    cin>> choice;
 
    while (!end){  
        switch(choice){      
        case 1: 
            airport_choice();
            end = true;
        break;

        case 2: 
        
        end = true;
        break;

        case 3: 
        end = true;
        break;

        default :
            cout << "Erreur : Choix invalide, merci de reessayer :\n-> ";
            cin >> choice;
        break;
        }
    }
}

void airport_choice()
{
    Database dtb(true);
    int choice = 0;
    int departure = 0;
    int i = 1;
    bool continu = true;

    do {
        cout << "Veuillez saisir l'aeroport de départ parmis les aeroports suivant :\n";
        for(auto& el:dtb.get_airports()){
            cout << i << ") "<< el.get_name() << "\n";
            i++;
        }
        cout << "-> ";
        cin >> choice;
        cout << "\n\n";
        if(choice<1 || choice > (dtb.get_airports().size()-1)){
            continu = false;
            i = 1;
        }
    } while (!continu);
    
    departure = choice;
    i=1;

    do {
        cout << "Veuillez choisir l'aeroport d'arrive parmis les aeroports suivant : \n";
        for(auto& el:dtb.get_airports()){
            if (!( i == departure )){ // We can't display the departure airport
                cout << i << ") "<< el.get_name() << "\n";
                i++;
            } 
        }
        cout << "-> ";
        cin >> choice;
        cout << "\n\n";
        if(choice<1 || choice > (dtb.get_airports().size()-1)){ //Choice's shielding
            continu = false;
            i = 1;
        }
    } while(!continu);
}

void clear_screen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system ("clear");
#endif
}