#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
struct Path
{
    std::vector<sf::Vector2f> waypoints;
    float radius = 10.0f;
    bool ActivePath;
    bool ActiveLoop;
    float FollowForce = 0.0f;
};