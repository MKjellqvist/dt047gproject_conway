//
// Created by martin on 2023-10-05.
//

#ifndef DT047GPROJECT_CONWAY_CONWAYWINDOW_H
#define DT047GPROJECT_CONWAY_CONWAYWINDOW_H

#include "BaseWindow.h"
#include "ConwayGrid.h"
#include <SFML/Graphics.hpp>

namespace conway {
    extern ConwayGrid grid;

    class ConwayWindow : public conway::BaseWindow {
        using coord_type = int;
        size_t height;
        size_t width;
        sf::RectangleShape rect;
        using BaseWindow::draw;
        void draw(coord_type x, coord_type y);
    public:
        /**
         * Display size
         * @param width
         * @param height
         */
        ConwayWindow(size_t width, size_t height);

        void draw();

        coord_type grid_min_y = 0;
        coord_type grid_min_x = 0;
    };
}
#endif //DT047GPROJECT_CONWAY_CONWAYWINDOW_H
