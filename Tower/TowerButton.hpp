#ifndef TURRETBUTTON_HPP
#define TURRETBUTTON_HPP
#include <string>

#include "UI/Component/ImageButton.hpp"
#include "Engine/Sprite.hpp"
#include "UI/Component/Label.hpp"

class PlayScene;

class TowerButton : public Engine::ImageButton {
protected:
    PlayScene* getPlayScene();
public:
	int money;
	Engine::Sprite Base;
	Engine::Sprite Tower;
    Engine::Label Price;
	TowerButton(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Turret, Engine::Label Price, float x, float y, int money);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // TURRETBUTTON_HPP
