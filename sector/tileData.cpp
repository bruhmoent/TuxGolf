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

#include "tileData.hpp"

void TileData::addTexturePath(int id, const std::string& texturePath) {
	m_texturePaths[id] = texturePath;

	sf::Texture texture;
	if (!texture.loadFromFile("tile.png")) {
		std::cerr << "Error loading texture: " << texturePath << std::endl;
	}

	m_textures[id] = texture;
}

const std::string&
TileData::getTexturePath(int id) const
{
	static std::string emptyPath;
	auto it = m_texturePaths.find(id);
	if (it != m_texturePaths.end()) {
		return it->second;
	}
	return emptyPath;
}

std::vector<int>
TileData::getTileIDs() const
{
	std::vector<int> tileIDs;
	for (const auto& pair : m_texturePaths) {
		tileIDs.push_back(pair.first);
	}
	return tileIDs;
}

const sf::Texture& TileData::getTexture(int id) const {
	auto it = m_textures.find(id);
	if (it != m_textures.end()) {
		return it->second;
	}

	// Handle missing texture
	static sf::Texture emptyTexture;
	return emptyTexture;
}