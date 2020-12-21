#include <iostream>
#include "Map.h"
#include "LoadData.h"
#include <fstream>

int main() {
    Map map;
    LoadData ld(&map,"station.txt","route.txt");
//    cout<<map.getRouteNum();
//    std::cout<<1<<std::endl;
    map.Floyd();
    map.LTFloyd();
//    for (int i = 0; i < map.getStationNum(); ++i) {
//        for (int j = 0; j < map.getStationNum(); ++j) {
//            map.shortestRoute(i,j);
//        }
//    }
   cout<<"欢迎使用广州地铁路线查询系统！"<<endl<<endl; 
   	ifstream infile;
   	infile.open("map.txt");
	string temp;
	while(getline(infile,temp))
   	{
   		cout<<temp<<endl;
   	}
	
	int flag=-1; 
    while (flag!=0){
    	cout<<"1.查询路线 0.退出"<<endl;
		cin>>flag;
		if(flag==1)
		{
			int start,end;
        cout<<"请输入起点:";
        cin>>start;
        cout<<"请输入终点:";
        cin>>end;
        cout<<endl<<"查询结果如下："<<endl<<endl; 
		cout<<"最短路径："<<endl; 
        map.shortestRoute(start,end);
        cout<<endl;
        cout<<"最少换乘：" <<endl;
        map.leastTransfer(start,end);
        cout<<endl;
			
		} 
    }
    cout<<"感谢使用,下次再会！"; 
    return 0;
}
