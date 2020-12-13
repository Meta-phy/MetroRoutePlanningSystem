#include <iostream>
#include "Map.h"
#include "LoadData.h"


int main() {
    Map map;
    LoadData ld(&map,"文件地址","文件地址");
    map.printStation();
    map.Floyd();
    for (int i = 0; i < map.getStationNum(); ++i) {
        for (int j = 0; j < map.getStationNum(); ++j) {
            map.shortestRoute(i,j);
        }
    }

    return 0;
}
