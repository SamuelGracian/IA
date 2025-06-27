#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "VectorFloat.h"


struct Path 
{
    std::vector<sf::Vector2f> waypoints;
    float radius = 10.0f; 
};


struct SeekObjective
{
    bool isActive = false;
    float seekforce = 0.0f;
    sf::Vector2f position = { 0.0f,0.0f };
    sf::Vector2f target = { 0.0f, 0.0f };

};


struct FleeObjective
{
    bool isActive = false;
	sf::Vector2f target = { 0.0f, 0.0f };
	float fleeForce = 0.0f;
    sf::Vector2f Position = { 0.0f, 0.0f };

};


class Boid
{
public:
    Boid()
    {
		m_shape.setRadius(20.0f);
		m_shape.setFillColor(sf::Color::Green);
    }

    virtual ~Boid() = default;

    void Update();

    void SetSeekObjective(SeekObjective& seek);

    void SetFleeObjective(FleeObjective& flee);


    void SetColor(sf::Color);

    void SetPosition(const sf::Vector2f& position);

    sf::Vector2f ConvertToVector2f(const sf::Vector2f& vectorsfml);

    sf::CircleShape getShape() const;

    void SetMass(float newMass);

    size_t m_currentWaypoint;

    sf::Vector2f FollowPath( sf::Vector2f position , const Path &path, size_t &currentWaypoint , float FollowForce);
private:

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

    sf::Vector2f PatrolLoop(sf::Vector2f position, const Path& path, size_t& currentwaypoint, float followforce);

	//___________ Boid Properties ___________
    sf::Vector2f m_position = sf::Vector2f(0,0);
    sf::Vector2f m_sf_target;
    sf::Vector2f m_direction = sf::Vector2f(1,0) ;

    sf::Vector2f m_desired;

    float m_mass = 1;

	//___________ Seek Objectives ___________
	SeekObjective m_seekObjective;
	FleeObjective m_fleeObjective;
	//___________ SFML variables ___________
    sf::CircleShape m_shape;


    //___________ Path __________________
};

