#include "DungeonGame.h"
#include "PlayState.h"

DungeonGame* DungeonGame::instance = nullptr;
DungeonGame::DungeonGame()
{
	instance = this;
	#ifdef _DEBUG
		printf("Game instantiated");
	#endif 
	
	renderer.setWindowSize(DungeonGame::windowSize);
	renderer.init().withSdlInitFlags(SDL_INIT_EVERYTHING)
		.withSdlWindowFlags(SDL_WINDOW_OPENGL);

	init();
	currentState->start();

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

std::shared_ptr<DungeonGame> DungeonGame::getInstance()
{
	if(!instance)
		instance = new DungeonGame();
	return std::shared_ptr<DungeonGame>(instance);
}

void DungeonGame::init()
{
	currentState = std::make_shared<PlayState>();
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
