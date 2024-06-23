#include <fstream>
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "UI/Component/Image.hpp"
#include "Engine/Resources.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/LOG.hpp"
#include "UI/Component/Label.hpp"
#include "Tower/TowerButton.hpp"
#include "Tower/TowerIndicator.hpp"
#include "Tower/Tower1.hpp"
#include "Tower/Tower2.hpp"
#include "Tower/Tower3.hpp"
#include "Tower/Tower4.hpp"
#include "Tower/Tower5.hpp"

bool PlayScene::DebugMode = false;
const int PlayScene::BlockSize = 64;
const int PlayScene::MapWidth = 20;
const int PlayScene::MapHeight = 13;

Engine::Point PlayScene::GetClientSize() {
	return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}

void PlayScene::Initialize() {
	mapState.clear();
    originMap.clear();
	ticks = 0;
    speedMul = 1;
    // set the score to 0
    Engine::GameEngine::GetInstance().GetScore() = 0;
	// Add groups from bottom to top.
	AddNewObject(TileMapGroup = new Group());
	ReadMap();
    // Team initialize
	// Should support buttons.
	AddNewControlObject(UIGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
    AddNewObject(teamPlayer = new Team(spawnPointA, spawnPointB, 0, al_map_rgb(0, 255, 0)));
    AddNewObject(teamEnemy = new Team(spawnPointB, spawnPointA, 1, al_map_rgb(255, 0, 0)));
	AddNewObject(EffectGroup = new Group());
	AddNewObject(BulletGroup = new Group());
    teamPlayer->SetOpponent(teamEnemy);
    teamEnemy->SetOpponent(teamPlayer);
	ReadEnemyWave();
	ConstructUI();
	imgTarget = new Engine::Image("play/target.png", 0, 0);
	imgTarget->Visible = false;
	preview = nullptr;
	UIGroup->AddNewObject(imgTarget);
	// Preload Scene
	Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
	Engine::Resources::GetInstance().GetBitmap("win/benjamin-sad.png");
	// Start BGM.
	bgmId = AudioHelper::PlayBGM("play.ogg");
}

void PlayScene::Draw() const {
    IScene::Draw();
}

void PlayScene::Update(float deltaTime) {
    for (int i = 0; i < speedMul; ++i) {
        IScene::Update(deltaTime);

        if (teamEnemy->lives <= 0) {
            Engine::GameEngine::GetInstance().ChangeScene("win");
            return;
        }
        if (teamPlayer->lives <= 0) {
            Engine::GameEngine::GetInstance().ChangeScene("lose");
            return;
        }

        if (enemyWave.empty()) continue;
        Wave& current = enemyWave.front();
        ticks += deltaTime;
        if (ticks < current.time) continue;
        ticks -= current.time;
        float objx = current.pos.x * BlockSize + BlockSize / 2.0;
        float objy = current.pos.y * BlockSize + BlockSize / 2.0;
        teamEnemy->addTower(objx, objy, current.type);
        enemyWave.pop();
    }
}

void PlayScene::OnMouseDown(int button, int mx, int my) {
    if ((button & 1) && !imgTarget->Visible && preview) {
        UIGroup->RemoveObject(preview->GetObjectIterator());
        preview = nullptr;
    }
    IScene::OnMouseDown(button, mx, my);
}

void PlayScene::OnMouseMove(int mx, int my) {
    IScene::OnMouseMove(mx, my);
    Engine::Point bp(int(mx / BlockSize), int(my / BlockSize));
    if (preview) {
        preview->SetPos(Engine::Point(mx, my));
        preview->Update(0);
    }
    if (!preview || bp.x < 0 || bp.x >= MapWidth || bp.y < 0 || bp.y >= MapHeight) {
        imgTarget->Visible = false;
        return;
    }
    imgTarget->Visible = true;
    imgTarget->Position = bp * BlockSize;
}

void PlayScene::OnMouseUp(int button, int mx, int my) {
    IScene::OnMouseUp(button, mx, my);
    if (!imgTarget->Visible) return;
    Engine::Point bp(int(mx / BlockSize), int(my / BlockSize));
    float objx = (bp.x + 0.5) * BlockSize;
    float objy = (bp.y + 0.5) * BlockSize;
    if (!(button & 1)) return;

    if (!preview) return;

    Engine::LOG(Engine::INFO) << preview->type;
    if (preview->type == 0) {
        if (mapState[bp.y][bp.x] != Engine::TILE_OCCUPIED) {
            Engine::Sprite* sprite;
            GroundEffectGroup->AddNewObject(sprite = new DirtyEffect("play/target-invalid.png",
                                                                     1, objx, objy));
            sprite->Rotation = 0;
            return;
        }
        for (auto& it : teamPlayer->TowerGroup->GetObjects()) {
            if (it.second->Position.x == objx && it.second->Position.y == objy) {
                EarnMoney(dynamic_cast<Tower*>(it.second)->GetPrice() * 0.5, 1);
                teamPlayer->TowerGroup->RemoveObject(it.second->GetObjectIterator());
                UIGroup->RemoveObject(preview->GetObjectIterator());
                preview = nullptr;
                mapState[bp.y][bp.x] = originMap[bp.y][bp.x];
                break;
            }
        }
        return;
    } else {
        if (mapState[bp.y][bp.x] != Engine::TILE_FLOOR ||
            teamPlayer->money < preview->price ||
            bp.x > 10) {
            Engine::Sprite* sprite;
            GroundEffectGroup->AddNewObject(sprite = new DirtyEffect("play/target-invalid.png",
                                                                     1, objx, objy));
            sprite->Rotation = 0;
            return;
        }
        std::cout << bp.y << ' ' << bp.x << std::endl;
        EarnMoney(-preview->price, 1);
        teamPlayer->addTower(objx, objy, preview->type);
        UIGroup->RemoveObject(preview->GetObjectIterator());
        preview = nullptr;
        mapState[bp.y][bp.x] = Engine::TILE_OCCUPIED;
        return;
    }
}

void PlayScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    switch (keyCode) {
        case ALLEGRO_KEY_TAB:
            DebugMode = !DebugMode;
            break;
        case ALLEGRO_KEY_Q:
            UIBtnClicked(1);
            break;
        case ALLEGRO_KEY_W:
            UIBtnClicked(2);
            break;
        case ALLEGRO_KEY_E:
            UIBtnClicked(3);
            break;
        case ALLEGRO_KEY_R:
            UIBtnClicked(4);
            break;
        case ALLEGRO_KEY_T:
            UIBtnClicked(5);
            break;
        case ALLEGRO_KEY_S:
            UIBtnClicked(0);
            break;
        case ALLEGRO_KEY_D:
            UIBtnClicked(6);
            break;
    }
    if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
        // Hotkey for Speed up.
        speedMul = keyCode - ALLEGRO_KEY_0;
        Engine::LOG(Engine::INFO) << "SpeedMul : " << speedMul;
    }
}

