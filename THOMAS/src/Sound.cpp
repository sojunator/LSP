#include "Sound.h"
#include <AtlBase.h>
#include <atlconv.h>

namespace thomas
{
	Sound::Data Sound::s_data;
	std::vector<Sound*> Sound::s_music;
	std::vector<Sound*> Sound::s_soundEffect;

	Sound::Sound(std::string fileName, std::string name, Type type, DirectX::SoundEffect * sound, DirectX::AudioEngine * audioEngine)
	{
		s_data.fileName = fileName;
		s_data.name = name;
		s_data.type = type;
		s_data.sound = sound;
		s_data.audioEngine = audioEngine;
		s_data.instance = nullptr;
		if(type == Type::Music)
			s_data.instance = s_data.sound->CreateInstance();
	}

	bool Sound::Init()
	{
		//because win32 desktop app
		CoInitialize(nullptr);

		s_data.audioEngine = new DirectX::AudioEngine();
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
			s_data.sound->Play();
			return true;
		}
		//else if(!s_data.sound->IsInUse()) //is music type and not in use
		//{
			//check for audio engine reset?
			s_data.instance->Play(true);
			return true;
		//}
		//return false;
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
