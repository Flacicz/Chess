#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

class ChessHelper {
public:
	class Vertex {
	public:
		float x, y;
		void printPoint() const { std::cout << x << " " << y << std::endl; };
	};

	std::string getShaderCode(const char* path);
	std::vector<Vertex> getPoints(unsigned int squares, unsigned int width);
	void printPoints(std::vector<Vertex> points) const;
};