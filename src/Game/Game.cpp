#include "headers/Game.h"

Game::Game(const glm::vec2& windowSize) : windowSize(windowSize), figureSize(160,120) {}

Game::~Game() {}

void Game::init() {
	shaderProgram = rm.loadShaderProgram("Default", "C:/Code/C++/Chess/resources/shaders/vertex_shader.txt",
												    "C:/Code/C++/Chess/resources/shaders/fragment_shader.txt");

	rm.loadTexture("ChessDesk", "C:/Code/C++/Chess/resources/textures/board.png");
	rm.loadTexture("DefaultTextureAtlas", "C:/Code/C++/Chess/resources/textures/spritesheet.png");
	rm.loadTextureAtlas("DefaultTextureAtlas", "C:/Code/C++/Chess/resources/textures/spritesheet.png");

	glm::vec2 startPos(70, 900);
	std::vector<std::string> names;
	std::ifstream in("C:/Code/C++/Chess/resources/desk.txt", std::ios::in);
	if (in.is_open()) {
		std::string line;
		while (std::getline(in, line)) {
			for (int i = 0; i < line.length();) {
				size_t index = line.find_first_of(" ");

				std::string substr = line.substr(i, index - i);

				std::string subTexture = substr;
				if (subTexture.find_first_of("12345678") != std::string::npos) subTexture.pop_back();

				line[index] = '.';
				i += (index - i) + 1;

				names.push_back(substr);
				if (substr != "None") rm.loadSprite(substr, "DefaultTextureAtlas", "Default", figureSize.x, figureSize.y, subTexture);
			}
		}
		in.close();
	}
	else {
		std::cerr << "Can't open this file" << std::endl;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			state[i][j] = names[8 * i + j];
			if (state[i][j] != "None") {
				auto& sprite = rm.getSprite(names[i * 8 + j]);
				sprite->setPosition(startPos);
			}

			startPos.x += 160;
		}

		startPos.x = 70;
		startPos.y -= 120;
	}

	shaderProgram->useProgram();
	shaderProgram->setInt("tex", 0);

	glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(windowSize.x), 0.f, static_cast<float>(windowSize.y), -100.f, 100.f);

	shaderProgram->setMatrix4("projectionMat", projectionMatrix);
}

void Game::render() {
	auto& desk = rm.loadSprite("Desk", "ChessDesk", "Default", windowSize.x, windowSize.y, "Desk");
	desk->render();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (state[i][j] != "None") {
				auto& sprite = rm.getSprite(state[i][j]);
				sprite->render();
			}
		}
	}
}