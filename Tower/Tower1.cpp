#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Bullet/Bullet3.hpp"
#include "Engine/Group.hpp"
#include "Tower1.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Instance/Instance1.hpp"

const int Tower1::Price = 50;
const int Tower1::spawnPeriod = 5;

Tower1::Tower1(float x, float y, Team *team) : Tower("play/tower-base.png", "play/turret-1.png", x, y, 64 + 32, Price, 1,
                                                     team->damageOffset,
                                                     team->GetOpponent()->FlyGroup->GetObjects(),
                                                     team->GetOpponent()->GroundGroup->GetObjects()),
                                               team(team)
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
    getPlayScene()->BulletGroup->AddNewObject(new Bullet3(Position + normalized * 36, diff, rotation, this, 2 + damageOffset, FlyTarget, GroundTarget));
    AudioHelper::PlayAudio("gun.wav");
}

void Tower1::Update(float deltaTime)
{
    Tower::Update(deltaTime);
    ticks += deltaTime;
    if (ticks > spawnPeriod)
    {
        ratio = 1;
    }
    else
    {
        ratio = ticks / spawnPeriod;
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
    Instance *n = new Instance1(objx, objy, team->ID, FlyTarget, GroundTarget);
    n->UpdatePath(team->groundMap, team->endPoint);
    team->GroundGroup->AddNewObject(n);
}

PlayScene *getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Engine::Point Tower1::SearchPlace()
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
