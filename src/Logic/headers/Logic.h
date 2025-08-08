#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

#include <iostream>

#include "../../Game/headers/Game.h"

class Logic {
private:
	Logic(const Logic&) = delete;
	Logic& operator=(const Logic&) = delete;

	GLFWwindow* window;
	static std::unique_ptr<Logic> instance;
public:
	Logic(GLFWwindow* window);

	static void createInstance(GLFWwindow* window) {
		if (!instance) {
			instance = std::make_unique<Logic>(window);
		}
	}

	static Logic& getInstance() {
		if (!instance) std::cerr << "Logic not initilized" << std::endl;
		return *instance;
	}

	glm::vec2 getMouseClickPos();
	std::string findFigureByPosition(int x, int y) const;
	bool isCursorInSquare(const glm::vec2& currentPos, const glm::vec2& leftBottom, const glm::vec2& rightTop);
	void onWhichFigureIsMouse();
};