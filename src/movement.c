#include "planet_guardian.h"

Vector2 moveTowardsWithGravity(Vector2 current, Vector2 direction, int speed, Vector2 planetCenter)
{
    // Direction and distance to planet center
    Vector2 toPlanet = Vector2Subtract(planetCenter, current);
    float distance = Vector2Length(toPlanet);

    //printf("Planetcenter %f, %f\n", planetCenter.x, planetCenter.y);

    // Normalize and apply gravity (simple proportional pull)
    float gravityStrength = 1.0f / (distance * GRAVITYPULL_SCALE); // Adjust 0.1f to control gravity intensity
    //printf("gravityStrength, %f \n", gravityStrength);
    Vector2 gravityPull = Vector2Scale(Vector2Normalize(toPlanet), gravityStrength);  // Tune 0.001f as needed

    //printf("gravity pull %f, %f\n", gravityPull.x, gravityPull.y);
    // Combine direction and gravity
    Vector2 moveDir = Vector2Add(direction, gravityPull);
    moveDir = Vector2Normalize(moveDir);
    moveDir = Vector2Scale(moveDir, speed);

    //printf("movedir %f, %f\n", moveDir.x, moveDir.y);
    return Vector2Add(current, moveDir);
}


Vector2 generateRandomDir(Vector2 current)
{
    Vector2 center = game.planet.center_pos;
    float radius = game.planet.radius * DIRECTION_CIRCLE_SIZE_TIMES_PLANET;

    // Arvot kulman asteina 0–90 ja muunnetaan radiaaneiksi
    float randomAngle = ((float)rand() / (float)RAND_MAX) * 360.0f;
    float rad = randomAngle * DEG2RAD;

    // Laske satunnainen piste kaarelta
    Vector2 target = {
        center.x + radius * cosf(rad),
        center.y + radius * sinf(rad)
    };

    Vector2 direction = Vector2Subtract(target, current);
    return direction;
}



Vector2 generateAsteroidPos()
{
    int edge = GetRandomValue(0, 3);  // 0 = top, 1 = right, 2 = bottom, 3 = left
    Vector2 position;

    float edgeMargin = 50; // Puskurietäisyys ruudun ulkopuolelle

    switch (edge)
    {
        case 0: // Top
            position.x = (float)GetRandomValue(0, GetScreenWidth());
            position.y = -edgeMargin;
            break;
        case 1: // Right
            position.x = GetScreenWidth() + edgeMargin;
            position.y = (float)GetRandomValue(0, GetScreenHeight());
            break;
        case 2: // Bottom
            position.x = (float)GetRandomValue(0, GetScreenWidth());
            position.y = GetScreenHeight() + edgeMargin;
            break;
        case 3: // Left
            position.x = -edgeMargin;
            position.y = (float)GetRandomValue(0, GetScreenHeight());
            break;
    }
    return position;
}

