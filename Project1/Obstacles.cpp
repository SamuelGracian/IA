#include "Obstacles.h"

#include <iostream>

void Obstacles::SetTexture(const std::string file)
{
	if (!m_texture.loadFromFile(file))
	{
		std::cerr << "Error loading image: " << file << std::endl;
		return;
	}
}