#ifndef __TOWER_INDICATOR__
#define __TOWER_INDICATOR__

#include "Engine/Sprite.hpp"

namespace Engine {
    class IObject;
    class Point;
};

class TowerIndicator final : public Engine::IObject {
public:
    /// @param(type)
    /// type is used to decide what to do after being pressed
    int type;
    float radius;
    int price;
    Engine::Sprite base;
    Engine::Sprite top;
    TowerIndicator(Engine::Sprite Base, Engine::Sprite Top, float radius, int price, int type, float x, float y, float w = 0, float h = 0);
    void Draw() const override;
    void SetPos(Engine::Point);
    void SetTint(ALLEGRO_COLOR filter);
};

#endif
