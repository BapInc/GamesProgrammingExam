#ifndef DUNGEONGAME
#define DUNGEONGAME

#include "sre/SDLRenderer.hpp"
#include "../GameStates/GameState.h"
#include "../Components/TopDownCameraComponent.h"
#include "../Managers/AudioManager.h"

class DungeonGame
{
public:
	DungeonGame();
	void generateDungeon();
	std::shared_ptr<AudioManager> getAudioManager();
	const glm::vec2& getWindowSize();
	static DungeonGame* getInstance();

private:
	static DungeonGame* instance;

	sre::SDLRenderer renderer; //TODO: Should renderer be here or in Playstate?
	const glm::vec2 windowSize = glm::vec2(1920, 1080);

	void init();
	void onKey(SDL_Event& event);
	void update(float time);
	void render();

	std::shared_ptr<AudioManager> audioManager;

	std::shared_ptr<GameState> currentState;

	std::shared_ptr<TopDownCameraComponent> camera;
};

#endif

