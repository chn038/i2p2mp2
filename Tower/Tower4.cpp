#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Bullet/Bullet3.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Tower/Tower4.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Instance/Instance4.hpp"

const int Tower4::Price = 100;
const int Tower4::spawnPeriod = 15;

Tower4::Tower4(float x, float y, Team *team) : Tower("play/tower-base.png", "play/turret-4.png", x, y, 64 * 3 + 32, Price, 2,
                                                     team->damageOffset,
                                                     team->GetOpponent()->FlyGroup->GetObjects(),
                                                     team->GetOpponent()->GroundGroup->GetObjects()),
                                               team(team)
{
}

void Tower4::CreateBullet()
{
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Bullet3(Position + normalized * 36, diff, rotation, this, 6 + damageOffset, FlyTarget, GroundTarget));
    AudioHelper::PlayAudio("gun.wav");
}

void Tower4::Update(float deltaTime)
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
    Instance *n = new Instance4(objx, objy, team->ID, team->damageOffset, FlyTarget, GroundTarget);
    n->UpdatePath(team->flyMap, team->endPoint);
    team->FlyGroup->AddNewObject(n);
}

static PlayScene *getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Engine::Point Tower4::SearchPlace()
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
