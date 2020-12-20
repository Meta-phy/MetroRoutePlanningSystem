//
// Created by 17737 on 2020/12/13.
//

#include "LoadData.h"
#include<fstream>

LoadData::LoadData(Map *map, const string &stationFile, const string &routeFile) {
	ifstream ifs;
	ifs.open(stationFile.c_str(),ios::in);
	string s;
	string station;
    int id[3];
    while(ifs>>s)
    {	
    int	lineNum=0; 
    	if(s == "|"){
			ifs>>id[lineNum];
//			cout<<"站点位于线路:";
			while(id[lineNum] != -1){
//				cout<<id[lineNum]<<" ";
				ifs>>id[++lineNum];
			}
			map->addStation(station,id,lineNum);
//			cout<<endl;
		}else{
			station = s;
//			cout<<station<<endl;
		}	
	}
	ifstream ifs2;
	ifs2.open(routeFile.c_str(),ios::in);
	int st1,st2,dis,line,temp;
	while(ifs2>>temp)
	{
		st1=temp;
		ifs2>>temp;
		st2=temp;
		ifs2>>temp;
		dis=temp;
        ifs2>>temp;
        line=temp;
//		cout<<"st1:"<<st1<<" "<<"st2:"<<st2<<" "<<"dis:"<<dis<<endl;
		map->addRoute(st1,st2,dis,line);
	}

}
