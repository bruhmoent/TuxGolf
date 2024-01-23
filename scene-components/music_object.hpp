//  TuxGolf
//  Copyright (C) 2024 bruhmoent
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

#ifndef MUSIC_OBJECT_HPP
#define MUSIC_OBJECT_HPP

class MusicObject {
public:
    MusicObject(const std::string& path);

    void play();
    void stop();
    void pause();
    void resume();

    void change_music(const std::string& new_path);

private:
    sf::Music m_music;
};

#endif // MUSIC_OBJECT_HPP