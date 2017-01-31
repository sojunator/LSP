#include "Sound.h"
#include <string>
#include <AtlBase.h>
#include <atlconv.h>

namespace thomas
{
	float Sound::s_masterVolume;
	float Sound::s_fxVolume;
	float Sound::s_musicVolume;
	std::unique_ptr<DirectX::WaveBank> Sound::s_bank;
	std::unique_ptr<DirectX::SoundEffectInstance> Sound::s_instance;
	std::unique_ptr<DirectX::AudioEngine> Sound::s_audioEngine;

	bool Sound::Init()
	{
		//because win32 desktop app
		CoInitialize(nullptr);
		DirectX::AUDIO_ENGINE_FLAGS aEFlags = DirectX::AudioEngine_Default;
#ifdef DEBUG
		aEFlags = aEFlags | DirectX::AudioEngine_Debug;
#endif // DEBUG

		s_audioEngine = std::make_unique<DirectX::AudioEngine>(aEFlags);
		s_masterVolume = 0.5f;
		s_fxVolume = 0.5f;
		s_musicVolume = 0.5f;
		s_bank = std::make_unique<DirectX::WaveBank>(s_audioEngine.get(), L"../res/sounds/soundlist.xwb");
		return true;
	}

	bool Sound::Play(Sound::Music name)
	{
		s_instance = s_bank->CreateInstance(int(name));
		if (!s_instance)
			return false;
		s_instance->Play(true);
		s_instance->SetVolume(s_masterVolume * s_musicVolume);
		return true;
	}
	bool Sound::Play(Sound::Effects name)
	{
		s_bank->Play(int(name), s_masterVolume * s_fxVolume, 0.0f, 0.0f);
		return true;
	}

	void Sound::Pause()
	{
		s_instance->Pause();
	}

	void Sound::Resume()
	{
		s_instance->Resume();
	}

	void Sound::SetMasterVolume(float volume)
	{
		s_masterVolume = volume;
	}
	void Sound::SetFxVolume(float volume)
	{
		s_fxVolume = volume;
	}
	void Sound::SetMusicVolume(float volume)
	{
		s_musicVolume = volume;
	}
	void Sound::Destroy()
	{
		s_audioEngine->Suspend();
	}
}