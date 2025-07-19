#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include <glad/glad.h>

#include "../../Render/headers/Texture2D.h"


class ChessHelper {
public:
	class Vertex {
	public:
		float x, y;
		void printPoint() const { std::cout << x << " " << y << std::endl; };
	};

	class Fragment {
	public:
		float r, g, b;
	};

	std::string getShaderCode(const char* path);
	std::vector<Vertex> getPoints(unsigned int squares, unsigned int width);
	void printPoints(std::vector<Vertex> points) const;
	std::vector<Fragment> getColors(unsigned int squares);
	std::shared_ptr<Texture2D> loadTexture(const std::string& textureName, const std::string& path);
	std::shared_ptr<Texture2D> getTexture(const std::string& textureName);
private:
	typedef std::map<const std::string, std::shared_ptr<Texture2D>> TextureMap;
	static TextureMap textures;
};