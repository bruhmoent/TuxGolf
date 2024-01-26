#include "levelData.hpp"
#include <sstream>
#include "jsonParser.hpp"

void LevelData::saveLevel(const std::string& levelName, const sf::Vector2u& levelSize, const sf::Vector2f& gridSize, TileData& tileData, TileMaps& tileMaps) {
    nlohmann::json json;

    json["LevelName"] = levelName;
    json["LevelSize"]["x"] = levelSize.x;
    json["LevelSize"]["y"] = levelSize.y;

    std::vector<nlohmann::json> tileMapData;
    for (const TileMap* tileMap : tileMaps.m_tileMaps) {
        nlohmann::json tileMapInfo;
        tileMapInfo["Opacity"] = tileMap->opacity;
        tileMapInfo["GridSize"]["x"] = tileMap->m_grid_size.x;
        tileMapInfo["GridSize"]["y"] = tileMap->m_grid_size.y;
        tileMapInfo["Width"] = tileMap->m_width;
        tileMapInfo["Height"] = tileMap->m_height;

        int estimatedWidth = static_cast<int>(levelSize.x / gridSize.x);
        int estimatedHeight = static_cast<int>(levelSize.y / gridSize.y);

        std::vector<uint32_t> tileIDsFilled(estimatedWidth * estimatedHeight, 0);

        for (const auto& tile : tileMap->m_tiles) {
            int x = static_cast<int>(tile.position.x / gridSize.x);
            int y = static_cast<int>(tile.position.y / gridSize.y);

            if (x >= 0 && x < estimatedWidth && y >= 0 && y < estimatedHeight) {
                int index = x + y * estimatedWidth;
                tileIDsFilled[index] = tile.id;
            }
        }

        std::string tilemapStr;
        for (int y = 0; y < estimatedHeight; ++y) {
            for (int x = 0; x < estimatedWidth; ++x) {
                int index = x + y * estimatedWidth;
                tilemapStr += std::to_string(tileIDsFilled[index]) + " ";
            }
            tilemapStr.pop_back();
            tilemapStr += "\n";
        }

        tilemapStr.pop_back();

        tileMapInfo["TileMapTiles"] = tilemapStr;
        tileMapData.push_back(tileMapInfo);
    }
    json["TileMaps"] = tileMapData;

    std::ofstream outputFile("level.json", std::ios::trunc);
    outputFile << json.dump(4);
    outputFile.close();
}

void LevelData::loadLevel(const std::string& filePath, const sf::Vector2f& gridSize, sf::Vector2u& levelSize, TileData& tileData, TileMaps& tileMaps) {
    for (TileMap* tileMap : tileMaps.m_tileMaps) {
        tileMap->clearTiles();
    }

    nlohmann::json json;
    std::ifstream inputFile(filePath);
    inputFile >> json;
    inputFile.close();

    levelSize.x = json["LevelSize"]["x"];
    levelSize.y = json["LevelSize"]["y"];

    const auto& tileMapsData = json["TileMaps"];
    for (const auto& tileMapInfo : tileMapsData) {
        TileMap tileMap(tileData, tileMapInfo["Width"], tileMapInfo["Height"], { tileMapInfo["GridSize"]["x"], tileMapInfo["GridSize"]["y"] });

        tileMap.opacity = tileMapInfo["Opacity"];

        const auto& tilemapStr = tileMapInfo["TileMapTiles"];
        std::istringstream iss(tilemapStr.get<std::string>());
        std::vector<std::string> lines;

        for (std::string line; std::getline(iss, line, '\n'); ) {
            lines.push_back(line);
        }

        int y = 0;
        for (const auto& line : lines) {
            std::istringstream lineStream(line);
            int x = 0;
            int tileID;

            while (lineStream >> tileID) {
                if (tileID != 0) {
                    float xPos = x * gridSize.x;
                    float yPos = y * gridSize.y;
                    tileMap.addTile(tileID, { xPos, yPos });
                }
                x++;
            }
            y++;
        }

        tileMaps.addTileMap(tileMap);
    }
}