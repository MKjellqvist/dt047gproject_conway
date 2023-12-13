#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include "BaseWindow.h"
#include "Window.h"

/**
 * @mainpage
 * Projektimplementation i DT047G. Conways game of life.
 *
 * Ointressant i sin rena form men kan bli intressant.
 *
 * TODO: Startkonfigurationerna läggs upp i en katalog för att senare kunna väljas och manipuleras
 * från gränssnittet.
 *
 * TODO: Översätt till en GApplication för en rimlig integration i gnome.
 */

using namespace conway;
namespace std{
    /**
     * Hash function for the unordered map in storage.
     * Mangles the y coordinate and xors it onto p.x.
     */
    template <>
    struct hash<point>{
        size_t operator()(const point& p) const{
            auto half_bits = sizeof (size_t) * 4;
            auto y_flipped = p.y >> half_bits | p.y << half_bits;
            return p.x ^ y_flipped;
        }
    };

}
/**
 * Container for life, no constraints on point positions.
 */
struct unordered_map_storage{
    std::unordered_set<point> uset;
    point topleft;
    point bottomright{-1, -1}; // initially empty.
    bool get(coordinate_type x, coordinate_type y) const {
        return uset.find({x, y}) != uset.end();
    }

    void set_minmax(coordinate_type x, coordinate_type y) {
        topleft.x = std::min(x, topleft.x);
        topleft.y = std::min(y, topleft.y);
        bottomright.x = std::max(x, bottomright.x);
        bottomright.y = std::max(y, bottomright.y);
    }

    coordinate_type min_x() const{
        return topleft.x;
    }
    coordinate_type min_y() const{
        return topleft.y;
    }
    coordinate_type max_x() const{
        return bottomright.x + 1;
    }
    coordinate_type max_y() const{
        return bottomright.y + 1;
    }

    void set(coordinate_type x, coordinate_type y){
        set_minmax(x, y);
        uset.insert({x, y});
    }
    void remove(coordinate_type x, coordinate_type y){
        if (!uset.erase({x, y})){
            std::cerr << "remove 0 elements\n";
        }
    }
} unlimited_storage;
/**
 * Grid for life points.
 */
Grid<unordered_map_storage> grid;

std::string init_gun =
        "X\n"
        " XX\n"
        "XX\n";

std::string init_gosper =
        "                         X X" "\n"
        "                        X  X    X" "\n"
        "              X        XX     XX" "\n"
        "             X X     XX   X        XX" "\n"
        "             XX X      XX          XX" "\n"
        " XX          XX XX      X  X" "\n"
        " XX          XX X        X X" "\n"
        "             X X" "\n"
        "              X         X" "\n"
        "                         X" "\n"
        "                       XXX";

std::string big_gosper =
        "                       XXX\n"
        "                         X" "\n"
        "              X         X" "\n"
        "             X X" "\n"
        " XX          XX X        X X" "\n"
        " XX          XX XX      X  X" "\n"
        "             XX X      XX          XX" "\n"
        "             X X     XX   X        XX" "\n"
        "              X        XX     XX" "\n"
        "                        X  X    X" "\n"
        "                         X X" "\n"
        "\n"
        "\n"
        "\n"
        "                         X X" "\n"
        "                        X  X    X" "\n"
        "              X        XX     XX" "\n"
        "             X X     XX   X        XX" "\n"
        "             XX X      XX          XX" "\n"
        " XX          XX XX      X  X" "\n"
        " XX          XX X        X X" "\n"
        "             X X" "\n"
        "              X         X" "\n"
        "                         X" "\n"
        "                       XXX";

std::string init_heart =
        "    XX   XX        \n"
        "   X  XXX  X       \n"
        "  XX   X   XX      \n"
        "   X       X       \n"
        "    XX   XX        \n"
        "     XX XX         \n"
        "      X X          \n"
        "       X";

void init_storage(std::string init = init_gun, conway::point position = {}){
    std::stringstream in(init);
    std::string line;
    for(auto row = 0; std::getline(in, line); row++){
        int col = 0;
        for(auto point: line){
            if(point != ' '){
                unlimited_storage.set(col, row);
            }
            col++;
        }
    }
}

int main() {
    auto reversegosper = "\n" + init_gosper;

    init_storage(big_gosper);
#ifndef NDEBUG
    std::cerr << unlimited_storage.get(0, 0) << "\n";
    std::cerr << unlimited_storage.min_x() << ", " << unlimited_storage.max_x() << "\n";
#endif
    grid.storage = unlimited_storage;

    Window<decltype(grid)> window(600, 400, grid);

    window.play();

}


