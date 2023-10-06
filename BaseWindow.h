//
// Created by martin on 2023-10-04.
//

#ifndef DT047GPROJECT_CONWAY_BASEWINDOW_H
#define DT047GPROJECT_CONWAY_BASEWINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace conway {

    namespace text{
        const std::string TITLE = "GOL";
    }

    class BaseWindow:public sf::RenderWindow {
        explicit BaseWindow(sf::VideoMode mode, bool is_fullscreen);

    public:
        BaseWindow();

    private:
        static sf::VideoMode GetMode(bool is_fullscreen = true, unsigned int width = 0, unsigned int height = 0);

    };

} // conway

#endif //DT047GPROJECT_CONWAY_BASEWINDOW_H
