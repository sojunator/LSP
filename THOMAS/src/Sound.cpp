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
	std::unique_ptr<DirectX::SoundEffectInstance> Sound::s_mInstance;
	std::unique_ptr<DirectX::SoundEffectInstance> Sound::s_aInstance;
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
		s_bank = NULL;
		return true;
	}

	bool Sound::Play(std::string name, float volume)
	{
		if (name[0] == 'm')
		{
			
			s_mInstance = s_bank->CreateInstance(name.c_str());
			if (!s_mInstance)
			{
				LOG("No instance was created for name: '" + name + "', probably invalid name. Check .txt file that comes with the wavebank.");
				return false;
			}
			s_mInstance->Play(true);
			s_mInstance->SetVolume(s_masterVolume * s_musicVolume * volume);
			return true;
		}
		else if (name[0] == 'f')
		{
			s_bank->Play(name.c_str(), s_masterVolume * s_fxVolume * volume, 0.0f, 0.0f);
			return true;
		}
		else if (name[0] == 'a')
		{
			s_aInstance = s_bank->CreateInstance(name.c_str());
			if (!s_aInstance)
			{
				LOG("No instance was created for name: '" + name + "', probably invalid name. Check .txt file that comes with the wavebank.");
				return false;
			}
			s_aInstance->Play(true);
			s_aInstance->SetVolume(s_masterVolume * s_musicVolume * volume);
			return true;
		}
		return false;
	}

	void Sound::Pause()
	{
		s_mInstance->Pause();
		s_aInstance->Pause();
	}

	void Sound::Resume()
	{
		s_mInstance->Resume();
		s_aInstance->Resume();
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
	bool Sound::LoadWaveBank(std::string name)
	{
		s_bank = std::make_unique<DirectX::WaveBank>(s_audioEngine.get(), CA2W(name.c_str()));
		if (!s_bank)
		{
			LOG("Unable to load wavebank, probably invalid path and/or name");
			return false;
		}
		return true;
	}
	void Sound::Destroy()
	{
		s_audioEngine->Suspend();
	}
}