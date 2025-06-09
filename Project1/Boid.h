#pragma once
#include <SFML/Graphics.hpp>

#include "VectorFloat.h"

/// <summary>
/// Struct to hold seek objective data.
/// Esta es aquien persigue
/// </summary>
struct SeekObjective
{
    bool isActive = false;
    Vector2f target = { 0.0f,0.0f };
    float seekforce = 0.0f;
    Vector2f Position = { 0.0f, 0.0f };
};

/// <summary>
/// Struct to hold flee objective data.
/// esta de quien huye
/// </summary>
struct FleeObjective
{
    bool isActive = false;
	Vector2f target = { 0.0f, 0.0f };
	float fleeForce = 0.0f;
    Vector2f Position = { 0.0f, 0.0f };
};


class Boid
{
public:
    Boid()
    {
		m_boidEntity.setRadius(10.0f);
    }

    virtual ~Boid() = default;

    void Update();

    void SetSeekObjective(SeekObjective& seek);

    void SetFleeObjective(FleeObjective& flee);

    void SetColor(sf::Color);

    sf::CircleShape& getShape();
    const sf::CircleShape& getShape() const;

private:

    //___________ Seek Behaviors ___________
    Vector2f Seek(const Vector2f& position,
        const Vector2f& target,
        float seekforce); const

        Vector2f Flee(const Vector2f& position,
            const Vector2f& target,
            float fleeForce);

    void Wander(float wanderForce);

    void Arrive(const Vector2f& target, float slowRadius);


	//___________ Boid Properties ___________
    Vector2f m_position;
    Vector2f m_direction;

	//___________ Seek Objectives ___________
	SeekObjective m_seekObjective;
	FleeObjective m_fleeObjective;

    sf::CircleShape m_boidEntity;
};


