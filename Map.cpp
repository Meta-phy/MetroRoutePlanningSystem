//
// Created by 17737 on 2020/12/12.
//

#include "Map.h"
#include <iostream>

using namespace std;

Map::Map() {
    stationNum = 0;
    routeNum = 0;
    for (int i = 0; i < MaxSize; i++)
        for (int j = 0; j < MaxSize; j++)
            route[i][j] = 65535; // 65535表示两个顶点不邻接
}

Map::~Map() {

}

void Map::addRoute(int st1, int st2, int dist) {
    route[st1][st2] = dist;
    route[st2][st1] = dist;
    routeNum++;
}

void Map::addStation(string name, int id[], int lineNum) {
    station[stationNum].name = name;
    Line *line = new Line;
    line = nullptr;
    for (int i = 0; i < lineNum; ++i) {
        Line *l = new Line;
        l->id = id[i];
        l->next = line;
        line = l;
    }
    station[stationNum].line = *line;
    stationNum++;
}

void Map::shortestRoute(int start, int end) {
    if (start == end) {
        cout << "起始点一致,无需搭乘地铁" << endl;
    } else if (path[start][end] == "") {
        cout << "两站点不可达" << endl;
    } else {
        cout << path[start][end] << ":" << dist[start][end] << endl;
    }

}

void Map::Floyd() {
    for (int i = 0; i < stationNum; ++i) {
        for (int j = 0; j < stationNum; ++j) {
            dist[i][j] = route[i][j];
            if (dist[i][j] != 65535) {
                path[i][j] = station[i].name + station[j].name;
            } else {
                path[i][j] = "";
            }
        }
    }
    for (int k = 0; k < stationNum; ++k) {
        for (int i = 0; i < stationNum; ++i) {
            for (int j = 0; j < stationNum; ++j) {
                if ((dist[i][k] + dist[k][j]) < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k] + "\b" + path[k][j];
                }
            }
        }
    }


}

int Map::getStationNum() const {
    return stationNum;
}

int Map::getRouteNum() const {
    return routeNum;
}

void Map::printStation() {
    for (int i = 0; i < stationNum; ++i) {
        cout<<station[i].name<< " " <<station[i].line.id;
        Line line = station[i].line;
        while (line.next!= nullptr){
            line = *line.next;
            cout<<" "<<line.id;
        }
        cout<<endl;
    }
}
