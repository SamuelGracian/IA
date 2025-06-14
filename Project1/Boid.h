#pragma once
#include <SFML/Graphics.hpp>

#include "VectorFloat.h"

/// <summary>
/// Struct to hold seek objective data.
/// </summary>
struct SeekObjective
{
    bool isActive = false;
    float seekforce = 0.0f;
    sf::Vector2f position = { 0.0f,0.0f };
    sf::Vector2f target = { 0.0f, 0.0f };

};

/// <summary>
/// Struct to hold flee objective data.
/// </summary>
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

    /// <summary>
	/// Sets the seek objective for the boid.
    /// </summary>
    /// <param name="seek"></param>
    void SetSeekObjective(SeekObjective& seek);

    /// <summary>
	/// Sets the flee objective for the boid.
    /// </summary>
    /// <param name="flee"></param>
    void SetFleeObjective(FleeObjective& flee);

    /// <summary>
	/// Sets the color of the boid entity.
    /// </summary>
    /// <param name=""></param>
    void SetColor(sf::Color);

    /// <summary>
	/// Sets the position of the boid in the world.
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(const sf::Vector2f& position);

    /// <summary>
	/// Returns the position of the boid in the world.
    /// </summary>
    /// <param name="vectorsfml"></param>
    /// <returns></returns>
    sf::Vector2f ConvertToVector2f(const sf::Vector2f& vectorsfml);

    sf::CircleShape getShape() const;

    void SetMass(float newMass);

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

    sf::Vector2f Patrol();

    sf::Vector2f PatrolLoop();


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


};

