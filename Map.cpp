//
// Created by 17737 on 2020/12/12.
//

#include "Map.h"
#include <iostream>

#define nullptr NULL
using namespace std;

Map::Map() {
    stationNum = 0;
    routeNum = 0;
    for (int i = 0; i < MaxSize; i++) {
        for (int j = 0; j < MaxSize; j++) {
            route[i][j] = 65535; // 65535��ʾ�������㲻�ڽ�
            lines[i][j] = 65535;
            transferTimes[i][j] = 65535;
            passStations[i][j] = 65535;
            time[i][j] = 65535;
            STDist[i][j] = 65535;
            STTransferTimes[i][j] = 65535;
        }
        tr[i] = false;
    }
}

Map::~Map() {

}

int Map::search(string str) {
    int index = -1;
    for (int i = 0; i < stationNum; i++) {
        if (station[i].name == str)
            index = i;
    }
    return index;

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
        cout << "��ʼ��һ��,�����˵���" << endl;
    } else if (path[start][end] == "") {
        cout << "��վ�㲻�ɴ�" << endl;
    } else {
        cout << path[start][end] << ":Լ" << dist[start][end] << "��" << endl;
    }

}

void Map::leastTransfer(int start, int end) {
    if (start == end) {
        cout << "��ʼ��һ��,�����˵���" << endl;
    } else if (LTPath[start][end] == "") {
        cout << "��վ�㲻�ɴ�" << endl;
    } else {
        cout << LTPath[start][end] << ":�軻��" << transferTimes[start][end] << "��" << endl;
    }
}

void Map::leastStation(int start, int end) {
    if (start == end) {
        cout << "��ʼ��һ��,�����˵���" << endl;
    } else if (LSPath[start][end] == "") {
        cout << "��վ�㲻�ɴ�" << endl;
    } else {
        cout << LSPath[start][end] << ":�辭��" << passStations[start][end] << "վ" << endl;
    }
}

void Map::shortestTime(int start, int end) {
    if (start == end) {
        cout << "��ʼ��һ��,�����˵���" << endl;
    } else if (STPath[start][end] == "") {
        cout << "��վ�㲻�ɴ�" << endl;
    } else {
        cout << STPath[start][end] << ":Լ" << time[start][end]/60 << "����" << endl;
    }
}

void Map::Floyd() {
    for (int i = 0; i < stationNum; ++i) { //��ʼ��·��
        for (int j = 0; j < stationNum; ++j) {
            dist[i][j] = route[i][j];
            if (dist[i][j] != 65535) {
                path[i][j] = station[i].name + "->" + station[j].name;
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
                    path[i][j] = path[i][k].substr(0, path[i][k].size() - station[k].name.size()) + path[k][j];
                    //�ָ��ַ���,�򵥷���ȥ��վ���ظ�����,�����ŷ���
                }
            }
        }
    }


}


void Map::LTFloyd() {
    for (int i = 0; i < stationNum; ++i) { //��ʼ��·��
        for (int j = 0; j < stationNum; ++j) {
            if (lines[i][j] != 65535) {
                transferTimes[i][j] = 0;
                LTPath[i][j] = station[i].name + "->" + station[j].name;
//                cout<<LTPath[i][j]<<lines[i][j]<<" "<<route[i][j]<<endl;
            } else {
                LTPath[i][j] = "";
            }
        }
    }
    for (int k = 0; k < stationNum; ++k) {
        for (int i = 0; i < stationNum; ++i) {
            for (int j = 0; j < stationNum; ++j) {
                if (route[i][k] < 65535 && route[k][j] < 65535 && i != j) {
                    if (lines[i][k] != lines[k][j]) {
                        if (!tr[k]) {
                            tr[k] = true;
//                    		cout<<station[k].name<<"�ǻ���վ"<<endl;
                        }
                        transferTimes[i][j] = 1;
                        LTPath[i][j] =
                                LTPath[i][k].substr(0, LTPath[i][k].size() - station[k].name.size()) + LTPath[k][j];
                    } else {
                        LTPath[i][j] =
                                LTPath[i][k].substr(0, LTPath[i][k].size() - station[k].name.size()) + LTPath[k][j];
                        transferTimes[i][j] = 0;
                    }
                    lines[i][j] = lines[k][j];
                }
            }
        }
    }

    for (int k = 0; k < stationNum; ++k) {
        for (int i = 0; i < stationNum; ++i) {
            for (int j = 0; j < stationNum; ++j) {
                if ((transferTimes[i][k] + transferTimes[k][j]) < transferTimes[i][j] && i != j) {
//                    transferTimes[i][j] = transferTimes[i][k] + transferTimes[k][j];
                    if (lines[i][k] != lines[k][j] && tr[k]) {
                        transferTimes[i][j] = transferTimes[i][k] + transferTimes[k][j] + 1;
                        LTPath[i][j] = LTPath[i][k] + "(��վ����)" +
                                       LTPath[k][j].substr(station[k].name.size(), LTPath[k][j].size());
//						cout<<LTPath[i][k]<<"("<<transferTimes[i][k]<<" "<<lines[i][k]<<")��"<<LTPath[k][j]<<"("<<transferTimes[k][j]<<" "<<lines[k][j]<<")"<<endl;
//						cout<<"���˴���"<<transferTimes[i][j];
                    } else if (!tr[k]) {
                        transferTimes[i][j] = transferTimes[i][k] + transferTimes[k][j];
                        lines[i][j] = lines[k][j];
                        LTPath[i][j] =
                                LTPath[i][k].substr(0, LTPath[i][k].size() - station[k].name.size()) + LTPath[k][j];
                    } else {
                        transferTimes[i][j] = transferTimes[i][k] + transferTimes[k][j];
                        lines[i][j] = lines[k][j];
                        LTPath[i][j] =
                                LTPath[i][k].substr(0, LTPath[i][k].size() - station[k].name.size()) + LTPath[k][j];
                    }
                }
            }
        }
    }


}

