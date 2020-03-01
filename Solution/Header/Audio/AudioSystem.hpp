#pragma once
#include <unordered_map>
#include "SoundEvent.hpp"
#include "Math/Math.h"

class Engine;

namespace FMOD
{
	class System;
	namespace Studio
	{
		class Bank;
		class EventDescription;
		class EventInstance;
		class System;
		class Bus;
	};
};


class AudioSystem {
public:
	AudioSystem(Engine* e);
	~AudioSystem();

	bool Initialize();
	void Shutdown();
	void Update(float deltaTime);

	void LoadBank(const std::string& name);
	void UnloadBank(const std::string& name);
	void UnloadAllBanks();

	SoundEvent PlayEvent(std::string name);

protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);

private:
	static unsigned int NextID;

	Engine* engine;
	FMOD::Studio::System* system;
	FMOD::System* lowLevelSystem;

	std::unordered_map<std::string, FMOD::Studio::Bank*> banks;
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> events;
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> eventInstances;


};