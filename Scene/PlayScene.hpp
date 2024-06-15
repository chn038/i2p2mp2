#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Team/Team.hpp"

class Tower;
namespace Engine {
	class Group;
	class Image;
	class Label;
	class Sprite;
}  // namespace Engine

class PlayScene final : public Engine::IScene {
private:
	void ReadMap();
	void ReadEnemyWave();
    void SpawnEnemy();
	bool CheckSpaceValid(int x, int y);
	void UIBtnClicked(int id);
	static Engine::Point GetClientSize();
	void ConstructUI();
protected:
	ALLEGRO_SAMPLE_ID bgmId;
	int SpeedMult;
    Team *teamA;
    Team *teamB;
	std::list<int> keyStrokes;
	static const std::vector<int> code;
	static bool DebugMode;
	float ticks;
public:
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	int MapId;
	// Map tiles.
	Group* TileMapGroup;
	Group* GroundEffectGroup;
	Group* DebugIndicatorGroup;
	Group* BulletGroup;
	Group* EffectGroup;
	Group* UIGroup;
    Tower* preview;
	Engine::Label* UIMoney;
	Engine::Label* UILives;
	Engine::Label* UIDamage;
	Engine::Image* imgTarget;
	std::vector<std::vector<Engine::TileType>> mapState;
    std::vector<std::vector<Engine::TileType>> originMap;
	explicit PlayScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
	void Hit();
	int GetMoney() const;
	void EarnMoney(int money, int id);
};
#endif // PLAYSCENE_HPP
