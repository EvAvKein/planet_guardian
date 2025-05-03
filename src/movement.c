#include "planet_guardian.h"
#include <stdio.h>
Vector2 moveTowardsWithGravity(Vector2 current, Vector2 direction, int speed, Vector2 planetCenter)
{
    // Direction and distance to planet center
    Vector2 toPlanet = Vector2Subtract(planetCenter, current);
    float distance = Vector2Length(toPlanet);

    printf("Planetcenter %f, %f\n", planetCenter.x, planetCenter.y);

    // Normalize and apply gravity (simple proportional pull)
    float gravityStrength = 1.0f / (distance * GRAVITYPULL_SCALE); // Adjust 0.1f to control gravity intensity
    printf("gravityStrength, %f \n", gravityStrength);
    Vector2 gravityPull = Vector2Scale(Vector2Normalize(toPlanet), gravityStrength);  // Tune 0.001f as needed

    printf("gravity pull %f, %f\n", gravityPull.x, gravityPull.y);
    // Combine direction and gravity
    Vector2 moveDir = Vector2Add(direction, gravityPull);
    moveDir = Vector2Scale(moveDir, speed);
    moveDir = Vector2Normalize(moveDir);

    printf("movedir %f, %f\n", moveDir.x, moveDir.y);
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

    // Keep the asteroid just off the edge by a small amount (e.g., 10-20 pixels)
    float edgeMargin = 20; // Adjust as needed

    switch (edge)
    {
        case 0: // Top edge
            position.x = (float)(rand() % GetScreenWidth());
            position.y = -edgeMargin; // Just above the top edge
            break;
        case 1: // Right edge
            position.x = GetScreenWidth() + edgeMargin; // Just beyond the right edge
            position.y = (float)(rand() % GetScreenHeight());
            break;
        case 2: // Bottom edge
            position.x = (float)(rand() % GetScreenWidth());
            position.y = GetScreenHeight() + edgeMargin; // Just below the bottom edge
            break;
        case 3: // Left edge
            position.x = -edgeMargin; // Just beyond the left edge
            position.y = (float)(rand() % GetScreenHeight());
            break;
    }

    return position;
}
