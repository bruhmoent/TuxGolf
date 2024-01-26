//  LevelEditor
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

#include <SFML/Graphics.hpp>

#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera
{
public:
    sf::Vector2f m_cameraOffset;
    float m_zoomLevel;
    float m_minZoom;
    float m_maxZoom;

    Camera() : m_zoomLevel(1.0f), m_minZoom(0.5f), m_maxZoom(2.0f) {}

    void viewFollow(const sf::Vector2f& objectPos, sf::RenderWindow& window, float speed);

    void zoomIn(sf::RenderWindow& window, float zoomFactor);

    void zoomOut(sf::RenderWindow& window, float zoomFactor);

private:
    void updateView(sf::RenderWindow& window);
};

#endif