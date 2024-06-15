#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Bullet1.hpp"
#include "Engine/Group.hpp"
#include "Tower1.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int Tower1::Price = 50;
const int Tower1::Type = 1;
Tower1::Tower1(float x, float y, int damageOffset, int team) : Tower("play/tower-base.png", "play/turret-1.png", x, y, 64 + 32, Price, 1, damageOffset, team, Type)
{
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Tower1::CreateBullet()
{
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Bullet1(Position + normalized * 36, diff, rotation, this, 2 + damageOffset));
    AudioHelper::PlayAudio("gun.wav");
}
