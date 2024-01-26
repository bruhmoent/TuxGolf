#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "json.hpp"
struct TileData;

struct JsonParser 
{
    static TileData loadTileData(const std::string& filePath);
};

#endif // JSON_PARSER_HPP