#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "VectorFloat.h"


struct Path 
{
    std::vector<sf::Vector2f> waypoints;
    float radius = 10.0f;
    bool ActivePath;
    bool ActiveLoop;
    float FollowForce = 0.0f;
};


struct SeekObjective
{
    bool isActive = false;
    float seekforce = 0.0f;
    float radius = 0.0f;
    sf::Vector2f position = { 0.0f,0.0f };
    sf::Vector2f target = { 0.0f, 0.0f };
};


struct FleeObjective
{
    bool isActive = false;
	float fleeForce = 0.0f;
    float radius = 0.0f;
	sf::Vector2f target = { 0.0f, 0.0f };
    sf::Vector2f Position = { 0.0f, 0.0f };

};

struct Wanders
{
    bool JoinGoup;
};

class Boid
{
public:
    Boid()
    {
		m_shape.setRadius(20.0f);
		m_shape.setFillColor(sf::Color::Green);
        SetRandomDirection();
        m_maxSpeed = 1.0f + float ((rand() % 10) / 10.0f);
    }

    virtual ~Boid() = default;

    void Update();

    void SetSeekObjective(SeekObjective& seek);

    void SetFleeObjective(FleeObjective& flee);

    void ActiveFollowPatch(Path& path);

    void ActiveJoin(Wanders& wander);

    void SetColor(sf::Color);

    void SetPosition(const sf::Vector2f& position);

    void SetPointer(std::vector<Boid>* pointervector);

    sf::CircleShape getShape() const;

    void SetMass(float newMass);

    sf::Vector2f FollowPath( sf::Vector2f position , const Path &path, size_t &currentWaypoint , float FollowForce);

    sf::Vector2f GetDirection();

    sf::Vector2f GetPosition();

    void SetImage(const std::string imageFile);

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

	sf::Vector2f Obstacleavoidance(std::vector <Boid>* world, float radius, float force);

	//___________ Boid Properties ___________
    sf::Vector2f m_position = sf::Vector2f(0,0);
    sf::Vector2f m_sf_target;
    sf::Vector2f m_direction = sf::Vector2f(1,0) ;

    sf::Vector2f m_desired;

    float m_mass = 200;
	int m_radius;
    float m_speed = 0.0f;
    float m_maxSpeed = 2.0f;
	//___________ Seek Objectives ___________
	SeekObjective m_seekObjective;
	FleeObjective m_fleeObjective;
	//___________ SFML variables ___________
    sf::CircleShape m_shape;
	sf::Image m_image;
	sf::Texture m_texture;

    //___________ Path _____________________
    Path m_path;
    size_t m_currentWaypoint;
    //__________ Follow Group ______________
    bool m_join;

    std::vector<Boid>* m_BoidVectorP;
};

