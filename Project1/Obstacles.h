#pragma once
#include <SFML/Graphics.hpp>

class Obstacles
{
public:
	Obstacles(sf::Vector2f position, sf::Color color, float radius) :
		m_position(position), m_color(color), m_radius(radius)
	{}

	void Update();

	void SetTexture( const std::string file);

private:
	sf::Vector2f m_position;
	sf::Color m_color;
	sf::Texture m_texture;
	float m_radius;
};

