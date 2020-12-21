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
   cout<<"��ܰ���ѣ��뽫��������ѻ���������飬��л��"<<endl<<endl; 
   	
	
	int flag=-1; 
    while (flag!=0){
    	cout<<"1.��ѯ·�� 2.�鿴��ͼ 0.�˳�"<<endl;
		cin>>flag;
		if(flag==1)
		{
			string start,end;
        int startNum,endNum;
        cout<<"���������:";
        cin>>start;
        cout<<"�������յ�:";
        cin>>end;
        startNum=map.search(start);
        endNum=map.search(end);
        cout<<endl<<"��ѯ������£�"<<endl<<endl; 
		cout<<"���·����"<<endl; 
        map.shortestRoute(startNum,endNum);
        cout<<endl;
        cout<<"���ٻ��ˣ�" <<endl;
        map.leastTransfer(startNum,endNum);
        cout<<endl;
			
		}
		else if(flag==2)
		{
			ifstream infile;
   	infile.open("map.txt");
	string temp;
	while(getline(infile,temp))
   	{
   		cout<<temp<<endl;
   	}
		 } 
    }
    cout<<"��лʹ��,�´��ٻᣡ"; 
    return 0;
}
