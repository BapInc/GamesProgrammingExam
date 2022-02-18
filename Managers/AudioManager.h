#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include "fmod_studio.hpp"
#include "fmod.hpp"
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>
#include <string>
#include "fmod_errors.h"
#include "../Utility/Debug.h"


// TODO: Add sounds to vector
class AudioManager
{
public:
	~AudioManager();
	AudioManager();


	void update();

	void loadBank(std::string path);
	FMOD::Studio::EventInstance* getEventInstance(std::string path);
	void playOneShot(std::string path);




private:
	FMOD::Studio::System* fmodSystem;
	FMOD::Studio::Bank* fmodBank;
	Logs getFMODResultStatus(FMOD_RESULT result);


};

#endif
