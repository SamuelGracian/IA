#pragma once
#include"Boid.h"
#include "Obstacles.h"

class World
{
public:
	World(const std::string background);

	~World() = default;

	void Render(sf::RenderTarget* window);

	void SetTexture(const std::string file);

private:
	//Objects
	std::vector<Boid> m_boidsVector;
	std::vector<Obstacles> m_obstaclesVector;

	//background
	sf::RectangleShape m_background;
	sf::Texture m_texture;
};

