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
        for (int j = 0; j < MaxSize; j++) {
            route[i][j] = 65535; // 65535表示两个顶点不邻接
            lines[i][j] = 65535;
            transferTimes[i][j] = 65535;
        }
}

Map::~Map() {

}

void Map::addRoute(int st1, int st2, int dist, int line) {
    route[st1][st2] = dist;
    route[st2][st1] = dist;
    lines[st1][st2] = line;
    lines[st2][st1] = line;
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
    } else if (path[start][end]=="") {
        cout << "两站点不可达" << endl;
    } else {
        cout << path[start][end] << ":约" << dist[start][end] << "米" << endl;
    }

}

void Map::leastTransfer(int start, int end) {
    if (start == end) {
        cout << "起始点一致,无需搭乘地铁" << endl;
//    } else if (LTPath[start][end]=="") {
//        cout << "两站点不可达" << endl;
//    } else {
//        cout << LTPath[start][end] << ":" << transferTimes[start][end] << endl;
    }
}

void Map::Floyd() {
    for (int i = 0; i < stationNum; ++i) { //初始化路线
        for (int j = 0; j < stationNum; ++j) {
            dist[i][j] = route[i][j];
            if (dist[i][j] != 65535) {
                path[i][j] = station[i].name +"->"+ station[j].name;
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
                    path[i][j] = path[i][k].substr(0,path[i][k].size()-station[k].name.size())  + path[k][j];
                    //分割字符串,简单方法去除站点重复问题,非最优方法
                }
            }
        }
    }


}


void Map::LTFloyd() {

    for (int i = 0; i < stationNum; ++i) { //初始化路线
        for (int j = 0; j < stationNum; ++j) {
            if (lines[i][j] != 65535) {
                transferTimes[i][j] = 0;
                LTPath[i][j] = station[i].name +"->"+ station[j].name;
//                cout<<LTPath[i][j]<<lines[i][j]<<" "<<route[i][j]<<endl;
            } else {
                LTPath[i][j] = "";
            }
        }
    }
    for (int k = 0; k < stationNum; ++k) {
        for (int i = 0; i < stationNum; ++i) {
            for (int j = 0; j < stationNum; ++j) {
                if(route[i][k] <65535 && route[k][j] < 65535 && i != j) {
                    if (lines[i][k] != lines[k][j]) {
                        transferTimes[i][j] = 1;
                        LTPath[i][j] = LTPath[i][k].substr(0,LTPath[i][k].size()-station[k].name.size()) + LTPath[k][j];
                        cout << "从" << LTPath[i][k] << "到" << LTPath[k][j] << "需要换乘" << transferTimes[i][j] << endl;
                        transferTimes[i][k] = transferTimes[k][j] = 65535;
                    }else{
                        transferTimes[i][j] = 0;
                        transferTimes[i][k] = transferTimes[k][j] = 65535;
                    }
                    lines[i][j] = lines[k][j];
                }
            }
        }
    }
//
//    for (int k = 0; k < stationNum; ++k) {
//        for (int i = 0; i < stationNum; ++i) {
//            for (int j = 0; j < stationNum; ++j) {
//                if ((transferTimes[i][k] + transferTimes[k][j]) < transferTimes[i][j] && i != j) {
//                    transferTimes[i][j] = transferTimes[i][k] + transferTimes[k][j];
////                    if(lines[i][k] == lines[k][j] ){
////                        transferTimes[i][j] = transferTimes[i][k] + transferTimes[k][j];
////                        lines[i][j] = lines[k][j];
////                    }else{
////                        transferTimes[i][j] = transferTimes[i][k] + transferTimes[k][j] + 1;
////
////                    }
////                    cout<<LTPath[i][k]<<"("<<transferTimes[i][k]<<" "<<lines[i][k]<<")到"<<LTPath[k][j]<<"("<<transferTimes[k][j]<<" "<<lines[k][j]<<")"<<endl;
//                    LTPath[i][j] = LTPath[i][k].substr(0,LTPath[i][k].size()-station[k].name.size()) + LTPath[k][j];
//
////                    cout<<LTPath[i][j]<<"("<<transferTimes[i][j]<<" "<<lines[i][j]<<")"<<endl;
//                    //分割字符串,简单方法去除站点重复问题,非最优方法
//
//                }
//            }
//        }
//    }
//

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
