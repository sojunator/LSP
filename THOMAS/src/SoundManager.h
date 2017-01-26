#pragma once
#include "common.h"
#include <string>
#include "utils/directXTK/Audio.h"

namespace thomas
{
	class THOMAS_API SoundManager
	{
	private:
		SoundManager(std::string fileName, DirectX::SoundEffect* sound, DirectX::AudioEngine* audioEngine);
	public:
		static void Init();
		static SoundManager* CreateSound(std::string fileName, std::string type); //types: "music" or "effect"
		std::string GetFileName();

	private:
		struct Data
		{
			std::string fileName;
			DirectX::SoundEffect* sound;
			DirectX::AudioEngine* audioEngine;
		};

		static Data s_data;
		static std::vector<SoundManager*> s_music;
		static std::vector<SoundManager*> s_soundEffect;
	};
}