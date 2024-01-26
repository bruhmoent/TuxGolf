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

#include "camera.hpp"

void Camera::viewFollow(const sf::Vector2f& objectPos, sf::RenderWindow& window, float speed)
{
	sf::View view = window.getView();

	view.setCenter(objectPos);

	window.setView(view);
}

void Camera::zoomIn(sf::RenderWindow& window, float zoomFactor)
{
	float newZoomLevel = m_zoomLevel * zoomFactor;
	if (newZoomLevel <= m_maxZoom)
	{
		sf::Vector2f viewCenter = window.getView().getCenter();
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		m_zoomLevel = newZoomLevel;

		sf::Vector2f newMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::Vector2f delta = newMousePos - mousePos;

		m_cameraOffset -= delta;
		updateView(window);
	}
}

void Camera::zoomOut(sf::RenderWindow& window, float zoomFactor)
{
	float newZoomLevel = m_zoomLevel / zoomFactor;
	if (newZoomLevel >= m_minZoom)
	{
		sf::Vector2f viewCenter = window.getView().getCenter();
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		m_zoomLevel = newZoomLevel;

		sf::Vector2f newMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		sf::Vector2f delta = newMousePos - mousePos;

		m_cameraOffset -= delta;
		updateView(window);
	}
}

void Camera::updateView(sf::RenderWindow& window)
{
	if (m_zoomLevel > m_maxZoom)
	{
		m_zoomLevel = m_maxZoom;
	}
	else if (m_zoomLevel < m_minZoom)
	{
		m_zoomLevel = m_minZoom;
	}

	sf::View view = window.getView();
	view.setCenter(view.getCenter() + m_cameraOffset);
	view.setSize(window.getDefaultView().getSize() / m_zoomLevel);
	window.setView(view);
}