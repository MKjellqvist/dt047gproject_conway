//
// Created by martin on 2023-10-04.
//

#include <vector>
#include <numeric>

#include "ConwayGrid.h"

namespace conway{

std::vector<Grid::point> neighbors = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1},
{0, 1}, {1, 1}};

size_t conway::Grid::getAliveNeighbors(conway::Grid::point src) const {
    return std::accumulate(neighbors.begin(), neighbors.end(), size_t(), [this, src](size_t curr, const point& p){
        return this->isAlive(p.offset(src)) + curr;
    });
}

    bool Grid::isAlive(point p) const {
        return storage->getPoint(p.x, p.y);
    }

    bool Grid::setAlive(point p) {
        try{
            storage->setPoint(p.x, p.y);
        }catch (...){
            return false;
        }
        return true;
    }

    bool Grid::tick() {
        Grid g = *this;

    }

    bool Rules::operator()(bool isAlive, int neighbors) {
        if(isAlive){
            return neighbors == 2 || neighbors == 3;
        }
        return neighbors == 3;
    }
} // conway