#ifndef DUNGEONGAME
#define DUNGEONGAME

#include "sre/SDLRenderer.hpp"
#include "GameState.h"
#include "TopDownCameraComponent.h"

class DungeonGame
{
public:
	DungeonGame();
	static DungeonGame* instance();

	void generateDungeon();
	const glm::vec2& getWindowSize();

private:

	sre::SDLRenderer renderer; //TODO: Should renderer be here or in Playstate?
	const glm::vec2 windowSize = glm::vec2(400, 600);

	void init();
	void onKey(SDL_Event& event);
	void update(float time);
	void render();

	GameState* currentState;

	std::shared_ptr<TopDownCameraComponent> camera;
};

#endif

