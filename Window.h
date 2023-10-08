//
// Created by martin on 2023-10-05.
//

#ifndef DT047GPROJECT_CONWAY_WINDOW_H
#define DT047GPROJECT_CONWAY_WINDOW_H

#include "BaseWindow.h"
#include "ConwayGrid.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace conway {
    template<typename Grid>
    class Window : public conway::BaseWindow {
        using coord_type = int;
        size_t height;
        size_t width;
        Grid grid;
        using BaseWindow::draw;
    public:
        static const unsigned int FRAMRATE_LIMIT = 10;
        /**
         * Display size
         * @param width
         * @param height
         */
        Window(size_t width, size_t height, Grid grid):
      //  BaseWindow(BaseWindow::GetMode(false, 640, 480), false),
        width(width), height(height), grid(grid){
            setFramerateLimit(FRAMRATE_LIMIT);
        }

        void draw(){
            {
                clear();
                auto size = getSize();
                auto height_per_life = size.y * 1.0f/ height;
                auto width_per_life = size.x * 1.0f/ width;
                auto rect = sf::RectangleShape({width_per_life, height_per_life});
                for(coord_type cx = grid_min_x; cx < width + grid_min_x; cx++){
                    for(coord_type cy = grid_min_y; cy < height + grid_min_y; cy++){
                        if(grid.isAlive({cx, cy})){
                            rect.setPosition(cx * width_per_life - grid_min_x * width_per_life, cy * height_per_life - grid_min_y * height_per_life);
                            draw(rect);
                        }
                    }
                }
                display();
            }
        }

        coord_type grid_min_y = 0;
        coord_type grid_min_x = 0;

        void play(){
            while(isOpen()){
                draw();
                grid.tick();
                sf::Event e;
                if(pollEvent(e)){
                    if(e.type == sf::Event::Closed){
                        close();
                    }
                    if(e.type == sf::Event::KeyReleased){
                        switch (e.key.code) {
                            case sf::Keyboard::Key::Left:
                                grid_min_x--;
                                break;
                            case sf::Keyboard::Key::Right:
                                grid_min_x++;
                                break;
                            case sf::Keyboard::Key::Up:
                                grid_min_y--;
                                break;
                            case sf::Keyboard::Key::Down:
                                grid_min_y++;
                                break;
                        }
                    }

                }
            }
        }

    };
}
#endif //DT047GPROJECT_CONWAY_WINDOW_H
