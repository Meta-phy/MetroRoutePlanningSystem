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
    void LTFloyd();
    void LSFloyd();
    void STFloyd(int velocity,int transferTime, int stoppingTime);
    void shortestRoute(int start, int end);
    void shortestTime(int start, int end);
    void leastTransfer(int start, int end);
    void leastStation(int start, int end);
    int getStationNum() const;
    int getRouteNum() const;
    void addRoute(int st1, int st2, int dist, int line);
    void addStation(string name,int id[],int lineNum);
    int search(string str);
    void printStation();
private:
    Station station[MaxSize];//存放路线图中站点的数组
    int route[MaxSize][MaxSize];//存放路线图中路线距离的数组
    int lines[MaxSize][MaxSize];
    int stationNum, routeNum;//路线图的站点数和路线数
    int dist[MaxSize][MaxSize];
    int STDist[MaxSize][MaxSize];
    int transferTimes[MaxSize][MaxSize];
    int STTransferTimes[MaxSize][MaxSize];
    int passStations[MaxSize][MaxSize];
    int time[MaxSize][MaxSize];
    bool tr[MaxSize];//储存该站点是否为换乘点
    string path[MaxSize][MaxSize];
    string LTPath[MaxSize][MaxSize];
    string LSPath[MaxSize][MaxSize];
    string STPath[MaxSize][MaxSize];
};


#endif //METROROUTEPLANNINGSYSTEM_MAP_H
