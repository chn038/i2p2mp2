#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Bullet/Bullet3.hpp"
#include "Engine/Group.hpp"
#include "Tower/Tower3.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Instance/Instance3.hpp"

const int Tower3::Price = 100;
const int Tower3::spawnPeriod = 12;

Tower3::Tower3(float x, float y, Team *team) : Tower("play/tower-base.png", "play/turret-3.png", x, y, 64 * 3 + 32, Price, 0.5,
                                                     team->damageOffset,
                                                     team->GetOpponent()->FlyGroup->GetObjects(),
                                                     team->GetOpponent()->GroundGroup->GetObjects()),
                                               team(team)
{
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Tower3::CreateBullet()
{
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Bullet3(Position + normalized * 36, diff, rotation, this, 2 + damageOffset, FlyTarget, GroundTarget));
    AudioHelper::PlayAudio("gun.wav");
}

void Tower3::Update(float deltaTime)
{
    Tower::Update(deltaTime);
    ticks += deltaTime;
    if (ticks > spawnPeriod)
    {
        barRatio = 1;
    }
    else
    {
        barRatio = ticks / spawnPeriod;
    }
    if (ticks < spawnPeriod)
        return;
    ticks -= spawnPeriod;

    Engine::Point sp = SearchPlace();
    if (sp.x == -1)
        return;

    const int blockSize = getPlayScene()->BlockSize;

    float objx = (sp.x + 0.5) * blockSize;
    float objy = (sp.y + 0.5) * blockSize;
    Instance *n = new Instance3(objx, objy, team->ID, team->damageOffset, FlyTarget, GroundTarget);
    n->UpdatePath(team->groundMap, team->endPoint);
    team->GroundGroup->AddNewObject(n);
}

static PlayScene *getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Engine::Point Tower3::SearchPlace()
{
    static const Engine::Point direction[4] = {
        Engine::Point(1, 0), Engine::Point(-1, 0),
        Engine::Point(0, -1), Engine::Point(0, 1)};

    const int blockSize = getPlayScene()->BlockSize;
    Engine::Point current = Engine::Point(Position.x / blockSize, Position.y / blockSize);
    Engine::Point np;
    for (int i = 0; i < 4; ++i)
    {
        np = current + direction[i];
        if (getPlayScene()->mapState[np.y][np.x] == Engine::TILE_DIRT)
        {
            return np;
        }
    }
    return Engine::Point(-1, -1);
}
