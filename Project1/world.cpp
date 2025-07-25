#include "world.h"
#include<iostream>

World::World(const std::string background)
{
	m_background.setSize(sf::Vector2f(1280, 1000));
	SetTexture(background);
}

void World::Render(sf::RenderTarget* window)
{
	
}

void World::SetTexture (const std::string file)
{
	if (!m_texture.loadFromFile(file))
	{
		std::cerr << "Error loading image: " << file << std::endl;
		return;
	}
	m_background.setTexture(&m_texture);
}