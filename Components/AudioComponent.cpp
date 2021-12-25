#include "AudioComponent.h"
#include "../Game/DungeonGame.h"

AudioComponent::AudioComponent(GameObject* gameObject)
	: Component(gameObject)
{
	audioManager = DungeonGame::getInstance()->getAudioManager();

}

void AudioComponent::addSound(std::string name, std::string eventPath)
{
	auto found = sounds.find(name);
	if (found != sounds.end())
	{
		Debug::Log("Trying to add duplicate sound to AudioComponent", Logs::WARNING);
		return;
	}
	sounds[name] = audioManager->getEventInstance(eventPath);
}

void AudioComponent::playSound(std::string name)
{
	auto found = sounds.find(name);
	if (found != sounds.end())
	{
		Debug::Log("Sound found! " + name);
		sounds[name]->start();
	}
	else
	{
		Debug::Log("Trying to stop a non-existing sound in AudioComponent", Logs::WARNING);
	}
}


void AudioComponent::stopSound(std::string name, FMOD_STUDIO_STOP_MODE stopMode)
{
	auto found = sounds.find(name);
	if (found != sounds.end())
	{
		Debug::Log("Sound found!");
		sounds[name]->stop(stopMode);
	}
	else
	{
		Debug::Log("Trying to stop a non-existing sound in AudioComponent", Logs::WARNING);
	}
}
