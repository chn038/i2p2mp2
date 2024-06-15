
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
// #include <utility>

#include "Enemy/Enemy.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IObject.hpp"
// #include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Instance.hpp"

PlayScene *Instance::getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Instance::Instance(std::string img, float x, float y, float radius, float speed, float hp, int money, int type, std::list<std::pair<bool, IObject *>> &TargetList) : Sprite(img, x, y), price(price), coolDown(coolDown), damageOffset(damageOffset), money(moeny), type(type), TargetList(TargetList), max_speed(speed)
{
    CollisionRadius = radius;
}

void Instance::Update(float deltaTime)
{
    // Pre-calculate the velocity.
    float remainSpeed = speed * deltaTime;
    while (remainSpeed != 0)
    {
        if (path.empty())
        {
            // Reach end point.
            Hit(hp);
            getPlayScene()->Hit();
            return;
        }
        Engine::Point target = path.back() * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2.0, PlayScene::BlockSize / 2.0);
        Engine::Point vec = target - Position;
        // Add up the distances:
        // 1. to path.back()
        // 2. path.back() to border
        // 3. All intermediate block size
        // 4. to end point
        // reachEndTime = (vec.Magnitude() + (path.size() - 1) * PlayScene::BlockSize - remainSpeed) / speed;
        Engine::Point normalized = vec.Normalize();
        if (remainSpeed - vec.Magnitude() > 0)
        {
            Position = target;
            path.pop_back();
            remainSpeed -= vec.Magnitude();
        }
        else
        {
            Velocity = normalized * remainSpeed / deltaTime;
            remainSpeed = 0;
        }
    }
    Rotation = atan2(Velocity.y, Velocity.x);
    Sprite::Update(deltaTime);
    PlayScene *scene = getPlayScene();
    imgBase.Position = Position;
    imgBase.Tint = Tint;
    if (Target)
    {
        if (speed != 0)
            speed = 0;
        Engine::Point diff = Target->Position - Position;
        if (diff.Magnitude() > CollisionRadius)
        {
            Target->lockedTowers.erase(lockedTowerIterator);
            Target = nullptr;
            lockedTowerIterator = std::list<Tower *>::iterator();
        }
    }
    if (!Target)
    {
        if (speed == 0)
            speed = max_speed;
        // Lock first seen target.
        // Can be improved by Spatial Hash, Quad Tree, ...
        // However simply loop through all enemies is enough for this program.
        for (auto &it : TargetList)
        {
            Engine::Point diff = it.second->Position - Position;
            if (diff.Magnitude() <= CollisionRadius)
            {
                Target = dynamic_cast<Instance *>(it.second);
                Target->lockedTowers.push_back(this);
                lockedTowerIterator = std::prev(Target->lockedTowers.end());
                break;
            }
        }
    }
    if (Target)
    {
        if (speed != 0)
            speed = 0;
        Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
        Engine::Point targetRotation = (Target->Position - Position).Normalize();
        float maxRotateRadian = rotateRadian * deltaTime;
        float cosTheta = originRotation.Dot(targetRotation);
        // Might have floating-point precision error.
        if (cosTheta > 1)
            cosTheta = 1;
        else if (cosTheta < -1)
            cosTheta = -1;
        float radian = acos(cosTheta);
        Engine::Point rotation;
        if (abs(radian) <= maxRotateRadian)
            rotation = targetRotation;
        else
            rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
        // Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
        Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
        // Shoot reload.
        reload -= deltaTime;
        if (reload <= 0)
        {
            // shoot.
            reload = coolDown;
            CreateBullet();
        }
    }
}

void Instance::OnExplode()
{
    getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
    for (int i = 0; i < 10; i++)
    {
        // Random add 10 dirty effects.
        getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
    }
}

void Instance::Hit(float damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        OnExplode();
        // Remove all turret's reference to target.
        for (auto &it : lockedTowers)
            it->Target = nullptr;
        for (auto &it : lockedTowers)
            it->Target = nullptr;
        getPlayScene()->EarnMoney(money, type);
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}

void Instance::UpdatePath(const std::vector<std::vector<int>> &mapDistance, Engine::Point endpoint)
{
    static const Engine::Point directions[4] = {Engine::Point(0, -1), Engine::Point(-1, 0), Engine::Point(1, 0), Engine(0, 1)};
    int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
    if (x < 0)
        x = 0;
    if (x >= PlayScene::MapWidth)
        x = PlayScene::MapWidth - 1;
    if (y < 0)
        y = 0;
    if (y >= PlayScene::MapHeight)
        y = PlayScene::MapHeight - 1;
    Engine::Point pos(x, y);
    int num = mapDistance[y][x];
    if (num == -1)
    {
        num = 0;
        Engine::LOG(Engine::ERROR) << "Enemy path finding error";
    }
    path = std::vector<Engine::Point>(num + 1);
    while (num != 0)
    {
        std::vector<Engine::Point> nextHops;
        for (auto &dir : directions)
        {
            int x = pos.x + dir.x;
            int y = pos.y + dir.y;
            if (x < 0 || x >= PlayScene::MapWidth || y < 0 || y >= PlayScene::MapHeight || mapDistance[y][x] != num - 1)
                continue;
            nextHops.emplace_back(x, y);
        }
        // Choose arbitrary one.
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, nextHops.size() - 1);
        pos = nextHops[dist(rng)];
        path[num] = pos;
        num--;
    }
    path[0] = endpoint;
}

void Instance::Draw() const
{
    Sprite::Draw();
    if (PlayScene::DebugMode)
    {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
    }
}
