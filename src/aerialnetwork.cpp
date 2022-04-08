#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "aerialnetwork.h"
#include "graphreader.h"

using namespace std;

void AerialNetwork::create_fleet()
{
    vector<Airplane> bank;
    vector<Airplane> fleet;
    int nb_planes = 10;
    std::srand(std::time(nullptr));
    bank = read_plane_file();
    /*
    for (int i = 0; i < nb_planes; i++) {
        fleet.push_back(bank[rand()%(6)]);
        fleet[i].set_id(i);
    }*/

    //set_airplane(bank);
    set_fleet(bank);

}
