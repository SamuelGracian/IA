#pragma once 

struct FleeObjective
{
    bool isActive = false;
    float fleeForce = 0.0f;
    float radius = 0.0f;
    sf::Vector2f target = { 0.0f, 0.0f };
    sf::Vector2f Position = { 0.0f, 0.0f };

};