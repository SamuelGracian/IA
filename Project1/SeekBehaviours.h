#pragma once
#include <vector>

#include "VectorFloat.h"

class SeekBehaviours
{
public:

	const void TwoDimensionSeeK(const std::vector<float>& PlayerPos,
        const std::vector<float>& EnemyPosition,
        std::vector<float>& Direction,
        float SF);

private:
	
};

class Boid
{
public:
    Boid() = default;
    virtual ~Boid() = default;



    Vector2f m_position;
    Vector2f m_direction;
};