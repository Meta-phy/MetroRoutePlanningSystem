#include <iostream>
#include "Map.h"
#include "LoadData.h"


int main() {
    Map map;
    LoadData ld(&map,"..\\station.txt","..\\route.txt");
//    cout<<map.getRouteNum();
//    std::cout<<1<<std::endl;
    map.Floyd();
    map.LTFloyd();
//    for (int i = 0; i < map.getStationNum(); ++i) {
//        for (int j = 0; j < map.getStationNum(); ++j) {
//            map.shortestRoute(i,j);
//        }
//    }
    while (true){
        int start,end;
        cout<<"请输入起点:";
        cin>>start;
        cout<<"请输入终点:";
        cin>>end;
        map.shortestRoute(start,end);
        map.leastTransfer(start,end);
    }
    return 0;
}
