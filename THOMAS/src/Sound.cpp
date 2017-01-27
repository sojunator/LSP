#include "Sound.h"
#include <AtlBase.h>
#include <atlconv.h>

namespace thomas
{
	Sound::Data Sound::s_data;
	std::vector<Sound*> Sound::s_music;
	std::vector<Sound*> Sound::s_soundEffect;
	float Sound::s_masterVolume;
	float Sound::s_fxVolume;
	float Sound::s_musicVolume;

	Sound::Sound(std::string fileName, std::string name, Type type, DirectX::SoundEffect * sound, DirectX::AudioEngine * audioEngine)
	{
		s_data.fileName = fileName;
		s_data.name = name;
		s_data.type = type;
		s_data.sound = sound;
		s_data.audioEngine = audioEngine;
		s_data.instance = NULL;
		if(type == Type::Music)
			s_data.instance = s_data.sound->CreateInstance();
	}

	bool Sound::Init()
	{
		//because win32 desktop app
		CoInitialize(nullptr);

		s_data.audioEngine = new DirectX::AudioEngine();
		s_masterVolume = 0.5f;
		s_fxVolume = 0.5f;
		s_musicVolume = 0.5f;
		return true;
	}

	Sound * thomas::Sound::CreateSound(std::string fileName, std::string name, Type type)
	{
		if (type == Type::Effect)
		{
			for (int i = 0; i < s_soundEffect.size(); ++i)
			{
				if (fileName == s_soundEffect[i]->s_data.fileName)
					return s_soundEffect[i];
			}
			Sound* newSound = new Sound(fileName, name, type, new DirectX::SoundEffect(s_data.audioEngine, CA2W(fileName.c_str())), s_data.audioEngine);
			s_soundEffect.push_back(newSound);
			return newSound;
		}
		
		else if (type == Type::Music)
		{
			for (int i = 0; i < s_music.size(); ++i)
			{
				if (fileName == s_music[i]->s_data.fileName)
					return s_music[i];
			}
			Sound* newSound = new Sound(fileName, name, type, new DirectX::SoundEffect(s_data.audioEngine, CA2W(fileName.c_str())), s_data.audioEngine);
			
			s_music.push_back(newSound);
			return newSound;
		}
		return nullptr;
	}
	std::string Sound::GetFileName()
	{
		return s_data.fileName;
	}

	bool Sound::Play()
	{
		if (s_data.type == Type::Effect)
		{
			s_data.sound->Play(s_masterVolume * s_fxVolume, 0, 0);
			return true;
		}
		else if(s_data.audioEngine->Reset()) //is music type and not in use
		{
			if (!s_data.instance->GetState())
			{
				s_data.instance->Play(true);
				s_data.instance->SetVolume(s_masterVolume * s_musicVolume);
				return true;
			}
			else
			{
				s_data.instance->Resume();
				return true;
			}
		}
		return false;
	}

	void Sound::Pause()
	{
		if(s_data.instance)
			s_data.instance->Pause();
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
		for (int i = 0; i < s_music.size(); ++i)
		{
			delete s_data.sound;
			s_data.audioEngine->Suspend();
			s_data.instance.reset();
		}
		for (int i = 0; i < s_soundEffect.size(); ++i)
		{
			delete s_data.sound;
			s_data.audioEngine->Suspend();
		}
	}
}
