//
// Created by martin on 2023-10-04.
//

#include "BaseWindow.h"

namespace conway {

    sf::VideoMode BaseWindow::GetMode(bool is_fullscreen, unsigned int width, unsigned int height) {
        const auto& modes = sf::VideoMode::getFullscreenModes();
        if(is_fullscreen) {
            return modes[0];
        }
        auto mode_width = std::min<decltype(modes[0].width)>(width, modes[0].width);
        auto mode_height = std::min<decltype(modes[0].height)>(height, modes[0].height);
        return {mode_width, mode_height};
    }

    BaseWindow::BaseWindow(sf::VideoMode mode, bool is_fullscreen):
            sf::RenderWindow(mode, text::TITLE, is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default) {
        setKeyRepeatEnabled(false);
    }

    BaseWindow::BaseWindow(): BaseWindow(GetMode(), true) {}


} // conway