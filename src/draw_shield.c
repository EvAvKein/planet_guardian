#include "planet_guardian.h"

void draw_shield(float angle)
{
    float orbitRadius = game.planet.radius + 50.0f;
    Vector2 center = game.planet.center_pos;

    // Calculate position along orbit (center of shield)
    Vector2 shieldCenterPos = {
        center.x + cosf(angle) * orbitRadius,
        center.y + sinf(angle) * orbitRadius
    };

    Rectangle sourceRec = {0, 0, (float)game.shield.sprite.texture.width,
                           (float)game.shield.sprite.texture.height};
    Rectangle destRec = {shieldCenterPos.x, shieldCenterPos.y,
                        (float)game.shield.sprite.texture.width,
                        (float)game.shield.sprite.texture.height};
    Vector2 origin = {(float)game.shield.sprite.texture.width / 2.0f,
                      (float)game.shield.sprite.texture.height / 2.0f};

    float shieldRotation = angle * RAD2DEG + 90.0f;

    DrawTexturePro(game.shield.sprite.texture, sourceRec, destRec, origin,
                   shieldRotation, WHITE);
}
