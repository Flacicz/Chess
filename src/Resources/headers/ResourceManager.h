#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include "../../Graphics/headers/Texture.h"

class ResourceManager {
public:
	std::string readShaderCode(const std::string& path);
	void loadTexture(const std::string& name, const std::string& path);
	std::shared_ptr<Texture> getTexture(const std::string& name);
private:
	typedef std::map<const std::string, std::shared_ptr<Texture>> TextureMap;
	static TextureMap textures;
};