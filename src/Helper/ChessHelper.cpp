#include "headers/ChessHelper.h"

std::string ChessHelper::getShaderCode(const char* path) {
	std::ifstream shaderStream(path, std::ios::in);

	if (shaderStream.is_open()) {
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();

		shaderStream.close();

		return sstr.str();
	}
}

std::vector<ChessHelper::Vertex> ChessHelper::getPoints(unsigned int squares, unsigned int width) {
	std::vector<Vertex> points;
	std::vector<float> points2;
	float interval = 0.25f;

	float startX, startY;
	startX = startY = -1.0f;
	
	for (int i = 0; i < squares; i++) {
		for (int j = 0; j < squares; j++) {
			float x = startX + j * interval;
			float y = startY + i * interval;

			float x1 = x + interval;
			float y1 = y + interval;

			points.push_back({ x,y });
			points.push_back({ x1,y });
			points.push_back({ x,y1 });

			points.push_back({ x1,y });
			points.push_back({ x,y1 });
			points.push_back({ x1,y1 });

		}
	}

	return points;
}

void ChessHelper::printPoints(std::vector<ChessHelper::Vertex> points) const {
	for (auto& point : points) {
		point.printPoint();
	}
}