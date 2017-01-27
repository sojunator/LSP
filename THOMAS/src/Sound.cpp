#include "Sound.h"
#include <AtlBase.h>
#include <atlconv.h>

namespace thomas
{
	Sound::Data Sound::s_data;
	std::vector<Sound*> Sound::s_music;
	std::vector<Sound*> Sound::s_soundEffect;

	Sound::Sound(std::string fileName, std::string name, int type, DirectX::SoundEffect * sound, DirectX::AudioEngine * audioEngine)
	{
		s_data.fileName = fileName;
		s_data.name = name;
		s_data.type = type;
		s_data.sound = sound;
		s_data.audioEngine = audioEngine;
	}

	bool Sound::Init()
	{
		//because win32 desktop app
		CoInitialize(nullptr);

		s_data.audioEngine = new DirectX::AudioEngine();
	}

	Sound * thomas::Sound::CreateSound(std::string fileName, std::string name, std::string type)
	{
		if (type == "effect")
		{
			for (int i = 0; i < s_soundEffect.size(); ++i)
			{
				if (fileName == s_soundEffect[i]->s_data.fileName)
					return s_soundEffect[i];
			}
			Sound* newSound = new Sound(fileName, name, 0, new DirectX::SoundEffect(s_data.audioEngine, CA2W(fileName.c_str())), s_data.audioEngine);
			s_soundEffect.push_back(newSound);
			return newSound;
		}
		
		else if (type == "music")
		{
			for (int i = 0; i < s_music.size(); ++i)
			{
				if (fileName == s_music[i]->s_data.fileName)
					return s_music[i];
			}
			Sound* newSound = new Sound(fileName, name, 1, new DirectX::SoundEffect(s_data.audioEngine, CA2W(fileName.c_str())), s_data.audioEngine);
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
		if (!s_data.type) //effect
		{
			s_data.sound->Play();
			return true;
		}
		else if(!s_data.sound->IsInUse()) //music and not in use
		{
			std::unique_ptr<DirectX::SoundEffectInstance> tempInstance = s_data.sound->CreateInstance();
			//check for audio engine reset?
			tempInstance->Play(true);
			return true;
		}
		return false;
	}
}
