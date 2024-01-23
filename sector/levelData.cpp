#include "levelData.hpp"
#include "TileMaps.hpp"
#include "TileMap.hpp"
#include "tileData.hpp"
#include "tiles.hpp"
#include "tile.hpp"

void LevelData::loadLevel(const std::string& filePath, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, Tiles& tiles, TileData& tileData, TileMaps& tileMaps)
{
    if (filePath.substr(filePath.find_last_of('.') + 1) != "json") {
        throw std::runtime_error("Invalid file format. Expected a JSON file.");
    }

    if (!tiles.m_tiles.empty() || !tileMaps.m_tileMaps.empty()) {
        tiles.m_tiles.clear();
        tileMaps.m_tileMaps.clear();
    }

    nlohmann::json json;
    std::ifstream inputFile(filePath);
    inputFile >> json;

    for (TileMap* tileMap : tileMaps.m_tileMaps) {
        for (Tile* tile : tileMap->m_helperMapTiles) {
            delete tile;
        }
        tileMap->m_helperMapTiles.clear();

        for (Tile* tile : tileMap->m_tileMapTiles) {
            delete tile;
        }
        tileMap->m_tileMapTiles.clear();
    }

    inputFile.close();

    for (const auto& tileMapInfo : json["TileMaps"]) {
        TileMap* tileMap = createTileMap(tileMapInfo);
        tileMaps.m_tileMaps.push_back(tileMap);
    }

    std::vector<TileMap*> loadedTileMaps;

    for (const auto& tileMapInfo : json["TileMaps"]) {
        TileMap* tileMap = createTileMap(tileMapInfo);
        loadedTileMaps.push_back(tileMap);
    }

    for (int i = 0; i < loadedTileMaps.size(); ++i) {
        for (const auto& tileMapInfo : json["TileMaps"]) {
            processTileMapTiles(tileMapInfo, loadedTileMaps, tiles, levelSize, tileMaps, tileData);
        }
    }
}

TileMap* LevelData::createTileMap(const nlohmann::json& tileMapInfo)
{
    TileMap* tileMap = new TileMap({ tileMapInfo["GridSize"]["x"], tileMapInfo["GridSize"]["y"] });
    tileMap->m_gridSize.x = tileMapInfo["GridSize"]["x"];
    tileMap->m_gridSize.y = tileMapInfo["GridSize"]["y"];
    tileMap->opacity = tileMapInfo["Opacity"];
    return tileMap;
}

void LevelData::processTileMapTiles(const nlohmann::json& tileMapInfo, const std::vector<TileMap*>& loadedTileMaps, Tiles& tiles, const sf::Vector2u& levelSize, TileMaps& tileMaps, const TileData& tileData)
{
    if (tileMapInfo.contains("TileMapTiles") && !tileMapInfo["TileMapTiles"].empty()) {
        for (const auto& tileInfo : tileMapInfo["TileMapTiles"]) {
            if (tileInfo.contains("tileMapID") && tileInfo["tileMapID"].is_number()) {
                int tileMapID = tileInfo["tileMapID"].get<int>();
                int tileMapIndex = tileMapID;

                float posX = tileInfo["Position"]["x"].get<float>();
                float posY = tileInfo["Position"]["y"].get<float>();
                int id = tileInfo["ID"];

                if (tileMapIndex >= 0 && tileMapIndex < loadedTileMaps.size()) {
                    TileMap* currentTileMap = loadedTileMaps[tileMapIndex];
                    tiles.addTileToTileMap(tileData, id, sf::Vector2f(posX, posY), currentTileMap->m_gridSize, levelSize, tileMaps, tileMapIndex);
                }
                else {
                    std::cout << "Invalid tile map index: " << tileMapIndex << std::endl;
                    std::cout << "loadedTileMaps.size(): " << loadedTileMaps.size() << std::endl;
                }
            }
            else {
                std::cout << "Invalid or missing 'tileMapID' value in tile info." << std::endl;
            }
        }
    }
    else {
        std::cout << "Empty or missing 'TileMapTiles' array in tile map." << std::endl;
    }
}


void
LevelData::truncateLevel(const std::string& filePath) {
	if (filePath.substr(filePath.find_last_of('.') + 1) != "json") {
		throw std::runtime_error("Invalid file format. Expected a JSON file.");
	}

	std::ofstream saveFile(filePath, std::ios::trunc);
	saveFile.close();
	std::remove(filePath.c_str());
}