// 2014-16649
// 최수빈
//
//  triangle.cpp
//  week03
//
//  Created by Subin_Choi on 3/21/16.
//  Copyright © 2016 DevSusu. All rights reserved.
//

#include <fstream>
#include "triangle.h"

void readFile(float** position){
    
    std::ifstream ifs("input.txt");
    
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++)
            ifs >> position[i][j];
    }
}
