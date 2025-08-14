#include "world.h"
#include "Boid.h"
#include <SFML/Graphics.hpp>

World::World(const std::string background) 
{
    SetTexture(background);
    m_background.setTexture(&m_texture);
}

void World::AddBoid(const Boid& boid) {
    m_boidsVector.push_back(boid);
}

void World::AddObstacle(const Obstacles& obstacle) {
    m_obstaclesVector.push_back(obstacle);
}

void World::Update() 
{
    for (auto& obstacle : m_obstaclesVector) 
    {
        obstacle.Update();
    }

    std::vector<Obstacles> obstacles;
    for (const auto& obstacle : m_obstaclesVector) 
    {
        obstacles.push_back(Obstacles{obstacle.GetPosition(), obstacle.GetColor(), obstacle.GetRadius()});
    }

    for (auto& boid : m_boidsVector) 
    {
        boid.AddObstacles(&obstacles);
        boid.Update();
    }
}

void World::Create()
{
    //Set vector size
    m_boidsVector.resize(4);

    Boid& boid = m_boidsVector[0];

    boid.SetPosition(sf::Vector2f(500.0f, 500.0f));
    boid.SetTexture("DespairFrog.png");

    Path path;
    path.waypoints = {
    { 120.0f, 120.0f },
    { 200.0f, 200.0f },
    { 300.0f, 100.0f },
    { 400.0f, 300.0f },
    { 500.0f, 200.0f },
    { 700.0f, 300.0f}
    };
    path.ActivePath = true;
    path.radius = 30.0f;
    path.FollowForce = 10.0f;
    path.ActiveLoop = true;

    boid.ActiveFollowPatch(path);
}

void World::Render(sf::RenderTarget* window)
{

    window->draw(m_background);


    for (auto& boid : m_boidsVector)
    {
        sf::CircleShape circleShape;
        circleShape.setRadius(boid.GetRadius());
        circleShape.setFillColor(boid.GetColor());
        circleShape.setTexture(boid.GetTexture());
        circleShape.setPosition(boid.GetPosition());
        window->draw(circleShape);
    }


    for (auto& obst : m_obstaclesVector)
    {
        sf::CircleShape obstacleshape;
        obstacleshape.setRadius(obst.GetRadius());
        obstacleshape.setOrigin(sf::Vector2f(obst.GetRadius(), obst.GetRadius()));
        obstacleshape.setPosition(obst.GetPosition());
        obstacleshape.setFillColor(obst.GetColor());
        window->draw(obstacleshape);
    }
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