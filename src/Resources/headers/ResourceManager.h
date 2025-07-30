#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ResourceManager {
public:
	std::string readShaderCode(const std::string& path);
};