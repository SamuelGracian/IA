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

const float Obstacles::GetRadius () const
{
	return m_radius;
}

const sf::Color Obstacles::GetColor() const
{
	return m_color;
}

const sf::Vector2f Obstacles::GetPosition() const
{
	return m_position;
}