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
    cout << "��ӭʹ�ù��ݵ���·�߲�ѯϵͳ��" << endl << endl;
    cout << "��ܰ���ѣ��뽫��������ѻ���������飬��л��" << endl << endl;


    string flag = "-1";
    while (flag != "0") {
        cout << "1.��ѯ·�� 2.�鿴��ͼ 0.�˳�" << endl;
        cin >> flag;
        if (flag == "1") {
            string start, end;
            int startNum, endNum;
            cout << "���������:";
            cin >> start;
            cout << "�������յ�:";
            cin >> end;
            startNum = map.search(start);
            endNum = map.search(end);
            if(startNum == -1){
                cout<<"δ�ҵ�վ��:"<< start <<endl;
                continue;
            }
            if(endNum == -1){
                cout<<"δ�ҵ�վ��:"<< end <<endl;
                continue;
            }
            cout << endl << "��ѯ������£�" << endl << endl;
            cout << "���·����" << endl;
            map.shortestRoute(startNum, endNum);
            cout << endl;
            cout << "���ٻ��ˣ�" << endl;
            map.leastTransfer(startNum, endNum);
            cout << endl;
            cout << "����վ����" << endl;
            map.leastStation(startNum, endNum);
            cout << endl;
            cout << "���ʱ�䣺" << endl;
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
            cout<<"�Ƿ�����:"<<flag<<endl;
        }
    }
    cout << "��лʹ��,�´��ٻᣡ";
    return 0;
}
