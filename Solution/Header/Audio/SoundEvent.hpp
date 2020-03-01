#pragma once
#include <string>
#include "Math/Math.h"

class AudioSystem;

class SoundEvent {
public:
	SoundEvent();
	bool IsValid();
	void Restart();
	void Stop(bool allowFadeOut);
	void SetPause(bool pause);
	void SetVolume(float value);
	void SetPitch(float value);
	void SetParameter(const std::string& name, float value);

	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name);
	bool Is3D() const;
	void Set3DAttributes(const Matrix4& worldTrans);

protected:
	friend class AudioSystem;
	SoundEvent(class AudioSystem* s, unsigned int id);

private:
	AudioSystem* system;
	unsigned int ID;

};