void PlayScene::Terminate() {
    AudioHelper::StopBGM(bgmId);
    IScene::Terminate();
}

void PlayScene::Hit(int id) {
    switch(id) {
        case 0:
            teamEnemy->Hit();
            UIELives->Text = std::string("Oppo HP ") + std::to_string(teamEnemy->lives);
            return;
        case 1:
            teamPlayer->Hit();
            UIPLives->Text = std::string("Your HP ") + std::to_string(teamPlayer->lives);
            // maybe a warning here?
            return;
    }
}

int PlayScene::GetMoney() const {
    return teamPlayer->money;
}

void PlayScene::EarnMoney(int val, int ID) {
    if (ID == 0) 
        return;
    teamPlayer->money += val;
    UIMoney->Text = std::string("$ ") + std::to_string(teamPlayer->money);
}

void PlayScene::ConstructUI() {
    int startX = MapWidth * BlockSize;
    int gap = 20;
    int size = 40;
    int SWidth = Engine::GameEngine::GetInstance().GetScreenWidth();
    int SHeight = Engine::GameEngine::GetInstance().GetScreenHeight();
    // Background
    UIGroup->AddNewObject(
        new Engine::Image("play/sand.png", 
                          startX, 0, SWidth - startX, SHeight));
	// Background
	UIGroup->AddNewObject(new Engine::Image("play/sand.png", 1280, 0, 320, 832));
	// Text
	UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(teamPlayer->money), "pirulen.ttf", 24, 1294, 32));
	UIGroup->AddNewObject(UIPLives = new Engine::Label(std::string("Your HP ") + std::to_string(teamPlayer->lives), "pirulen.ttf", 24, 1294, 48));
	UIGroup->AddNewObject(UIDamage = new Engine::Label(std::to_string(teamPlayer->damageOffset), "pirulen.ttf", 24, 1522, 288));
	UIGroup->AddNewObject(UIELives = new Engine::Label(std::string("Oppo HP ") + std::to_string(teamEnemy->lives), "pirulen.ttf", 24, 1294, 88));
	TowerButton* btn;
    // Delete Tower
    btn = new TowerButton("play/floor.png", "play/dirt.png",
                          Engine::Sprite("play/dirt.png", 1522, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/target-invalid.png", 1522, 136, 0, 0, 0, 0),
                          Engine::Label(std::to_string(0), "pirulen.ttf", 16, 1522, 136),
                          1522, 136, 0);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 0));
	UIGroup->AddNewControlObject(btn);
	// Button 1
    btn = new TowerButton("play/floor.png", "play/dirt.png",
                          Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-1.png", 1294, 136 - 8, 0, 0, 0, 0),
                          Engine::Label(std::to_string(Tower1::Price), "pirulen.ttf", 16, 1294, 136),
                          1294, 136, Tower1::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 1));
	UIGroup->AddNewControlObject(btn);
	// Button 2
    btn = new TowerButton("play/floor.png", "play/dirt.png",
                          Engine::Sprite("play/tower-base.png", 1294, 212, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-2.png", 1294, 212 - 8, 0, 0, 0, 0),
                          Engine::Label(std::to_string(Tower2::Price), "pirulen.ttf", 16, 1294, 212),
                          1294, 212, Tower2::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 2));
	UIGroup->AddNewControlObject(btn);
	// Button 3
    btn = new TowerButton("play/floor.png", "play/dirt.png",
                          Engine::Sprite("play/tower-base.png", 1294, 288, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-3.png", 1294, 288, 0, 0, 0, 0),
                          Engine::Label(std::to_string(Tower3::Price), "pirulen.ttf", 16, 1294, 288),
                          1294, 288, Tower3::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 3));
	UIGroup->AddNewControlObject(btn);
	// Button 4
    btn = new TowerButton("play/floor.png", "play/dirt.png",
                          Engine::Sprite("play/tower-base.png", 1294, 364, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-4.png", 1294, 364, 0, 0, 0, 0),
                          Engine::Label(std::to_string(Tower4::Price), "pirulen.ttf", 16, 1294, 364),
                          1294, 364, Tower4::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 4));
	UIGroup->AddNewControlObject(btn);
	// Button 5
    btn = new TowerButton("play/floor.png", "play/dirt.png",
                          Engine::Sprite("play/tower-base.png", 1294, 440, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-3.png", 1294, 440, 0, 0, 0, 0),
                          Engine::Label(std::to_string(Tower5::Price), "pirulen.ttf", 16, 1294, 440),
                          1294, 440, Tower5::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 5));
	UIGroup->AddNewControlObject(btn);
    // Button 6
    updateButton = new TowerButton("play/target.png", "play/bullet-1.png",
                                   Engine::Sprite("play/target.png", 1522, 212, 0, 0, 0, 0),
                                   Engine::Sprite("play/bullet-1.png", 1522, 212, 0, 0, 0, 0),
                                   Engine::Label(std::to_string(200), "pirulen.ttf", 16, 1522, 212),
                                   1522, 212, 200);
    updateButton->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 6));
    UIGroup->AddNewControlObject(updateButton);
}

