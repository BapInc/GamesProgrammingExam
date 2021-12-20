#include "DungeonGame.h"
#include "PlayState.h"

DungeonGame* DungeonGame::instance = nullptr;
DungeonGame::DungeonGame()
{
	instance = this;
	#ifdef _DEBUG
		std::cout << "Game instantiated" << std::endl;
	#endif 
	
	renderer.setWindowSize(windowSize);
	renderer.init().withSdlInitFlags(SDL_INIT_EVERYTHING)
		.withSdlWindowFlags(SDL_WINDOW_OPENGL);
	//TODO: Load spritesheet

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

	// start game loope
	renderer.startEventLoop(); // Maybe th game won't work unless we register update and render here  
}

DungeonGame* DungeonGame::getInstance()
{
	if(!instance)
		instance = new DungeonGame();
	return instance;
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
	currentState->render();
}
