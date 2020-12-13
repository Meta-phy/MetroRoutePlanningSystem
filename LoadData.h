//
// Created by 17737 on 2020/12/13.
//

#ifndef METROROUTEPLANNINGSYSTEM_LOADDATA_H
#define METROROUTEPLANNINGSYSTEM_LOADDATA_H
#include "Map.h"
#include <string>
using namespace std;

class LoadData {
public:
    LoadData(Map* map,const string &stationFile, const string &routeFile);

private:
    string stationFile;
    string routeFile;
};


#endif //METROROUTEPLANNINGSYSTEM_LOADDATA_H
