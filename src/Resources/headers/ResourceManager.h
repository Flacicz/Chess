#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "../../Graphics/headers/Texture.h"
#include "../../Graphics/headers/Sprite.h"
#include "Figures.h"

class ResourceManager {
public:
	std::string readShaderCode(const std::string& path);

	std::shared_ptr<ShaderProgram> loadShaderProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<ShaderProgram> getShaderProgram(const std::string& name);

	void loadTexture(const std::string& name, const std::string& path);
	void loadFiguresTexture(const std::string& path);
	std::shared_ptr<Texture> getTexture(const std::string& name);

	std::shared_ptr<Sprite> loadSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderProgramName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight);
	std::shared_ptr<Sprite> getSprite(const std::string& name);
private:
	typedef std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramMap;
	static ShaderProgramMap shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Texture>> TextureMap;
	static TextureMap textures;

	typedef std::map<const std::string, std::shared_ptr<Sprite>> SpriteMap;
	static SpriteMap sprites;
};