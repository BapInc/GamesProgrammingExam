#include "DungeonGame.h"
#include "../GameStates/LevelState.h"
#include "../Utility/Debug.h"

DungeonGame* DungeonGame::instance = nullptr;
DungeonGame::DungeonGame()
{
	instance = this;
#ifdef _DEBUG
	Debug::Log("Game instantiated", SUCCESS);
#endif 
	renderer.setWindowSize(windowSize);

	SDL_GetWindowSize(renderer.getSDLWindow(), &w, &h);

	renderer.init().withSdlInitFlags(SDL_INIT_EVERYTHING)
		.withSdlWindowFlags(SDL_WINDOW_OPENGL);
	// Load audio 
	Debug::Log("$(ProjectDir)");
	audioManager = std::make_shared<AudioManager>();
	// Load bank with audio files
	audioManager->loadBank("..\\FMOD_Banks\\Master.bank");
	// Load bank with strings of event path names (So we don't have to use GUI to play sounds)
	audioManager->loadBank("..\\FMOD_Banks\\Master.strings.bank");

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

std::shared_ptr<AudioManager> DungeonGame::getAudioManager()
{
	return audioManager;
}

const glm::vec2& DungeonGame::getWindowSize()
{
	return windowSize;
}

void DungeonGame::onKey(SDL_Event& event)
{
	currentState->onKey(event);
}

void DungeonGame::update(float time)
{
	currentState->update(time);
	if (audioManager != nullptr)
		audioManager->update();
}

void DungeonGame::render()
{
	currentState->render();
}
