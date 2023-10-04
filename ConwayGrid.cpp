//
// Created by martin on 2023-10-04.
//

#include <vector>
#include <numeric>

#include "ConwayGrid.h"

namespace conway{

std::vector<ConwayGrid::point> neighbors = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1},
{0, 1}, {1, 1}};

size_t conway::ConwayGrid::getAliveNeighbors(conway::ConwayGrid::point src) const {
    return std::accumulate(neighbors.begin(), neighbors.end(), size_t(), [this, src](size_t curr, const point& p){
        return this->isAlive(p + src) + curr;
    });
}

    bool ConwayGrid::isAlive(ConwayGrid::point p) const {
        // jag kan göra en find i ett set! unordered?
        // jag kan göra ett uppslag i en vector-vector [x][y]

        return false;
    }

    void ConwayGrid::setAlive(ConwayGrid::point p) {
        // Ja hur gör jag här?
    }

} // conway