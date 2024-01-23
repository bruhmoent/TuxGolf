#include "app.hpp"

void App::app_loop()
{
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // DEV TOOL: Get pos on mouse click
            /*
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Mouse X: " << event.mouseButton.x << ", Mouse Y: " << event.mouseButton.y << std::endl;
                }
            }
            */
        }

        window->clear(sf::Color(189, 138, 35));

        for (size_t i = 0; i < m_items.size() - 1; ++i) {
            m_items[i]->update(m_menuManager);
            if (m_items[i]->is_completed) {
                m_items[i + 1]->is_active = true;
            }
        }

        m_sc_manager->handle_input(*window);
        m_sc_manager->draw_current_scene(*window);

        window->display();
    }
}