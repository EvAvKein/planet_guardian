#include "planet_guardian.h"
#include <stdio.h>
Vector2 moveTowardsWithGravity(Vector2 current, Vector2 direction, int speed, Vector2 planetCenter)
{
    // Normalize input direction
    if (Vector2Length(direction) > 0.001f)
        direction = Vector2Normalize(direction);
    else
        return direction;

    // Direction and distance to planet center
    Vector2 toPlanet = Vector2Subtract(planetCenter, current);
    float distance = Vector2Length(toPlanet);

    // Normalize and apply gravity (simple proportional pull)
    float gravityStrength = 1.0f / (distance * 0.9f); // Adjust 0.1f to control gravity intensity
    Vector2 gravityPull = Vector2Scale(Vector2Normalize(toPlanet), gravityStrength);  // Tune 0.001f as needed

    // Combine direction and gravity
    Vector2 moveDir = Vector2Add(direction, gravityPull);
    moveDir = Vector2Normalize(moveDir);
    moveDir = Vector2Scale(moveDir, speed);

    return Vector2Add(current, moveDir);
}


Vector2 generateRandomDir(Vector2 current)
{
     // Generate random target position
    Vector2 target = 
    {
        rand() % GetScreenWidth(),
        rand() % GetScreenHeight()
    };

    Vector2 direction = Vector2Subtract(target, current);
    return direction;
}


Vector2 generateAsteroidPos()
{
    int edge = rand() % 4;
    Vector2 position;

    switch (edge)
    {
        case 0:
            position.x = (float)(rand() % GetScreenWidth());
            position.y = -50;
            break;
        case 1:
            position.x = GetScreenWidth() + 50;
            position.y = (float)(rand() % GetScreenHeight());
            break;
        case 2:
            position.x = (float)(rand() % GetScreenWidth());
            position.y = GetScreenHeight() + 50;
            break;
        case 3:
            position.x = -50;
            position.y = (float)(rand() % GetScreenHeight());
            break;
    }

    return position;
}
