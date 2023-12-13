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
    /**
     * Display font in UI. Bad choice for now.
     */
    constexpr auto sfFontFilename = "/usr/share/fonts/opentype/cantarell/Cantarell-Thin.otf";

    /**
     * Ticks and display
     * @tparam Grid
     */
    template<typename Grid>
    class Window : public conway::BaseWindow {
        using coord_type = int;
        coord_type height;
        coord_type width;
        Grid grid;
        sf::Font windowFont;
        using BaseWindow::draw;
    public:
        static const unsigned int FRAMRATE_LIMIT = 30;

/**
         * Display size
         * @param width
         * @param height
         */
        Window(size_t width, size_t height, Grid grid):
      //  BaseWindow(BaseWindow::GetMode(false, 640, 480), false),
        width(width), height(height), grid(grid){
            setFramerateLimit(FRAMRATE_LIMIT);
            setup_handlers();
            load_font();
        }
        /**
         * Update screen, meta info and apply rules for dots/game.
         * Call this for step by step updates.
         */
        void draw(){
            clear();
            auto size = getSize();
            auto height_per_life = size.y * 1.0f/ height;
            auto width_per_life = size.x * 1.0f/ width;
            auto rect = sf::RectangleShape({width_per_life, height_per_life});
            auto alive = 0;
            auto pixels = 0;
            for(coord_type cx = grid_min_x; cx < width + grid_min_x; cx++){
                for(coord_type cy = grid_min_y; cy < height + grid_min_y; cy++){
                    if(grid.isAlive({cx, cy})){
                        rect.setPosition(cx * width_per_life - grid_min_x * width_per_life, cy * height_per_life - grid_min_y * height_per_life);
                        draw(rect);
                    }
                }
            }
            std::string meta = "Alive " + std::to_string(alive) + "[" + std::to_string(grid_min_x) + ", " + std::to_string(grid_min_y) + "]"
            "-[" + std::to_string(width + grid_min_x) + ", " + std::to_string(height + grid_min_y) + "]";
            auto text = sf::Text(meta, windowFont, 50);
            text.setFillColor(sf::Color::White);
            draw(text);
            display();
        }
        /**
         * An offset to the displayed section of the grid.
         */
        coord_type grid_min_y = 0;
        coord_type grid_min_x = 0;

        /**
         * If there is a registered handler for the event type, call it.
         * @param event
         * @return true if the event was handled.
         */
        bool handleEvents(sf::Event event) {
            // Call handler if it exists.
            return events[event.type] && events[event.type](event);
        }
        /**
         * Main event loop. Loops until window is closed.
         */
        void play(){
            sf::Event playEvent;
            while(isOpen()){
                draw();
                grid.tick();
                while(pollEvent(playEvent))
                    handleEvents(playEvent);
            }
        }

    private:
        void setup_handlers() {
            events[sf::Event::KeyPressed] = [this](sf::Event e){
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
                return true;
            };
            events[sf::Event::Closed] = [this](sf::Event e){
                this->close();
                return true;
            };
            events[sf::Event::MouseButtonPressed] = [this](sf::Event e){
                this->addDot({e.mouseButton.x, e.mouseButton.y});
                return true;
            };

        }
        void addDot(point p){
            // transform screen to grid coordinates.
            // This should be simplified to
            // point to_grid(coord_type x, coord_type y)
            // point from_grid(point );
            auto size = getSize();
            auto height_per_life = size.y * 1.0f/ height;
            auto width_per_life = size.x * 1.0f/ width;
            auto col = p.x / width_per_life + grid_min_x;
            auto row = p.y / height_per_life + grid_min_y;
            grid.storage.set(col, row);
        }
        void load_font() {
            windowFont.loadFromFile(sfFontFilename);
        }

        std::unordered_map<sf::Event::EventType, std::function<bool(sf::Event)>> events;
    };
}
#endif //DT047GPROJECT_CONWAY_WINDOW_H
