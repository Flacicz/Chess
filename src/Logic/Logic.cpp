#include "headers/Logic.h"

std::unique_ptr<Logic> Logic::instance = nullptr;

Logic::Logic(GLFWwindow* window) : window(std::move(window)) {};

glm::vec2 Logic::getMouseClickPos() {
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	return glm::vec2(x, y);
}

bool Logic::isCursorInSquare(const glm::vec2& currentPos, const glm::vec2& leftBottom, const glm::vec2& rightTop) {
	if ((currentPos.x >= leftBottom.x && currentPos.x <= rightTop.x) && (currentPos.y >= rightTop.y && currentPos.y <= leftBottom.y)) return true;
	return false;
}

//std::string Logic::findFigureByPosition(int x, int y) const {
//	return Game::getInstance().getState()[x][y];
//}

std::shared_ptr<Sprite> Logic::onWhichFigureIsMouse() {
	glm::vec2 currentPos = getMouseClickPos();

	glm::vec2 leftBottomStart(70, 180);
	glm::vec2 rightTopStart(230, 60);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isCursorInSquare(currentPos, leftBottomStart, rightTopStart)) {
				//std::string figure = findFigureByPosition(i, j);
				/*if (figure != "None") {
					return ResourceManager::getInstance().getSprite(figure);
				}*/
			}

			leftBottomStart.x += 160;
			rightTopStart.x += 160;
		}

		leftBottomStart.x = 70;
		rightTopStart.x = 230;

		leftBottomStart.y += 120;
		rightTopStart.y += 120;
	}

	return nullptr;
}



