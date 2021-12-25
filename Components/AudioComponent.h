#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H

#include "Component.h"
#include "fmod_studio.h"
#include "fmod.h"
#include "../Managers/AudioManager.h"

using namespace rapidjson;
class AudioComponent : public Component
{
public:
	explicit AudioComponent(GameObject* gameObject);

	void addSound(std::string name, std::string eventPath);
	void playSound(std::string name);
	void stopSound(std::string name, FMOD_STUDIO_STOP_MODE stopMode);

	void AudioComponent::setValuesFromJSON(GenericMember<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* jsonObject) override;
private:

	std::shared_ptr<AudioManager> audioManager;
	std::map <std::string, FMOD::Studio::EventInstance*> sounds;
};

#endif