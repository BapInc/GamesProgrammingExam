#include "AudioManager.h"
#include "fmod_studio_common.h"


FMOD_RESULT F_CALLBACK oneshotStoppedCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* eventInstance, void* parameters);


AudioManager::AudioManager()
{
	Debug::Log("Initializing FMOD...");
	FMOD::Studio::System::create(&fmodSystem, FMOD_VERSION);
	auto initializeResult = fmodSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL);
	fmodSystem->update();
	Debug::Log(FMOD_ErrorString(initializeResult), getFMODResultStatus(initializeResult));
}

void AudioManager::update()
{
	fmodSystem->update();
}

void AudioManager::loadBank(std::string path)
{
	Debug::Log("Loading bank...");
	auto loadBankResult = fmodSystem->loadBankFile(path.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &fmodBank);
	Debug::Log(FMOD_ErrorString(loadBankResult), getFMODResultStatus(loadBankResult));

}


FMOD::Studio::EventInstance* AudioManager::getEventInstance(std::string path)
{

	Debug::Log("Loading Event Description... for path: " + path);

	FMOD::Studio::EventDescription* eventDesc;
	auto loadEventDescription = fmodSystem->getEvent(path.c_str(), &eventDesc);

	Debug::Log(FMOD_ErrorString(loadEventDescription), getFMODResultStatus(loadEventDescription));
	Debug::Log("Loading Sample Data...");
	FMOD::Studio::EventInstance* sound;
	eventDesc->createInstance(&sound);

	return sound;
}
Logs AudioManager::getFMODResultStatus(FMOD_RESULT result)
{
	return result == FMOD_RESULT::FMOD_OK ? Logs::SUCCESS : Logs::ALERT;
}
FMOD_RESULT F_CALLBACK oneshotStoppedCallback(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* eventInstance, void* parameters)
{
	Debug::Log("Sound stopped playing");
	return FMOD_OK();
}
;
