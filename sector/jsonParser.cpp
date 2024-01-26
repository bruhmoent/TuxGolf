#include "jsonParser.hpp"
#include "tileData.hpp"
#include <fstream>

TileData 
JsonParser::loadTileData(const std::string& filePath) {
	TileData tileData;

	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cout << "Failed to open JSON file: " << filePath << std::endl;
		return tileData;
	}

	try {
		nlohmann::json json;
		file >> json;

		if (json.contains("Tile")) {
			const auto& tileJson = json["Tile"];
			for (auto it = tileJson.begin(); it != tileJson.end(); ++it) {
				int id = std::stoi(it.key());
				std::string path = it.value();
				tileData.addTexturePath(id, path);

				std::cout << "Read path for ID " << id << ": " << path << std::endl;
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << "Failed to parse JSON file: " << e.what() << std::endl;
	}

	file.close();

	return tileData;
}