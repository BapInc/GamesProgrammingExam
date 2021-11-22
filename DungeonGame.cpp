#include "DungeonGame.h"
#include "PlayState.h"


DungeonGame::DungeonGame()
{
	static DungeonGame* game = new DungeonGame;

	renderer.setWindowSize(windowSize);
	renderer.init().withSdlInitFlags(SDL_INIT_EVERYTHING)
		.withSdlWindowFlags(SDL_WINDOW_OPENGL);

	init();

	// setup callback functions
	renderer.keyEvent = [&](SDL_Event& e) {
		onKey(e);
	};
	renderer.frameUpdate = [&](float deltaTime) {
		update(deltaTime);
	};
	renderer.frameRender = [&]() {
		render();
	};

	// start game loop
	renderer.startEventLoop(); // Maybe the game won't work unless we register update and render here  
}

DungeonGame* DungeonGame::instance()
{
	static DungeonGame* game = new DungeonGame;
	return game;
}

void DungeonGame::init()
{
	currentState = new PlayState();
}

void DungeonGame::generateDungeon()
{
}

const glm::vec2& DungeonGame::getWindowSize()
{
	return windowSize;
}

void DungeonGame::onKey(SDL_Event& event)
{
	// TODO: Loop over objects that needs onKey to be called
}

void DungeonGame::update(float time)
{
}

void DungeonGame::render()
{
}
