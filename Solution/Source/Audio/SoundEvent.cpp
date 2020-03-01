#include "Audio\SoundEvent.hpp"
#include "Audio\AudioSystem.hpp"
#include <fmod_studio.hpp>

SoundEvent::SoundEvent() : system(nullptr), ID(0)
{
}

SoundEvent::SoundEvent(AudioSystem* s, unsigned int ID) : system(s), ID(ID)
{
}


bool SoundEvent::IsValid()
{
	return (system && system->GetEventInstance(ID) != nullptr);
}

void SoundEvent::Restart()
{
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		event->start();
	}
}

void SoundEvent::Stop(bool allowFadeOut)
{
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		FMOD_STUDIO_STOP_MODE mode = allowFadeOut ?
			FMOD_STUDIO_STOP_ALLOWFADEOUT :
			FMOD_STUDIO_STOP_IMMEDIATE;
		event->stop(mode);
	}
}

void SoundEvent::SetPause(bool pause)
{
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		event->setPaused(pause);
	}
}

void SoundEvent::SetVolume(float value)
{
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		event->setVolume(value);
	}
}

void SoundEvent::SetPitch(float value)
{
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		event->setPitch(value);
	}
}

void SoundEvent::SetParameter(const std::string& name, float value)
{
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		event->setParameterValue(name.c_str(), value);
	}
}

bool SoundEvent::GetPaused() const
{
	bool retVal = false;
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		event->getPaused(&retVal);
	}
	return retVal;
}

float SoundEvent::GetVolume() const
{
	float retVal = 0.0f;
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		event->getVolume(&retVal);
	}
	return retVal;;
}

float SoundEvent::GetPitch() const
{
	float retVal = 0.0f;
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		event->getPitch(&retVal);
	}
	return retVal;
}

float SoundEvent::GetParameter(const std::string& name)
{
	float retVal = 0.0f;
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		event->getParameterValue(name.c_str(), &retVal);
	}
	return retVal;
}

bool SoundEvent::Is3D() const
{
	bool retVal = false;
	auto event = system ? system->GetEventInstance(ID) : nullptr;
	if (event)
	{
		// Get the event description
		FMOD::Studio::EventDescription* ed = nullptr;
		event->getDescription(&ed);
		if (ed)
		{
			ed->is3D(&retVal);
		}
	}
	return retVal;
}

void SoundEvent::Set3DAttributes(const Matrix4& worldTrans)
{
}
