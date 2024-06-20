#include <allegro5/color.h>

#include "Engine/GameEngine.hpp"
#include "Scene/PlayScene.hpp"
#include "UI/Component/Label.hpp"
#include "TowerButton.hpp"

PlayScene* TowerButton::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
TowerButton::TowerButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Tower, Engine::Label Price, float x, float y, int money) :
	ImageButton(img, imgIn, x, y), money(money), Base(Base), Tower(Tower), Price(Price) {
}
void TowerButton::Update(float deltaTime) {
	ImageButton::Update(deltaTime);
	if (getPlayScene()->GetMoney() >= money) {
		Enabled = true;
		Base.Tint = Tower.Tint = al_map_rgba(255, 255, 255, 255);
	} else {
		Enabled = false;
		Base.Tint = Tower.Tint = al_map_rgba(0, 0, 0, 160);
	}
}
void TowerButton::Draw() const {
	ImageButton::Draw();
	Base.Draw();
	Tower.Draw();
    Price.Draw();
}