void Map::LSFloyd() {
    for (int i = 0; i < stationNum; ++i) { //��ʼ��·��
        for (int j = 0; j < stationNum; ++j) {
            if (route[i][j] != 65535) {
                LSPath[i][j] = station[i].name + "->" + station[j].name;
                passStations[i][j] = 1;
            } else {
                LSPath[i][j] = "";
            }
        }
    }

    for (int k = 0; k < stationNum; ++k) {
        for (int i = 0; i < stationNum; ++i) {
            for (int j = 0; j < stationNum; ++j) {
                if ((passStations[i][k] + passStations[k][j]) < passStations[i][j]) {
                    passStations[i][j] = passStations[i][k] + passStations[k][j];
                    LSPath[i][j] = LSPath[i][k].substr(0, LSPath[i][k].size() - station[k].name.size()) + LSPath[k][j];
                    //�ָ��ַ���,�򵥷���ȥ��վ���ظ�����,�����ŷ���
                }
            }
        }
    }

}

void Map::STFloyd(int velocity, int transferTime, int stoppingTime) {
    for (int i = 0; i < stationNum; ++i) { //��ʼ��·��
        for (int j = 0; j < stationNum; ++j) {
            if (route[i][j] != 65535) {
                STTransferTimes[i][j] = 0;
                STPath[i][j] = station[i].name +"->"+ station[j].name;
                STDist[i][j] = route[i][j];
                time[i][j] = STDist[i][j] / velocity + stoppingTime;
//                cout<<LTPath[i][j]<<lines[i][j]<<" "<<route[i][j]<<endl;
            } else {
                STPath[i][j] = "";
            }
        }
    }
    for (int k = 0; k < stationNum; ++k) {
        for (int i = 0; i < stationNum; ++i) {
            for (int j = 0; j < stationNum; ++j) {
                if(route[i][k] <65535 && route[k][j] < 65535 && i != j) {  //����վ��
                    if (lines[i][k] != lines[k][j]) {
                        if(!tr[k]){
                            tr[k] = true;
                        }
                        STTransferTimes[i][j] = 1;
                        time[i][j] = (STTransferTimes[i][j] * transferTime + (STDist[i][k] + STDist[k][j]) / velocity + stoppingTime*2);
                        STPath[i][j] = STPath[i][k] + "(��վ����)" +
                                       STPath[k][j].substr(station[k].name.size(), STPath[k][j].size());
                    }else{
                        STTransferTimes[i][j] = 0;
                        time[i][j] = (STTransferTimes[i][j] * transferTime + (STDist[i][k] + STDist[k][j]) / velocity + stoppingTime*2);
                        STPath[i][j] = STPath[i][k].substr(0,STPath[i][k].size()-station[k].name.size()) + STPath[k][j];
                    }
                    STDist[i][j] = STDist[i][k]+STDist[k][j];
                    lines[i][j] = lines[k][j];
                }
            }
        }
    }

    for (int k = 0; k < stationNum; ++k) {
        for (int i = 0; i < stationNum; ++i) {
            for (int j = 0; j < stationNum; ++j) {
//                cout<<(STDist[i][k] + STDist[k][j])/velocity<<endl;
                if ((time[i][k]+time[k][j]) < time[i][j] && i != j ) {
//                    cout<<STPath[i][k]<<"("<<time[i][k]<<")��"<<STPath[k][j]<<"("<<time[k][j]<<")"<<endl;
                    if (lines[i][k] != lines[k][j] && tr[k] ) {
                        STTransferTimes[i][j] = STTransferTimes[i][k] + STTransferTimes[k][j] + 1;
                        STDist[i][j] = STDist[i][k] + STDist[k][j];
                        time[i][j] = time[i][k] + time[k][j] + transferTime;
                        STPath[i][j] = STPath[i][k] + "(��վ����)" +
                                STPath[k][j].substr(station[k].name.size(), STPath[k][j].size());
//						cout<<LTPath[i][k]<<"("<<transferTimes[i][k]<<" "<<lines[i][k]<<")��"<<LTPath[k][j]<<"("<<transferTimes[k][j]<<" "<<lines[k][j]<<")"<<endl;
//						cout<<"���˴���"<<transferTimes[i][j];
                        cout<<"��ս����";
                    } else if (!tr[k]) {
                        STTransferTimes[i][j] = STTransferTimes[i][k] + STTransferTimes[k][j];
                        STDist[i][j] = STDist[i][k] + STDist[k][j];
                        time[i][j] = time[i][k] + time[k][j];
                        lines[i][j] = lines[k][j];
                        STPath[i][j] =
                                STPath[i][k].substr(0, STPath[i][k].size() - station[k].name.size()) + STPath[k][j];
                    } else {
                        STTransferTimes[i][j] = STTransferTimes[i][k] + STTransferTimes[k][j];
                        STDist[i][j] = STDist[i][k] + STDist[k][j];
                        time[i][j] = time[i][k] + time[k][j];
                        lines[i][j] = lines[k][j];
                        STPath[i][j] =
                                STPath[i][k].substr(0, STPath[i][k].size() - station[k].name.size()) + STPath[k][j];
                    }

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
        cout << station[i].name << " " << station[i].line.id;
        Line line = station[i].line;
        while (line.next != nullptr) {
            line = *line.next;
            cout << " " << line.id;
        }
        cout << endl;
    }
}
