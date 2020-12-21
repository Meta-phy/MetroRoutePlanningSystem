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
   cout<<"��ӭʹ�ù��ݵ���·�߲�ѯϵͳ��"<<endl<<endl; 
   	ifstream infile;
   	infile.open("map.txt");
	string temp;
	while(getline(infile,temp))
   	{
   		cout<<temp<<endl;
   	}
	
	int flag=-1; 
    while (flag!=0){
    	cout<<"1.��ѯ·�� 0.�˳�"<<endl;
		cin>>flag;
		if(flag==1)
		{
			int start,end;
        cout<<"���������:";
        cin>>start;
        cout<<"�������յ�:";
        cin>>end;
        cout<<endl<<"��ѯ������£�"<<endl<<endl; 
		cout<<"���·����"<<endl; 
        map.shortestRoute(start,end);
        cout<<endl;
        cout<<"���ٻ��ˣ�" <<endl;
        map.leastTransfer(start,end);
        cout<<endl;
			
		} 
    }
    cout<<"��лʹ��,�´��ٻᣡ"; 
    return 0;
}
