//
// Created by martin on 2023-10-04.
//

#include <vector>
#include <numeric>

#include "ConwayGrid.h"

namespace conway{
    bool Rules::operator()(bool isAlive, int neighbors) {
        if(isAlive){
            return neighbors == 2 || neighbors == 3;
        }
        return neighbors == 3;
    }
} // conway