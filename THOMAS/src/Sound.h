#pragma once
#include "common.h"
#include <string>

#include "utils\directXTK\SoundCommon.h"



namespace thomas
{
	class THOMAS_API Sound
	{
	public:
		enum class Type
		{
			Effect = 0,
			Music = 1
		};
	private:
		Sound(std::string fileName, std::string name, Type type, DirectX::SoundEffect* sound, DirectX::AudioEngine* audioEngine);
	public:
		static bool Init();
		static Sound* CreateSound(std::string fileName, std::string name, Type type); //types: "Music" or "Effect"
		std::string GetFileName();
		bool Play();
		void Pause();
		static void SetMasterVolume(float volume);
		static void SetFxVolume(float volume);
		static void SetMusicVolume(float volume);
		static void Destroy();

	private:
		struct Data
		{
			std::string fileName;
			std::string name;
			Type type;
			DirectX::SoundEffect* sound;
			DirectX::AudioEngine* audioEngine;
			std::unique_ptr<DirectX::SoundEffectInstance> instance;
		};

		static float s_masterVolume;
		static float s_fxVolume;
		static float s_musicVolume;
		static Data s_data;
		static std::vector<Sound*> s_music;
		static std::vector<Sound*> s_soundEffect;
	};
}