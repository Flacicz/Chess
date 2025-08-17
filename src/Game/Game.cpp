#include "headers/Game.h"

std::unique_ptr<Game> Game::instance = nullptr;

Game::Game(const glm::vec2& windowSize) : windowSize(windowSize) {}

void Game::init() {
	std::string state = ChessEngine::getInstance().getState();

	auto& rm = ResourceManager::getInstance();

	shaderProgram = rm.loadShaderProgram("Default", "C:/Code/C++/Chess/resources/shaders/vertex_shader.txt",
													"C:/Code/C++/Chess/resources/shaders/fragment_shader.txt");

	rm.loadTexture("ChessDesk", "C:/Code/C++/Chess/resources/textures/board.png");
	rm.loadTexture("DefaultTextureAtlas", "C:/Code/C++/Chess/resources/textures/spritesheet.png");
	rm.loadTextureAtlas("DefaultTextureAtlas");

	shaderProgram->useProgram();
	shaderProgram->setInt("tex", 0);

	glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(windowSize.x), 0.f, static_cast<float>(windowSize.y), -100.f, 100.f);

	shaderProgram->setMatrix4("projectionMat", projectionMatrix);
}

