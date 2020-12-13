//
// Created by 17737 on 2020/12/13.
//

#include "LoadData.h"


LoadData::LoadData(Map *map, const string &stationFile, const string &routeFile) {
    int id[] = {1,2};
    map->addStation("广州站",id,2);
    int id2[] = {1,2,3,4,5,6,7,8};
    map->addStation("广州南站",id2,8);
    int id3[] = {2};
    map->addStation("华师站",id3,1);
}
