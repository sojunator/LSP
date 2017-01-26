#include "SoundManager.h"
#include <AtlBase.h>
#include <atlconv.h>

namespace thomas
{
	SoundManager::Data SoundManager::s_data;
	std::vector<SoundManager*> SoundManager::s_music;
	std::vector<SoundManager*> SoundManager::s_soundEffect;

	SoundManager::SoundManager(std::string fileName, DirectX::SoundEffect * sound, DirectX::AudioEngine * audioEngine)
	{
		s_data.fileName = fileName;
		s_data.sound = sound;
		s_data.audioEngine = audioEngine;
	}

	void SoundManager::Init()
	{
		//because win32 desktop app
		CoInitialize(nullptr);


		s_data.audioEngine = new DirectX::AudioEngine();
	}

	SoundManager * thomas::SoundManager::CreateSound(std::string fileName, std::string type)
	{
		if (type == "music")
		{
			for (int i = 0; i < s_music.size(); ++i)
			{
				if (fileName == s_music[i]->s_data.fileName)
					return s_music[i];
			}
			SoundManager* newSound = new SoundManager(fileName, new DirectX::SoundEffect(s_data.audioEngine, CA2W(fileName.c_str())), s_data.audioEngine);
			s_music.push_back(newSound);
			return newSound;
		}
		else if (type == "effect")
		{
			for (int i = 0; i < s_soundEffect.size(); ++i)
			{
				if (fileName == s_soundEffect[i]->s_data.fileName)
					return s_soundEffect[i];
			}
			SoundManager* newSound = new SoundManager(fileName, new DirectX::SoundEffect(s_data.audioEngine, CA2W(fileName.c_str())), s_data.audioEngine);
			s_soundEffect.push_back(newSound);
			return newSound;
		}
		return nullptr;
	}
	std::string SoundManager::GetFileName()
	{
		return s_data.fileName;
	}
}
