#include "headers/ChessEngine.h"


void ChessEngine::initPieces() {
	ResourceManager& rm = ResourceManager::getInstance();
	rm.loadSprite("Desk", "ChessDesk", "Default", 1420, 1080, "Desk");

	uint8_t x = 0; uint8_t y = 7;
	std::map<std::pair<Colors, FiguresNames>, int> idCounter;

	for (auto& ch : state) {
		if (ch == '/') {
			x = 0;
			y--;
		}
		else if (std::isdigit(ch)) {
			x += ch - '0';
		}
		else {
			Colors color = std::isupper(ch) ? Colors::White : Colors::Black;
			FiguresNames figureName = convertCharToEnum(std::tolower(ch));
			int id = idCounter[{color, figureName}]++;

			std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(
				rm.getShaderProgram("Default"),
				std::string(convertColorsToString(color) + convertFiguresToString(figureName)),
				rm.getTexture("DefaultTextureAtlas"),
				glm::vec2(160, 120), glm::vec2(70 + 160 * x, 60 + 120 * y)
			);

			pieces.push_back({ id,color,figureName,y,x,sprite });

			x++;
		}
	}
}

void ChessEngine::render() {
	ResourceManager::getInstance().getSprite("Desk")->render();

	for (auto& piece : pieces) {
		piece.sprite->render();
	}
}



