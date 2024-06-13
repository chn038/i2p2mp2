#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/FireBullet.hpp"
#include "Engine/Group.hpp"
#include "Tower2.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int Tower2::Price = 50;
const int Tower2::Type = 2;
Tower2::Tower2(float x, float y, int damageOffset, int team) : Tower("play/tower-base.png", "play/turret-1.png", x, y, 64 * 2 + 32, Price, 1, damageOffset, team, Type)
{
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Tower2::CreateBullet()
{
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new FireBullet(Position + normalized * 36, diff, rotation, this, 1 + damageOffset));
    AudioHelper::PlayAudio("gun.wav");
}
