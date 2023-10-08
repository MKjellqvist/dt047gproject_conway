//
// Created by martin on 2023-10-05.
//

#ifndef DT047GPROJECT_CONWAY_WINDOW_H
#define DT047GPROJECT_CONWAY_WINDOW_H

#include "BaseWindow.h"
#include "ConwayGrid.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>

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

        bool handleEvents(sf::Event event) {
            // throws std::bad_function_call on most event s
            events[event.type](event);
        }

        void play(){
            sf::Event playEvent;
            while(isOpen()){
                draw();
                grid.tick();
                while(pollEvent(playEvent))
                    handleEvents(playEvent);
            }
        }

        std::unordered_map<sf::Event::EventType, std::function<bool(sf::Event)>> events;
    };
}
#endif //DT047GPROJECT_CONWAY_WINDOW_H
