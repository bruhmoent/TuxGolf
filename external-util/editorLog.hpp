//  LevelEditor
//  Copyright (C) 2023 bruhmoent
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

#include "directives.hpp"

#ifndef EDITOR_LOG_HPP
#define EDITOR_LOG_HPP

struct EditorLog {

    sf::Text m_message;
    sf::Font m_messageFont;
    sf::RenderWindow& m_window;
    sf::Clock m_fadeTimer;
    bool m_shouldDelete;

    EditorLog(sf::RenderWindow& window, std::string path) : m_shouldDelete(false), m_window(window){
        m_messageFont.loadFromFile(path);
        m_message.setCharacterSize(16);
        m_message.setFillColor(sf::Color::White);
        m_message.setFont(m_messageFont);
        m_message.setPosition(10.f, window.getSize().y - 30.f);
    }

    void 
    showMessage(const std::string& message) {
        m_message.setString(message);
        m_fadeTimer.restart();
    }

    void 
    update(float deltaTime) {
        sf::View view = m_window.getView();
        sf::Vector2f viewCenter = view.getCenter();
        sf::Vector2f viewSize = view.getSize();

        float elapsedTime = m_fadeTimer.getElapsedTime().asSeconds();
        float fadeDuration = 1.0f;

        if (elapsedTime > fadeDuration || deltaTime == 0) {
            m_shouldDelete = true;
        }
        else {
            sf::Color color = m_message.getFillColor();
            color.a = static_cast<sf::Uint8>((1.0f - (elapsedTime / fadeDuration)) * 255.f);
            m_message.setFillColor(color);
        }
        sf::Vector2f messagePosition(viewCenter.x - viewSize.x / 2.f + 10.f, viewCenter.y + viewSize.y / 2.f - 30.f);
        m_message.setPosition(messagePosition);
    }

};

#endif