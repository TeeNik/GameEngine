/*
#include "Audio\AudioSystem.hpp"
#include "fmod_studio.hpp"
#include "fmod.h"
#include "fmod_errors.h"
#include "Utils/Utils.hpp"
#include <iostream>
#include <vector>

unsigned int AudioSystem::NextID = 0;

AudioSystem::AudioSystem(Engine* e) : engine(e), system(nullptr), lowLevelSystem(nullptr)
{
}

AudioSystem::~AudioSystem()
{
}

bool AudioSystem::Initialize()
{
	FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR, FMOD_DEBUG_MODE_TTY);
	FMOD_RESULT result = FMOD::Studio::System::create(&system);
	if (result != FMOD_OK) {
		printf("Failed to create FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}
	result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK) {
		printf("Failed to create FMOD system: %s", FMOD_ErrorString(result));
	}
	system->getLowLevelSystem(&lowLevelSystem);

	LoadBank(Utils::ContructPath("Audio/Master Bank.string.bank"));
	LoadBank(Utils::ContructPath("Audio/Master Bank.bank"));

	return false;
}

void AudioSystem::Shutdown()
{
}

void AudioSystem::Update(float deltaTime)
{
	std::vector<unsigned int> done;
	for (auto& iter : eventInstances) {
		auto event = iter.second;
		FMOD_STUDIO_PLAYBACK_STATE state;
		event->getPlaybackState(&state);
		if (state == FMOD_STUDIO_PLAYBACK_STOPPED) {
			event->release();
			done.emplace_back(iter.first);
		}
	}

	for (auto id : done) {
		eventInstances.erase(id);
	}

	system->update();
}

void AudioSystem::LoadBank(const std::string& name)
{
	if (banks.find(name) != banks.end()) {
		return;
	}
	FMOD::Studio::Bank* bank = nullptr;
	FMOD_RESULT result = system->loadBankFile(name.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
	const int maxPathLength = 512;
	if (result == FMOD_OK) {
		banks.emplace(name, bank);
		bank->loadSampleData();
		int numEvents = 0;
		bank->getEventCount(&numEvents);
		if (numEvents > 0) {
			std::vector<FMOD::Studio::EventDescription*> eventsVec(numEvents);
			bank->getEventList(eventsVec.data(), numEvents, &numEvents);
			char eventName[maxPathLength];
			for (int i = 0; i < numEvents; ++i) {
				FMOD::Studio::EventDescription* e = eventsVec[i];
				e->getPath(eventName, maxPathLength, nullptr);
				events.emplace(eventName, e);
			}
		}
	}
}

void AudioSystem::UnloadBank(const std::string& name)
{
	auto iter = banks.find(name);
	if (iter == banks.end()) {
		return;
	}

	FMOD::Studio::Bank* bank = iter->second;
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0) {
		std::vector<FMOD::Studio::EventDescription*> eventsVec(numEvents);
		bank->getEventList(eventsVec.data(), numEvents, &numEvents);
		char eventName[512];
		for (int i = 0; i < numEvents; i++)
		{
			FMOD::Studio::EventDescription* e = eventsVec[i];
			e->getPath(eventName, 512, nullptr);
			auto event = events.find(eventName);
			if (event != events.end())
			{
				events.erase(event);
			}
		}
	}
}

void AudioSystem::UnloadAllBanks()
{
	for (auto& iter : banks) {
		iter.second->unloadSampleData();
		iter.second->unload();
	}
	banks.clear();
	events.clear();
}

SoundEvent AudioSystem::PlayEvent(std::string name)
{
	unsigned int retID = 0;
	auto iter = events.find(name);
	if (iter != events.end()) {
		FMOD::Studio::EventInstance* event = nullptr;
		iter->second->createInstance(&event);
		if (event) {
			event->start();
			++NextID;
			retID = NextID;
			eventInstances.emplace(retID, event);
		}
	}
	return SoundEvent(this, retID);
}

FMOD::Studio::EventInstance * AudioSystem::GetEventInstance(unsigned int id)
{
	FMOD::Studio::EventInstance* event = nullptr;
	auto iter = eventInstances.find(id);
	if (iter != eventInstances.end())
	{
		event = iter->second;
	}
	return event;
}
*/