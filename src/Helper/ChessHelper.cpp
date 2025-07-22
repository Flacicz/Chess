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

void ChessHelper::loadTexture(const std::string& path) {
	int parts = 12;

	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!pixels) {
		std::cerr << "Can't load texture: " << path << std::endl;
	}

	std::vector<std::unique_ptr<unsigned char[]>> parts_data = sliceTexture(pixels, width, height, channels, parts);

	for (int i = 0; i < parts; i++) {
		textures.emplace(Figures::convertToString(Figures::Figures(i)), std::make_shared<Texture2D>(
			width / parts,
			height,
			i,
			parts_data[i].get(),
			channels,
			GL_NEAREST,
			GL_CLAMP_TO_EDGE)
		);
	}

	stbi_image_free(pixels);
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

std::vector<std::unique_ptr<unsigned char[]>> ChessHelper::sliceTexture(unsigned char* data, int width, int height, int channels, int parts) {
	std::vector<std::unique_ptr<unsigned char[]>> parts_data;
	int interval = width / parts;
	int startX, startY;
	startY = 0;

	for (int i = 0; i < parts; i++) {
		startX = i * interval;

		auto part_data = std::make_unique<unsigned char[]>(static_cast<size_t>(interval) * height * channels);

		for (int row = 0; row < height; row++) {
			for (int col = 0; col < interval; col++) {
				int src_index = ((row + startY) * width + (col + startX)) * channels;
				int dest_index = (row * interval + col) * channels;

				for (int ch = 0; ch < channels; ch++) {
					part_data[static_cast<size_t>(dest_index) + ch] = data[src_index + ch];
				}
			}
		}

		parts_data.push_back(std::move(part_data));
	}

	return parts_data;
}