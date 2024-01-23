#include "directives.hpp"
#include "json.hpp"

#ifndef LEVEL_DATA_HPP
#define LEVEL_DATA_HPP

struct TileMap;
struct TileMaps;
struct EditorLog;
struct TileData;
struct Tiles;

struct 
LevelData {

    EditorLog& m_editorLog;

    LevelData(EditorLog& editorLog) : m_editorLog(editorLog) {}

    // Load level from a .json file
    void loadLevel(const std::string& filePath, const sf::Vector2f& gridSize, const sf::Vector2u& levelSize, Tiles& tiles, TileData& tileData, TileMaps& tileMaps);
    
    //Truncate a .json level file
    void truncateLevel(const std::string& filePath);
   
    TileMap* createTileMap(const nlohmann::json& tileMapInfo);

    void processTileMapTiles(const nlohmann::json& tileMapInfo, const std::vector<TileMap*>& loadedTileMaps, Tiles& tiles, const sf::Vector2u& levelSize, TileMaps& tileMaps, const TileData& tileData);
};

#endif // LEVEL_DATA_HPP