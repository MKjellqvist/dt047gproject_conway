//
// Created by martin on 2023-10-04.
//

#ifndef DT047GPROJECT_CONWAY_CONWAYGRID_H
#define DT047GPROJECT_CONWAY_CONWAYGRID_H


#include <cstddef>

namespace conway {
    struct Rules{
        virtual bool operator ()(bool isAlive, int neighbors);
    };
    struct Grid {
        Rules rules;
        using coordinate_type = int;

        struct point {
            point(coordinate_type x, coordinate_type y) : x(x), y(y) {
            }

            coordinate_type x;
            coordinate_type y;
            point offset(point p) const{
                return {p.x + x, p.y + y};
            }
        };
        struct Storage{
            virtual bool getPoint(coordinate_type x, coordinate_type y) = 0;
            virtual void setPoint(coordinate_type x, coordinate_type y) = 0;
        } *storage;



        size_t getAliveNeighbors(point p) const;

        /**
         *
         * @param p
         * @return false if the point is not available in the
         * coordinate system used.
         */
        bool setAlive(point p);

        bool isAlive(point p) const;

        /**
         *
         * @return false if no evolution happened
         */
        bool tick();

        void setSize(coordinate_type width, coordinate_type height);

        point getSize() const;
    } inline grid;
}
#endif //DT047GPROJECT_CONWAY_CONWAYGRID_H
