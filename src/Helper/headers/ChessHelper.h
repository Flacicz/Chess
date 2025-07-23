#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include <glad/glad.h>

#include "../../Render/headers/Texture2D.h"
#include "../../Render/headers/Sprite.h"
#include "../../Render/headers/ShaderProgram.h"
#include "FiguresName.h"


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

	std::shared_ptr<ShaderProgram> loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<ShaderProgram> getShader(const std::string& shaderName);

	void loadTexture(const std::string& path);
	std::shared_ptr<Texture2D> getTexture(const std::string& textureName);
	std::vector<std::unique_ptr<unsigned char[]>> sliceTexture(unsigned char* data,int width,int height,int channels,int parts);

	std::shared_ptr<Sprite> loadSprite(const std::string& spriteName,
									  const std::string& textureName,
									  const std::string& shaderName,
									  const unsigned int spriteWidth,		
									  const unsigned int spriteHeight);
	std::shared_ptr<Sprite> getSprite(const std::string& spriteName);
private:
	typedef std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramMap;
	static ShaderProgramMap shaders;

	typedef std::map<const std::string, std::shared_ptr<Texture2D>> TextureMap;
	static TextureMap textures;

	typedef std::map<const std::string, std::shared_ptr<Sprite>> SpriteMap;
	static SpriteMap sprites;
};