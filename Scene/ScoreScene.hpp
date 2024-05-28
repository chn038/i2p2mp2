#ifndef SCORESCENE_HPP
#define SCORESCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include <string>
#include "Engine/IScene.hpp"

class ScoreScene final : public Engine::IScene {
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:

    struct Score {
        std::string name;
        int score;
        Score(std::string str, int val)
        :name(str), score(val){}
        bool operator>(Score rhs) {
            return score > rhs.score;
        }
    };

	explicit ScoreScene() = default;
	void Initialize() override;
	void Terminate() override;
    void OnKeyUp(int keyCode) override;
    void OnKeyDown(int keyCode) override;
	void BackOnClick(int stage);
    void NextOnClick(int stage);
    void PrevOnClick(int stage);
};

#endif // SCORESCENE_HPP
