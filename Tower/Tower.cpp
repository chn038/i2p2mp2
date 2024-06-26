#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>

#include "Instance/Instance.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/IObject.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Tower.hpp"

PlayScene *Tower::getPlayScene()
{
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Tower::Tower(std::string imgBase, 
             std::string imgTower, 
             float x,
             float y,
             float radius,
             int price,
             float coolDown,
             int damageOffset,
             std::list<std::pair<bool, IObject *>> &FlyTarget,
             std::list<std::pair<bool, IObject *>> &GroundTarget,
             ALLEGRO_COLOR color)
    :Sprite(imgTower, x, y),
    price(price),
    coolDown(coolDown),
    imgBase(imgBase, x, y),
    damageOffset(damageOffset),
    FlyTarget(FlyTarget),
    GroundTarget(GroundTarget),
    barRatio(0), barColor(color) {
    CollisionRadius = radius;
}

void Tower::UpgradeDamage(int toDamage) {
    this->damageOffset = toDamage;
}

void Tower::Draw() const {
    imgBase.Draw();
    Sprite::Draw();
    if (PlayScene::DebugMode)
    {
        // Draw target radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);
    }
    Engine::Point barP = Engine::Point(Position.x - 0.5*GetBitmapWidth(), Position.y - 0.5*GetBitmapHeight());
    al_draw_filled_rectangle(barP.x, barP.y, barP.x + GetBitmapWidth(), barP.y + 8, al_map_rgb(0, 0, 0));
    al_draw_filled_rectangle(barP.x, barP.y, barP.x + barRatio * GetBitmapWidth(), barP.y + 8, barColor);
}

int Tower::GetPrice() const {
    return this->price;
}

void Tower::SearchTarget() {
    // Lock first seen target.
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    Target = nullptr;
    for (auto &it : FlyTarget) {
        Engine::Point diff = it.second->Position - Position;
        if (diff.Magnitude() <= CollisionRadius) {
            Target = dynamic_cast<Instance *>(it.second);
            break;
        }
    }
    if (Target) return;

    for (auto &it : GroundTarget) {
        Engine::Point diff = it.second->Position - Position;
        if (diff.Magnitude() <= CollisionRadius) {
            Target = dynamic_cast<Instance *>(it.second);
            break;
        }
    }
}

void Tower::Update(float deltaTime) {
    // no moving when shooting
    Sprite::Update(deltaTime);
    PlayScene *scene = getPlayScene();
    imgBase.Position = Position;
    imgBase.Tint = Tint;
    if (!Enabled)
        return;
    SearchTarget();
    if (Target) {
        Engine::Point targetRotation = (Target->Position - Position).Normalize();
        /*
            Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
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
            */
        Rotation = atan2(targetRotation.y, targetRotation.x) + ALLEGRO_PI/2;
    }
    // Shoot reload.
    if (reload <= 0) {
        if (Target) {
            // shoot.
            reload = coolDown;
            CreateBullet();
        }
    } else {
        reload -= deltaTime;
    }
}
