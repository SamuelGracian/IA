#pragma once

#include "VectorFloat.h"

class Boid
{
public:
    Boid() = default;
    virtual ~Boid() = default;

    Vector2f Seek(  const Vector2f& position,
                    const Vector3f& target,
                    float seekforce);

    void Update()

private:

    Vector2f m_position;
    Vector2f m_direction;
};