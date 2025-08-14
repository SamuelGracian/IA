#pragma once
#include "Boid.h"
#include "Obstacles.h"
#include "Path.h"
#include "SeekObjective.h"
#include "FleeObjective.h"


class World
{
public:
    World(const std::string background);
    ~World() = default;

    void Create();

    void Render(sf::RenderTarget* window);
    void Update(); 

    private:
    void SetTexture(const std::string file);

    void AddBoid(const Boid& boid);

    void AddObstacle(const Obstacles& obstacle);

private:
    std::vector<Boid> m_boidsVector;
    std::vector<Obstacles> m_obstaclesVector;

    sf::RectangleShape m_background;
    sf::Texture m_texture;
};

