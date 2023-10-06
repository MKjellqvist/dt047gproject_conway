//
// Created by martin on 2023-10-05.
//
#include "ConwayWindow.h"
#include <SFML/Graphics.hpp>
namespace conway{
    ConwayWindow::ConwayWindow(size_t width, size_t height):width(width), height(height) {

    }

    void ConwayWindow::draw() {
        clear();
        auto size = getSize();
        auto height_per_life = size.y * 1.0f/ height;
        auto width_per_life = size.x * 1.0f/ width;
        rect = sf::RectangleShape({height_per_life, width_per_life});
        for(coord_type cx = grid_min_x; cx < width; cx++){
            for(coord_type cy = grid_min_y; cy < height; cy++){
                if(grid.isAlive({cx, cy})){
                    rect.setPosition(cx*width_per_life, cy*height_per_life);
                    draw(rect);
                }
            }
        }
        display();
    }

    void ConwayWindow::draw(coord_type x, coord_type y) {

    }

}

