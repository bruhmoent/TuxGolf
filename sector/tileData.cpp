#include "tileData.hpp"
#include "tiles.hpp"
#include "tile.hpp"

void
TileData::addTexturePath(int id, const std::string& texturePath)
{
	m_texturePaths[id] = texturePath;
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