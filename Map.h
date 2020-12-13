//
// Created by 17737 on 2020/12/12.
//

#ifndef METROROUTEPLANNINGSYSTEM_MAP_H
#define METROROUTEPLANNINGSYSTEM_MAP_H

#include<string>
#include <iostream>

using namespace std;

const int MaxSize = 100;
struct Line{ //存放当前站点位于几号线
    int id;
    Line* next;
};
struct Station{ //存放站点信息
    string name;
    Line line;
};
class Map {
public:
    Map();

    virtual ~Map();
    void Floyd();
    void shortestRoute(int start, int end);
    void shortestTime(int start, int end);
    void leastTransfer(int start, int end);
    void leastStation(int start, int end);
    int getStationNum() const;
    int getRouteNum() const;
    void addRoute(int st1, int st2, int dist);
    void addStation(string name,int id[],int lineNum);
    void printStation();
private:

    Station station[MaxSize];          //存放路线图中站点的数组
    int route[MaxSize][MaxSize];          //存放路线图中路线距离的数组
    int stationNum, routeNum;             //路线图的站点数和路线数
    int dist[MaxSize][MaxSize];
    string path[MaxSize][MaxSize];
};


#endif //METROROUTEPLANNINGSYSTEM_MAP_H
