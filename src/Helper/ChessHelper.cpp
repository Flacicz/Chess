#include "headers/ChessHelper.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "headers/stb_image.h"

ChessHelper::TextureMap ChessHelper::textures;

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
	float interval = 2.0f / squares;

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

std::vector<ChessHelper::Fragment> ChessHelper::getColors(unsigned int squares) {
	std::vector<ChessHelper::Fragment> colors;
	bool alternation = true;
	Fragment green = { 0.0f,0.39f,0.0f };
	Fragment white = { 0.8f,0.8f,0.8f };

	for (int i = 0; i < squares* squares; i++) {
		if (i % squares == 0) alternation = !alternation;

		switch (alternation) {
		case true:
			colors.push_back(green);
			colors.push_back(green);
			colors.push_back(green);
			colors.push_back(green);
			colors.push_back(green);
			colors.push_back(green);

			alternation = false;
			break;
		case false:
			colors.push_back(white);
			colors.push_back(white);
			colors.push_back(white);
			colors.push_back(white);
			colors.push_back(white);
			colors.push_back(white);

			alternation = true;
			break;
		}
	}

	return colors;
}

std::shared_ptr<Texture2D> ChessHelper::loadTexture(const std::string& textureName, const std::string& path) {
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!pixels) {
		std::cerr << "Can't load texture: " << path << std::endl;
		return nullptr;
	}

	std::shared_ptr<Texture2D> newTexture = textures.emplace(textureName, std::make_shared<Texture2D>(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);

	return newTexture;
}

std::shared_ptr<Texture2D> ChessHelper::getTexture(const std::string& textureName) {
	TextureMap::const_iterator it = textures.find(textureName);
	if (it != textures.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the texture: " << textureName << std::endl;
	return nullptr;
}