#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Turret/TurretButton.hpp"
#include "Team/Team.hpp"

class Turret;
namespace Engine {
	class Group;
	class Image;
	class Label;
	class Sprite;
}  // namespace Engine

class PlayScene final : public Engine::IScene {
private:
	ALLEGRO_SAMPLE_ID bgmId;
	void ReadMap();
	void ReadEnemyWave();
    void SpawnEnemy();
    void DeleteTurret(int x, int y);
    void BuildTurret(int x, int y);
	bool CheckSpaceValid(int x, int y);
	std::vector<std::vector<int>> CalculateBFSDistance();
protected:
    int damageOffset;
	int lives;
	int money;
	int SpeedMult;
public:
	static bool DebugMode;
	static const std::vector<Engine::Point> directions;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	static const float DangerTime;
	static const Engine::Point SpawnGridPoint;
	static const Engine::Point EndGridPoint;
	static const std::vector<int> code;
	int MapId;
	float ticks;
	// Map tiles.
	Group* TileMapGroup;
	Group* GroundEffectGroup;
	Group* DebugIndicatorGroup;
	Group* BulletGroup;
	Group* TowerGroup;
	Group* EnemyGroup;
	Group* EffectGroup;
	Group* UIGroup;
	Engine::Label* UIMoney;
	Engine::Label* UILives;
	Engine::Label* UIDamage;
	Engine::Image* imgTarget;
    TurretButton* updateButton;
	Turret* preview;
	std::vector<std::vector<Engine::TileType>> mapState;
    std::vector<std::vector<Engine::TileType>> originMap;
	std::vector<std::vector<int>> mapDistance;
	std::list<std::pair<int, float>> enemyWaveData;
	std::list<int> keyStrokes;
	static Engine::Point GetClientSize();
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
	void EarnMoney(int money);
	void ConstructUI();
	void UIBtnClicked(int id);
	// void ModifyReadMapTiles();
};
#endif // PLAYSCENE_HPP
