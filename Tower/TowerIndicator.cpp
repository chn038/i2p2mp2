#include <allegro5/allegro_primitives.h>
#include "TowerIndicator.hpp"

TowerIndicator::TowerIndicator( 
    Engine::Sprite Base, Engine::Sprite Top, 
    float radius, int price, int type, float x, float y, float w, float h)
    :type(type),
    price(price),
    radius(radius),
    base(Base),
    top(Top) {
}

void TowerIndicator::Draw() const {
    al_draw_filled_circle(Position.x, Position.y, radius, al_map_rgba(0, 255, 0, 50));
    base.Draw();
    top.Draw();
}

void TowerIndicator::SetPos(Engine::Point pos) {
    base.Position = pos;
    top.Position = pos;
}

void TowerIndicator::SetTint(ALLEGRO_COLOR filter) {
    base.Tint = filter;
    top.Tint = filter;
}
