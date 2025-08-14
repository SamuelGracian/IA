#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Path.h"
#include "Obstacles.h"
#include "SeekObjective.h"
#include "FleeObjective.h"
#include "VectorFloat.h"


class Boid
{
public:
    Boid()
    {
        SetRandomDirection();
        m_maxSpeed = 1.0f + float ((rand() % 10) / 10.0f);
    }

    virtual ~Boid() = default;

    void Update();

    void SetSeekObjective(SeekObjective& seek);

    void SetFleeObjective(FleeObjective& flee);

    void ActiveFollowPatch(Path& path);

    void SetColor(sf::Color);

    void SetPosition(const sf::Vector2f& position);

    void SetPointer(std::vector<Boid>* pointervector);

    //sf::CircleShape getShape() const;

    void SetMass(float newMass);

    sf::Vector2f FollowPath( sf::Vector2f position , const Path &path, size_t &currentWaypoint , float FollowForce);

    sf::Vector2f GetDirection();

    sf::Vector2f GetPosition();

    void SetTexture(const std::string imageFile);

    void AddObstacles(std::vector<Obstacles>* obstpointer);

    float GetRadius();

    sf::Color GetColor();

    sf::Texture* GetTexture();

private:

    void SetRandomDirection();
    //___________ Seek Behaviors ___________
    sf::Vector2f Seek(const sf::Vector2f& position,
        const sf::Vector2f& target,
        float seekforce); const

        sf::Vector2f Flee(const sf::Vector2f& position,
        const sf::Vector2f& target,
        float radus,
        float fleeForce);

    sf::Vector2f Wander(float wanderForce);

    void Arrive(const sf::Vector2f& target, float slowRadius);

    sf::Vector2f PatrolLoop(sf::Vector2f position, 
        const Path& path, 
        size_t& currentwaypoint, 
        float followforce);

    sf::Vector2f Direction(sf::Vector2f position, 
        std::vector <Boid>* world, 
        float distance, 
        float DirectionForce);

    sf::Vector2f Separation(std::vector <Boid>* world, float radius, float force);

    sf::Vector2f Cohesion(std::vector <Boid>* world, float radius, float force);

	sf::Vector2f ObstacleAvoidance(const std::vector<Obstacles>* obstacles, float avoidRadius, float force);


	//___________ Boid Properties ___________
    sf::Vector2f m_position = sf::Vector2f(0,0);
    sf::Vector2f m_sf_target;
    sf::Vector2f m_direction = sf::Vector2f(1,0) ;

    sf::Vector2f m_desired;

    float m_mass = 200;
    float m_radius = 10;
    float m_speed = 0.0f;
    float m_maxSpeed = 2.0f;
	//___________ Seek Objectives ___________
	SeekObjective m_seekObjective;
	FleeObjective m_fleeObjective;
	//___________ SFML variables ___________
	sf::Image m_image;
	sf::Texture m_texture;
    sf::Color m_color;

    //___________ Path _____________________
    Path m_path;
    size_t m_currentWaypoint;
    //__________ Follow Group ______________
    bool m_join;

    std::vector<Boid>* m_BoidVectorP = nullptr;

	std::vector<Obstacles>* m_obstacles = nullptr;

	//sf::CircleShape m_shape;
};

