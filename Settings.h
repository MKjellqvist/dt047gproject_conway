//
// Created by martin on 2023-10-03.
//

#ifndef DT047GPROJECT_CONWAY_SETTINGS_H
#define DT047GPROJECT_CONWAY_SETTINGS_H


#include <ostream>

namespace conway{
    class Settings {
        bool is_fullscreen;
        size_t size_x;
        size_t size_y;
        friend std::ostream& operator << (std::ostream& out, const Settings& s){
            out << "fullscreen: " << s.is_fullscreen << "\nX = " << s.size_x << "\nY = " << s.size_y << "\n";
            return out;
        }
    };
}

#endif //DT047GPROJECT_CONWAY_SETTINGS_H
