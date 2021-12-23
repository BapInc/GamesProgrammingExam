#include "DungeonGame.h"
#include "../GameStates/LevelState.h"
#include "../Utility/Debug.h"

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

	Debug::Log("Normal Debug");
	Debug::Log("Alert, you love cat girls", ALERT);
	Debug::Log("Gotta drink less cherry wine", WARNING);
	Debug::Log("Easy Debug lass", SUCCESS);

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

DungeonGame* DungeonGame::getInstance()
{
	if (!instance)
		instance = new DungeonGame();
	return instance;
}

void DungeonGame::init()
{
	currentState = std::make_shared<LevelState>();
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
	currentState->onKey();
}

void DungeonGame::update(float time)
{
	currentState->update(time);
}

void DungeonGame::render()
{
	currentState->render();
}