void PlayScene::UIBtnClicked(int id) {
    if (preview) {
        UIGroup->RemoveObject(preview->GetObjectIterator());
        preview = nullptr;
    }
    switch (id) {
        case 0:
            preview = new TowerIndicator(
                          Engine::Sprite("play/dirt.png", 1522, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/target-invalid.png", 1522, 136, 0, 0, 0, 0),
                          0, 0, 0, 0, 0);
            break;
        case 1:
            if (teamPlayer->money >= Tower1::Price) {
                preview = new TowerIndicator(
                          Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-1.png", 1294, 136 - 8, 0, 0, 0, 0),
                          64 + 32, Tower1::Price, 1, 0, 0);
            }
            break;
        case 2:
            if (teamPlayer->money >= Tower2::Price) {
                preview = new TowerIndicator(
                          Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-2.png", 1294, 136 - 8, 0, 0, 0, 0),
                          64 * 2 + 32, Tower2::Price, 2, 0, 0);
            }
            break;
        case 3:
            if (teamPlayer->money >= Tower3::Price) {
                preview = new TowerIndicator(
                          Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-3.png", 1294, 136 - 8, 0, 0, 0, 0),
                          64 * 3 + 32, Tower3::Price, 3, 0, 0);
            }
            break;
        case 4:
            if (teamPlayer->money >= Tower4::Price) {
                preview = new TowerIndicator(
                          Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-4.png", 1294, 136 - 8, 0, 0, 0, 0),
                          64 * 4 + 32, Tower4::Price, 4, 0, 0);
            }
            break;
        case 5:
            if (teamPlayer->money >= Tower5::Price) {
                preview = new TowerIndicator(
                          Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-5.png", 1294, 136 - 8, 0, 0, 0, 0),
                          0, Tower5::Price, 5, 0, 0);
            }
            break;
        case 6:
            if (teamPlayer->money >= updateButton->money) {
                EarnMoney(-updateButton->money, 1);
                teamPlayer->damageOffset += 1;
                updateButton->money *= 2;
                updateButton->Price.Text = std::to_string(updateButton->money);
                UIDamage->Text = std::string("Up ") + std::to_string(teamPlayer->damageOffset);

                for (auto &it : teamPlayer->TowerGroup->GetObjects()) {
                    dynamic_cast<Tower*>(it.second)->UpgradeDamage(teamPlayer->damageOffset);
                }
                for (auto &it : teamPlayer->FlyGroup->GetObjects()) {
                    dynamic_cast<Tower*>(it.second)->UpgradeDamage(teamPlayer->damageOffset);
                }
                for (auto &it : teamPlayer->GroundGroup->GetObjects()) {
                    dynamic_cast<Tower*>(it.second)->UpgradeDamage(teamPlayer->damageOffset);
                }
            }
            break;
    }

    if (!preview) return;
    preview->SetPos(Engine::GameEngine::GetInstance().GetMousePosition());
    preview->SetTint(al_map_rgba(255, 255, 255, 200));
    UIGroup->AddNewObject(preview);
    OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x,
                Engine::GameEngine::GetInstance().GetMousePosition().y);
    preview->Update(0);
}

