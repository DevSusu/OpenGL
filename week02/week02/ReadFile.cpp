//  2014-16649 최수빈
//
//  ReadFile.cpp
//  week02
//
//  Created by Subin_Choi on 3/14/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <fstream>
#include "ReadFile.h"

void readFile(double &cen_x, double &cen_y, double &cen_z, double &radius){
    
    std::ifstream ifs("data.txt");
    
    ifs >> cen_x;
    ifs >> cen_y;
    ifs >> cen_z;
    ifs >> radius;
}