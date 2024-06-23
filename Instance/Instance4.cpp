#include "Instance4.hpp"
#include "Engine/AudioHelper.hpp"
#include "Scene/PlayScene.hpp"
#include "Bullet/Bullet2.hpp"
#include <cmath>

Instance4::Instance4(float x, float y, int team, int damageOffset,
                     std::list<std::pair<bool, IObject *>> &FlyTarget,
                     std::list<std::pair<bool, IObject *>> &GroundTarget,
                     ALLEGRO_COLOR teamColor)
    : Instance("instance/instance4.png", x, y, 64 * 3 + 32, 32, 20, 50, 10, team, false, 0.5, damageOffset, FlyTarget, GroundTarget, teamColor)
{
}

void Instance4::CreateBullet()
{
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Bullet2(Position, diff, rotation, this, 2 + damageOffset, FlyTarget, GroundTarget));
    AudioHelper::PlayAudio("gun.wav");
}

void Instance4::SearchTarget()
{
    // Lock first seen target.
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    Target = nullptr;
    for (auto &it : GroundTarget)
    {
        Engine::Point diff = it.second->Position - Position;
        if (diff.Magnitude() <= CollisionRadius)
        {
            Target = dynamic_cast<Instance *>(it.second);
            break;
        }
    }
}