void PlayScene::ReadMap() {
    int i = 0, j = 0;
    std::string filename = std::string("Resource/map.txt");
    char c;
    std::vector<int> mapData;
    std::ifstream fin(filename);
    while (c = fin.get(), !fin.eof()) {
        switch (c) {
            case '0':
                mapData.push_back(0);
                j++;
                break;
            case '1':
                mapData.push_back(1);
                j++;
                break;
            case '2':
                spawnPointA = Engine::Point(j, i);
                std::cout << j << ' ' << i;
                mapData.push_back(1);
                j++;
                break;
            case '3':
                spawnPointB = Engine::Point(j, i);
                std::cout << j << ' ' << i;
                mapData.push_back(1);
                j++;
                break;
            case '5':
                mapData.push_back(2);
                j++;
                break;
            case '\n':
            case '\r':
                if (j != MapWidth)
                    throw std::ios_base::failure("Map data is corrupted.");
                i++;
                j = 0;
                break;
            default:
                throw std::ios_base::failure("Map data is corrupted.");
        }
    }
    fin.close();
    if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
        throw std::ios_base::failure("Error reading map data");
    originMap = std::vector<std::vector<Engine::TileType>>(MapHeight, std::vector<Engine::TileType>(MapWidth));
    for (int h = 0; h < MapHeight; ++h) {
        for (int w = 0; w < MapWidth; ++w) {
            int type = mapData[h * MapWidth + w];
            switch (type) {
                case 0:
                    originMap[h][w] = Engine::TILE_FLOOR;
                    TileMapGroup->AddNewObject(new Engine::Image("play/floor.png", w * BlockSize, h * BlockSize, BlockSize, BlockSize));
                    break;
                case 1:
                    originMap[h][w] = Engine::TILE_DIRT;
                    TileMapGroup->AddNewObject(new Engine::Image("play/dirt.png", w * BlockSize, h * BlockSize, BlockSize, BlockSize));
                    break;
                case 2:
                    originMap[h][w] = Engine::TILE_OCCUPIED;
                    TileMapGroup->AddNewObject(new Engine::Image("play/floor.png", w * BlockSize, h * BlockSize, BlockSize, BlockSize));
                    TileMapGroup->AddNewObject(new Engine::Image("play/target-invalid.png", w * BlockSize, h * BlockSize, BlockSize, BlockSize));
                    break;
            };
        }
    }
    for (int h = 0; h < MapHeight; ++h) {
        for (int w = 0; w < MapWidth; ++w) {
            switch(originMap[h][w]) {
                case Engine::TILE_FLOOR:
                    std::cout << 0;
                    break;
                case Engine::TILE_DIRT:
                    std::cout << 1;
                    break;
                case Engine::TILE_OCCUPIED:
                    std::cout << 2;
                    break;
            }
        }
        std::cout << std::endl;
    }
    mapState = originMap;
}

void PlayScene::ReadEnemyWave() {
    std::string filename = std::string("Resource/enemy") + std::to_string(MapId) + ".txt";
	// Read enemy file.
    // time type posx posy
    while (!enemyWave.empty()) {
        enemyWave.pop();
    }
	std::ifstream fin(filename);
    int time, type, posx, posy;
	while (fin >> time && fin >> type && fin >> posx && fin >> posy) {
        enemyWave.emplace(Wave(time, type, Engine::Point(posx, posy)));
	}
    Engine::LOG(Engine::INFO) << "Total wave size " << enemyWave.size();
	fin.close();
}

void PlayScene::DeleteInstance(int id, bool isGround, 
                               std::list<std::pair<bool, IObject*>>::iterator const& iter) {
    if (id == 0) {
        if (isGround)
            teamPlayer->GroundGroup->RemoveObject(iter);
        else
            teamPlayer->FlyGroup->RemoveObject(iter);
    } else if (id == 1) {
        if (isGround)
            teamEnemy->GroundGroup->RemoveObject(iter);
        else
            teamEnemy->FlyGroup->RemoveObject(iter);
    }
}
