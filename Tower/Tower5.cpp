#include <allegro5/base.h>
#include <string>

#include "Engine/GameEngine.hpp"
#include "Bullet/Bullet3.hpp"
#include "Engine/Group.hpp"
#include "Tower/Tower5.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Instance/Instance5.hpp"
#include "Instance/Instance6.hpp"

const int Tower5::Price = 150;
const int Tower5::spawnPeriod = 12;

Tower5::Tower5(float x, float y, Team *team) : Tower("play/tower-base.png", "play/turret-5.png", x, y, 32, Price, 5,
                                                     team->damageOffset,
                                                     team->GetOpponent()->FlyGroup->GetObjects(),
                                                     team->GetOpponent()->GroundGroup->GetObjects()),
                                               team(team), ticks(0)
{
}

void Tower5::CreateBullet()
{
    return;
}

void Tower5::Update(float deltaTime)
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

    float objx = sp.x * blockSize;
    float objy = sp.y * blockSize;
    Instance *n = new Instance5(objx, objy, team->ID, team->damageOffset, FlyTarget, GroundTarget);
    n->UpdatePath(team->groundMap, team->endPoint);
    team->GroundGroup->AddNewObject(n);
    n = new Instance6(objx, objy, team->ID, team->damageOffset, FlyTarget, GroundTarget);
    n->UpdatePath(team->flyMap, team->endPoint);
    team->FlyGroup->AddNewObject(n);
}

static PlayScene *getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Engine::Point Tower5::SearchPlace()
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
