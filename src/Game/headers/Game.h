#pragma once

#include <vector>
#include <iostream>

#include "../../Graphics/headers/ShaderProgram.h"
#include "../../Resources/headers/ResourceManager.h"

class Game {
public:
	Game(const glm::vec2& windowSize);
	~Game();

	void init();
	void render();
private:
	ResourceManager rm;

	std::string state[8][8];
	std::shared_ptr<ShaderProgram> shaderProgram;

	glm::vec2 windowSize;
	glm::vec2 figureSize;
};