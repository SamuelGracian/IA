#pragma once
#include <SFML/Graphics.hpp>
struct SeekObjective
{
    bool isActive = false;
    float seekforce = 0.0f;
    float radius = 0.0f;
    sf::Vector2f position = { 0.0f,0.0f };
    sf::Vector2f target = { 0.0f, 0.0f };
};