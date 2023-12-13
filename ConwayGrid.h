//
// Created by martin on 2023-10-04.
//

#ifndef DT047GPROJECT_CONWAY_CONWAYGRID_H
#define DT047GPROJECT_CONWAY_CONWAYGRID_H


#include <cstddef>
#include <numeric>

namespace conway {
    using coordinate_type = int;

    struct Rules{
        virtual bool operator ()(bool isAlive, int neighbors);
    };
    struct point {
        point() = default;
        point(coordinate_type x, coordinate_type y) : x(x), y(y) {
        }

        coordinate_type x;
        coordinate_type y;
        point offset(point p) const{
            return {p.x + x, p.y + y};
        }
        bool operator == (const point& p) const{
            return x == p.x && y == p.y;
        }
    };
    template<typename Store>
    struct Grid {
        Rules rules;

        Store storage;

        size_t getAliveNeighbors(point src) const{
            return std::accumulate(neighbors.begin(), neighbors.end(), size_t(), [this, src](size_t curr, const point& p){
                return this->isAlive(p.offset(src)) + curr;
            });
        }

        bool isAlive(point p) const{
            return storage.get(p.x, p.y);
        }

        /**
         * Evolve each dot one round based on rules.
         * @return false if no evolution happened
         */
        bool tick(){
            Store temp = storage;
            auto evolved = false;
            for(auto x = storage.min_x() - 1; x < storage.max_x() + 1; x++){
                for(auto y = storage.min_y() - 1; y < storage.max_y() + 1; y++){
                    auto n = getAliveNeighbors({x, y});
                    auto wasAlive = isAlive({x, y});
                    auto alive = rules(wasAlive, n);
                    if(alive != wasAlive){
                        evolved = true;
                        if(alive){
                            temp.set(x, y);
                        }else{
                            temp.remove(x, y);
                        }
                    }
                }
            }
            storage = temp;
            return evolved;
        }

        void setSize(coordinate_type width, coordinate_type height);

        point getSize() const;
    private:
        std::vector<point> neighbors = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1},
                                        {0, 1}, {1, 1}};
    };
}
#endif //DT047GPROJECT_CONWAY_CONWAYGRID_H
