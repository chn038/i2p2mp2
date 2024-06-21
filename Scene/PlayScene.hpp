#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <vector>
#include <queue>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Team/Team.hpp"
#include "Tower/TowerButton.hpp"
#include "Tower/TowerIndicator.hpp"

class Tower;
namespace Engine {
	class Group;
	class Image;
	class Label;
	class Sprite;
}  // namespace Engine

class PlayScene final : public Engine::IScene {
private:
    struct Wave {
        int time;
        int type;
        Engine::Point pos;
        Wave(int time, int type, Engine::Point pos)
        :time(time), type(type), pos(pos){}
    };
    std::queue<Wave> enemyWave;
	void ReadMap();
	void ReadEnemyWave();
	void UIBtnClicked(int id);
	void ConstructUI();
protected:
	ALLEGRO_SAMPLE_ID bgmId;
    Team *teamPlayer;
    Team *teamEnemy;
	float ticks;
    Engine::Point spawnPointA, spawnPointB;
public:
	static bool DebugMode;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	int MapId;
	// Map tiles.
	Group* TileMapGroup;
	Group* GroundEffectGroup;
	Group* BulletGroup;
	Group* EffectGroup;
	Group* UIGroup;
    TowerIndicator* preview;
    TowerButton* updateButton;
	Engine::Label* UIMoney;
	Engine::Label* UIPLives;
	Engine::Label* UIELives;
	Engine::Label* UIDamage;
	Engine::Image* imgTarget;
	std::vector<std::vector<Engine::TileType>> mapState;
    std::vector<std::vector<Engine::TileType>> originMap;
	explicit PlayScene() = default;
	static Engine::Point GetClientSize();
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
    /// @param(id) the id of the instance.
    /// Please be causcious that it is the opponent of the teamID will get hit.
	void Hit(int id);
	int GetMoney() const;
    /// @param(id) the id of the instance.
    /// @param(isGround) whether the instance is in ground group.
    /// @param(iter) the object iterator of the instance.
    /// Delete the instance from correspond team and the correspond group
    void DeleteInstance(int id, bool isGround, std::list<std::pair<bool, IObject*>>::iterator const& iter);
    /// @param(id) the id of the instance.
    /// Please be causcious that it is the opponent of the teamID will get money.
	void EarnMoney(int money, int id);
};
#endif // PLAYSCENE_HPP
