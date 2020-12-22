#include <iostream>
#include "Map.h"
#include "LoadData.h"
#include <fstream>

int main() {
    Map map;
    LoadData ld(&map, "data\\station.txt", "data\\route.txt");
//    cout<<map.getRouteNum();
//    std::cout<<1<<std::endl;
    map.Floyd();
    map.LTFloyd();
    map.LSFloyd();
    map.STFloyd(60*1000/60/60 , 300, 60);
//    for (int i = 0; i < map.getStationNum(); ++i) {
//        for (int j = 0; j < map.getStationNum(); ++j) {
//            map.shortestRoute(i,j);
//        }
//    }
    cout << "欢迎使用广州地铁路线查询系统！" << endl << endl;
    cout << "温馨提醒：请将窗口最大化已获得良好体验，感谢！" << endl << endl;


    string flag = "-1";
    while (flag != "0") {
        cout << "1.查询路线 2.查看地图 0.退出" << endl;
        cin >> flag;
        if (flag == "1") {
            string start, end;
            int startNum, endNum;
            cout << "请输入起点:";
            cin >> start;
            cout << "请输入终点:";
            cin >> end;
            startNum = map.search(start);
            endNum = map.search(end);
            if(startNum == -1){
                cout<<"未找到站点:"<< start <<endl;
                continue;
            }
            if(endNum == -1){
                cout<<"未找到站点:"<< end <<endl;
                continue;
            }
            cout << endl << "查询结果如下：" << endl << endl;
            cout << "最短路径：" << endl;
            map.shortestRoute(startNum, endNum);
            cout << endl;
            cout << "最少换乘：" << endl;
            map.leastTransfer(startNum, endNum);
            cout << endl;
            cout << "最少站数：" << endl;
            map.leastStation(startNum, endNum);
            cout << endl;
            cout << "最短时间：" << endl;
            map.shortestTime(startNum, endNum);
            cout << endl;
        } else if (flag == "2") {
            ifstream infile;
            infile.open("data\\map.txt");
            string temp;
            while (getline(infile, temp)) {
                cout << temp << endl;
            }
        }else{
            cout<<"非法输入:"<<flag<<endl;
        }
    }
    cout << "感谢使用,下次再会！";
    return 0;
}
