#pragma once

#include "VectorFloat.h"

struct SeekObjective
{
    bool isActive = false;
    Vector2f target;
    float seekforce;
};

struct FleeObjective
{
	bool isActive = false;
	Vector2f target;
	float fleeForce;
};


class Boid
{
public:
    Boid() = default;
    virtual ~Boid() = default;

	//___________ Seek Behaviours ___________
    Vector2f Seek(const Vector2f& position,
        const Vector2f& target,
        float seekforce); const

     Vector2f Flee(const Vector2f& position,
         const Vector2f& target,
         float fleeForce);

    void Update();

    void SetSeekObjective(SeekObjective& seek);

    void SetFleeObjective(FleeObjective& flee);

private:
	//___________ Boid Properties ___________
    Vector2f m_position;
    Vector2f m_direction;

	//___________ Seek Objectives ___________
	SeekObjective m_seekObjective;
	FleeObjective m_fleeObjective;
};