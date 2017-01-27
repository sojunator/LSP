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
		void Update();
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

		static Data s_data;
		static std::vector<Sound*> s_music;
		static std::vector<Sound*> s_soundEffect;
	};
}