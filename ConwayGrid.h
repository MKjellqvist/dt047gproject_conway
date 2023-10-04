//
// Created by martin on 2023-10-04.
//

#ifndef DT047GPROJECT_CONWAY_CONWAYGRID_H
#define DT047GPROJECT_CONWAY_CONWAYGRID_H


#include <cstddef>

namespace conway {
    struct ConwayGrid {
        using coordinate_type = int;

        struct point {
            point(coordinate_type x, coordinate_type y) : x(x), y(y) {
            }

            coordinate_type x;
            coordinate_type y;
            point operator+(point p) const{
                return {p.x + x, p.y + y};
            }
        };

        size_t getAliveNeighbors(point p) const;

        void setAlive(point p);

        bool isAlive(point p) const;
    } grid;
}
#endif //DT047GPROJECT_CONWAY_CONWAYGRID_H
