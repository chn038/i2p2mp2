#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/Group.hpp"
#include "Tower4.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int Tower4::Price = 100;
const int Tower4::Type = 4;
Tower4::Tower4(float x, float y, int damageOffset, int team) : Tower("play/tower-base.png", "play/turret-1.png", x, y, 64 * 3 + 32, Price, 2, damageOffset, team, Type)
{
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Tower4::CreateBullet()
{
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position + normalized * 36, diff, rotation, this, 6 + damageOffset));
    AudioHelper::PlayAudio("gun.wav");
}
