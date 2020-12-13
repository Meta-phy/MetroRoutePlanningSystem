#include <iostream>
#include "Map.h"
#include "LoadData.h"


int main() {
    Map map;
    LoadData ld(&map,"station.txt","route.txt");
//    map.printStation();
    map.Floyd();
    for (int i = 0; i < map.getStationNum(); ++i) {
        for (int j = 0; j < map.getStationNum(); ++j) {
            map.shortestRoute(i,j);
        }
    }

    return 0;
}
