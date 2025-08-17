#pragma once

#include <vector>
#include <iostream>

#include "../../Graphics/headers/ShaderProgram.h"
#include "../../Resources/headers/ResourceManager.h"

class Game {
public:
	Game(const glm::vec2& windowSize);

	static void createInstance(const glm::vec2& windowSize) {
		if (!instance) {
			instance = std::make_unique<Game>(windowSize);
		}
	}

	static Game& getInstance() {
		if (!instance) std::cerr << "Game not initilized" << std::endl;
		return *instance;
	}

	void init();
private:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	static std::unique_ptr<Game> instance;
	std::shared_ptr<ShaderProgram> shaderProgram;

	glm::vec2 windowSize;
};